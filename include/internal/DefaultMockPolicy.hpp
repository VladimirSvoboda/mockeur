/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file DefaultMockPolicy.hpp
 * @brief 
 */

#ifndef DEFAULTMOCKPOLICY_HPP_
#define DEFAULTMOCKPOLICY_HPP_

#include "AbstractCallEntry.hpp"
#include "MockPolicy.hpp"

#include "internal/CallEntry.hpp"
#include "internal/AbstractCallHandler.hpp"

#include <list>
#include <stdexcept>

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
     * Returns the stored value for the given arguments. It may be some logic (a function called with these arguments)
     * @param args The instance of arguments
     *
     * @return The stored value for the given arguments.
     */
    ReturnType value(ArgumentTypes ...)
    {
        throw std::runtime_error("Mock object is not configured for these values.");
    }

    /**
     * Returns whether the current object matches this instance of arguments.
     *
     * @param args The instance of arguments.
     * @return Whether the current object matches this instance of arguments.
     */
    bool matchArguments(ArgumentTypes ...)
    {
        return true;
    }
};

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
