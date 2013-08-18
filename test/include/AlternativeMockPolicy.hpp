/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file AlternativeMockPolicy.hpp
 * @brief 
 */

#ifndef ALTERNATIVEMOCKPOLICY_HPP_
#define ALTERNATIVEMOCKPOLICY_HPP_

#include "internal/AbstractCallHandler.hpp"
#include "internal/DefaultMockPolicy.hpp"

#include <stdexcept>

template<typename ReturnType, typename ... ArgumentTypes>
class AlternativeMockPolicy: public DefaultMockPolicy<ReturnType, ArgumentTypes...>
{
public:
    AlternativeMockPolicy()
        : DefaultMockPolicy<ReturnType, ArgumentTypes...>()
    {
    }

    virtual ~AlternativeMockPolicy()
    {
    }

    virtual AbstractCallHandler<ReturnType, ArgumentTypes...>* getHandler(ArgumentTypes ...)
    {
        throw std::runtime_error("Mock object is not configured for these values.");
    }
};

#endif /* ALTERNATIVEMOCKPOLICY_HPP_ */
