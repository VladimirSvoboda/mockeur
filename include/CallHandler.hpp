/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file CallHandler.hpp
 *
 * Declaration and definition of the CallHandler class.
 */

#ifndef CALLHANDLER_HPP_
#define CALLHANDLER_HPP_

#include "ArgumentMatcher/AbstractArgumentMatcher.hpp"
#include "ArgumentMatchers.hpp"

#include "internal/AbstractCallHandler.hpp"

/**
 * The CallHandler class handles an instance of arguments and executes the
 * recorded instructions on the arguments. The instance of argument matchers
 * has to be provided to the constructor of the class.
 *
 * The class has 3 main types of methods:
 *  - to tell if it matches the arguments: matchArguments;
 *  - to return the value: value;
 *  - to store the expected behavior: then and thenReturn.
 *
 * This class is templatized on the return type of the mock and the instance of
 * the arguments types.
 * Example:
 *  For a function declared as:
 *   char *strncat(char *dest, const char *src, size_t n)
 *  The related CallHandler instances must be templatized as:
 *   CallHandler<char*, char*, const char*, size_t>
 */
template<typename ReturnType, typename ... ArgumentTypes>
class CallHandler;

/**
 * Specialized implementation of CallHandler class when the return type is
 * 'void'. This is mandatory to avoid compilation errors because of void
 * arguments (in the method thenReturn).
 *
 * In this implementation, the method thenReturn creates a lambda function
 * which does nothing and forwards it to the method then.
 */
template<typename ... ArgumentTypes>
class CallHandler<void, ArgumentTypes...> : public AbstractCallHandler_impl<void, ArgumentTypes...>
{
public:
    /**
     * Constructor of CallHandler
     *
     * @param args Instance of argument matchers for the types of the handlers
     */
    CallHandler(AbstractArgumentMatcher<ArgumentTypes>* ... args)
        : AbstractCallHandler_impl<void, ArgumentTypes...>(args...)
    {
    }

    /**
     * Destructor of CallHandler
     */
    ~CallHandler()
    {
    }

    /**
     * Instantiates the CallHandler object to do nothing when called.
     */
    void thenReturn()
    {
        this->then([] (ArgumentTypes...) {});
    }
};

/**
 * Implementation of the CallHandler when the return type is anything but void
 * (this implementation would fail with void return type because of the
 * function which would take void as a named argument).
 *
 * In this implementation, the method thenReturn creates a lambda function
 * returning the valueToReturn and forwards it to the method "then".
 */
template<typename ReturnType, typename ... ArgumentTypes>
class CallHandler: public AbstractCallHandler_impl<ReturnType, ArgumentTypes...>
{
public:
    /**
     * Constructor of CallHandler
     *
     * @param args Instance of argument matchers for the types of the handlers
     */
    CallHandler(AbstractArgumentMatcher<ArgumentTypes>* ... args)
        : AbstractCallHandler_impl<ReturnType, ArgumentTypes...>(args...)
    {
    }

    /**
     * Destructor of CallHandler
     */
    ~CallHandler()
    {
    }

    /**
     * Instantiates the CallHandler object to return the provided argument when
     * called.
     *
     * @param valueToReturn The argument to return when the value of the object is called.
     */
    void thenReturn(ReturnType valueToReturn)
    {
        /* [=] means that the local variable must be captured in the lambda
         * function */
        this->then([=] (ArgumentTypes...) { return valueToReturn; });
    }
};

#endif /* CALLHANDLER_HPP_ */
