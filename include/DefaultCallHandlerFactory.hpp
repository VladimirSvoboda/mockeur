/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file DefaultCallHandlerFactory.hpp
 * @brief 
 */

#ifndef DEFAULTCALLHANDLERHANDLER_HPP_
#define DEFAULTCALLHANDLERHANDLER_HPP_

#include "internal/AbstractCallHandler.hpp"

/**
 * Generator of call handler in the case of the mock was not configured for the given set of arguments.
 *
 * It could be useful to provide its own DefaultCallHandlerFactory in order to:
 *  - print the arguments not matched;
 *  - call a fail function of the unit test library.
 */
template<typename ReturnType, typename ... ArgumentTypes>
class DefaultCallHandlerFactory
{
public:
    DefaultCallHandlerFactory() {};

    virtual ~DefaultCallHandlerFactory() {};

    /**
     * Returns a call handler to use when no other call handler matched the arguments.
     *
     * @param args The arguments of the call
     * @return The call handler used when no other call handler matched the arguments
     */
    virtual AbstractCallHandler<ReturnType, ArgumentTypes...>* getHandler(ArgumentTypes... args) = 0;
};

#endif /* DEFAULTCALLHANDLERHANDLER_HPP_ */
