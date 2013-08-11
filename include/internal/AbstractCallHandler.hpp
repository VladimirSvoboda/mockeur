/*
 * (c) Copyright 2013 Vladimir Svoboda
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

/**
 * Abstract implementation for CallHandler. Everything in this class is common for both void return type and anything else.
 * @see CallHandler
 */
template<typename ReturnType, typename ... ArgumentTypes>
class AbstractCallHandler
{
public:
    /**
     * Constructor of AbstractCallHandler
     *
     * @param args Instance of argument matchers for the types of the handlers
     */
    AbstractCallHandler(AbstractArgumentMatcher<ArgumentTypes>* ... args)
        : matchers(args...), callbackFunction()
    {
    }

    /**
     * Destructor of AbstractCallHandler
     */
    virtual ~AbstractCallHandler()
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
