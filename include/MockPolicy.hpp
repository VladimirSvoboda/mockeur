/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file MockPolicy.hpp
 * @brief 
 */

#ifndef MOCKPOLICY_HPP_
#define MOCKPOLICY_HPP_

#include "DefaultCallHandlerFactory.hpp"
#include "CallEntryFactory.hpp"


/**
 * Specializes the behavior of a Mock
 */
template<typename ReturnType, typename ... ArgumentTypes>
class MockPolicy : public DefaultCallHandlerFactory<ReturnType, ArgumentTypes...>, public CallEntryFactory<ArgumentTypes...>
{
public:
    MockPolicy() {}

    virtual ~MockPolicy() {}
};

#endif /* MOCKPOLICY_HPP_ */
