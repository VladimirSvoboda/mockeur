/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file DefaultMockPolicy.hpp
 * @brief Implementation of the default @ref MockPolicy
 */

#ifndef DEFAULTMOCKPOLICY_HPP_
#define DEFAULTMOCKPOLICY_HPP_

#include "AbstractCallEntry.hpp"
#include "MockPolicy.hpp"

#include "internal/CallEntry.hpp"
#include "internal/AbstractCallHandler.hpp"

#include <list>
#include <stdexcept>


/**
 * DefaultCallHandler matches any arguments and always throws an exception
 * when its value method is called.
 */
template<typename ReturnType, typename ... ArgumentTypes>
class DefaultCallHandler: public AbstractCallHandler<ReturnType, ArgumentTypes...>
{
public:
    /**
     * Constructor of DefaultCallHandler
     *
     * @param args Instance of argument matchers for the types of the handlers
     */
    DefaultCallHandler()
        : AbstractCallHandler<ReturnType, ArgumentTypes...>()
    {
    }

    /**
     * Destructor of DefaultCallHandler
     */
    virtual ~DefaultCallHandler()
    {
    }

    /**
     * Throws a @ref std::runtime_error telling that the @ref Mock object has
     * not been configured for these arguments.
     *
     * @param args The instance of arguments
     *
     * @throws A @ref std::runtime_error
     */
    ReturnType value(ArgumentTypes ...)
    {
        throw std::runtime_error("Mock object is not configured for these values.");
    }

    /**
     * Returns true.
     *
     * @param args The instance of arguments.
     * @return true
     */
    bool matchArguments(ArgumentTypes ...)
    {
        return true;
    }
};

/**
 * DefaultMockPolicy uses the copy constructor to copy arguments to a list and
 * it provides a @ref DefaultCallHandler, which always throws an exception, to
 * handle unexpected calls.
 */
template<typename ReturnType, typename ... ArgumentTypes>
class DefaultMockPolicy: public MockPolicy<ReturnType, ArgumentTypes...>
{
public:
    DefaultMockPolicy()
        : MockPolicy<ReturnType, ArgumentTypes...>(), handler()
    {
    }

    virtual ~DefaultMockPolicy()
    {
        clear();
    }

    virtual AbstractCallHandler<ReturnType, ArgumentTypes...>* getHandler(ArgumentTypes ...)
    {
        return &handler;
    }

    void clear()
    {
        createdItemList.clear();
    }

    AbstractCallEntry<ArgumentTypes...>* create(ArgumentTypes ... args)
    {
        createdItemList.push_back(CallEntry<ArgumentTypes...>(args...));

        return &(createdItemList.back());
    }

private:
    DefaultCallHandler<ReturnType, ArgumentTypes...> handler;
    std::list<CallEntry<ArgumentTypes...> > createdItemList;
};

#endif /* DEFAULTMOCKPOLICY_HPP_ */
