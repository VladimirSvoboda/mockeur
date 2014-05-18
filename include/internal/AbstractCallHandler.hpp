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
class AbstractCallHandler;

template<typename ... ArgumentTypes>
class AbstractCallHandler<void, ArgumentTypes...>
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
     * Call the function defined for this instance of matchers.
     * @param args The instance of arguments
     */
    virtual void value(ArgumentTypes ... args) = 0;

    /**
     * Returns whether the current object matches this instance of arguments.
     *
     * @param args The instance of arguments.
     * @return Whether the current object matches this instance of arguments.
     */
    virtual bool matchArguments(ArgumentTypes ... args) = 0;
};

template<typename ReturnType>
class AbstractCallHandler<ReturnType>
{
public:
    /**
     * Default constructor of AbstractCallHandler
     */
    AbstractCallHandler()
    {
    }

    /**
     * Destructor of AbstractCallHandler
     */
    virtual ~AbstractCallHandler()
    {
    }

    /**
     * Call the registered function.
     *
     * @return The value computed by the registered function.
     */
    virtual ReturnType value() = 0;

    /**
     * Returns whether the matchers accepts the absence of arguments.
     *
     * @return Whether the matchers accepts the absence of arguments.
     */
    virtual bool matchArguments() = 0;
};

template<>
class AbstractCallHandler<void>
{
public:
    /**
     * Default constructor of AbstractCallHandler
     */
    AbstractCallHandler()
    {
    }

    /**
     * Destructor of AbstractCallHandler
     */
    virtual ~AbstractCallHandler()
    {
    }

    /**
     * Call the registered function.
     */
    virtual void value() = 0;

    /**
     * Returns whether the matchers accepts the absence of arguments.
     *
     * @return Whether the matchers accepts the absence of arguments.
     */
    virtual bool matchArguments() = 0;
};

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

#endif /* ABSTRACTCALLHANDLER_HPP_ */
