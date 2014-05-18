/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file AbstractCallHandler.hpp
 * @brief Declaration and definition of private class AbstractCallHandler
 */

#ifndef ABSTRACTCALLHANDLER_HPP_
#define ABSTRACTCALLHANDLER_HPP_

#include <functional>

template<typename ReturnType, typename ... ArgumentTypes>
class AbstractCallHandler
{
public:
    /**
     * Default constructor of AbstractCallHandler
     */
    AbstractCallHandler()
    {
    }

    /**
     * Constructor of AbstractCallHandler
     *
     * @param args Instance of argument matchers for the types of the handlers
     */
    AbstractCallHandler(AbstractArgumentMatcher<ArgumentTypes>* ...)
    {
    }

    /**
     * Destructor of AbstractCallHandler
     */
    virtual ~AbstractCallHandler()
    {
    }

    /**
     * Returns the stored value for the given arguments. It may involve
     * computations as a true function can be registered.
     * @param args The instance of arguments
     *
     * @return The stored value for the given arguments.
     */
    virtual ReturnType value(ArgumentTypes ... args) = 0;

    /**
     * Returns whether the current object matches this instance of arguments.
     *
     * @param args The instance of arguments.
     * @return Whether the current object matches this instance of arguments.
     */
    virtual bool matchArguments(ArgumentTypes ... args) = 0;
};

/**
 * Abstract implementation for CallHandler. Everything in this class is common
 * for both void return type and anything else.
 * @see CallHandler
 */
template<typename ReturnType, typename ... ArgumentTypes>
class AbstractCallHandler_impl : public AbstractCallHandler<ReturnType, ArgumentTypes...>
{
public:
    /**
     * Constructor of AbstractCallHandler_impl
     *
     * @param args Instance of argument matchers for the types of the handlers
     */
    AbstractCallHandler_impl(AbstractArgumentMatcher<ArgumentTypes>* ... args)
        : AbstractCallHandler<ReturnType, ArgumentTypes...>(args...),
          matchers(args...),
          callbackFunction()
    {
    }

    /**
     * Destructor of AbstractCallHandler_impl
     */
    virtual ~AbstractCallHandler_impl()
    {
    }

    /**
     * @brief Callback function to call when the value function is called.
     * The arguments will be forwarded to the callback function.
     *
     * @param fct The callback function
     */
    virtual void then(const std::function<ReturnType(ArgumentTypes...)> fct)
    {
        callbackFunction = fct;
    }

    /**
     * Returns the stored value for the given arguments. It may be some logic (a function called with these arguments)
     * @param args The instance of arguments
     *
     * @return The stored value for the given arguments.
     */
    ReturnType value(ArgumentTypes ... args)
    {
        return callbackFunction(args...);
    }

    /**
     * Returns whether the current object matches this instance of arguments.
     *
     * @param args The instance of arguments.
     * @return Whether the current object matches this instance of arguments.
     */
    bool matchArguments(ArgumentTypes ... args)
    {
        return matchers.matchArguments(args...);
    }

protected:
    ArgumentMatchers<ArgumentTypes...> matchers;
    std::function<ReturnType(ArgumentTypes...)> callbackFunction;
};

#endif /* ABSTRACTCALLHANDLER_HPP_ */
