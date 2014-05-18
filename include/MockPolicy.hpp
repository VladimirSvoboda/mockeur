/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file MockPolicy.hpp
 * @brief This file contains the declaration of the @ref MockPolicy class which
 *        can be used to customise the behavior of the mock:
 *        - for the copy of the arguments (for later reuse like in
 *          numberOfCalls method)
 *        - for the handling of unexpected calls (when no matchers matches the
 *          arguments provided to the value method)
 */

#ifndef MOCKPOLICY_HPP_
#define MOCKPOLICY_HPP_

#include "DefaultCallHandlerFactory.hpp"
#include "CallEntryFactory.hpp"


/**
 * Specializes the behavior of a Mock by allowing to decide how the Mock should
 * react when its value method is called:
 *  - how to copy the arguments (for later reuse like in numberOfCalls method)
 *  - how to handle unexpected calls (when no matchers matches the arguments
 *    provided to the value method)
 */
template<typename ReturnType, typename ... ArgumentTypes>
class MockPolicy : public DefaultCallHandlerFactory<ReturnType, ArgumentTypes...>,
                   public CallEntryFactory<ArgumentTypes...>
{
public:
    MockPolicy() {}

    virtual ~MockPolicy() {}
};

#endif /* MOCKPOLICY_HPP_ */
