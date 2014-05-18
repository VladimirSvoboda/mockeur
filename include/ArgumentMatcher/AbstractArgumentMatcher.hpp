/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE.txt in this distribution.
 */

/**
 * @file AbstractArgumentMatcher.hpp
 * @brief Declaration of the class AbstractArgumentMatcher
 */

#ifndef ABSTRACT_ARGUMENT_MATCHER_HPP_
#define ABSTRACT_ARGUMENT_MATCHER_HPP_

#include "internal/BaseArgumentMatcher.hpp"

/**
 * Abstract class for argument matchers. It declares a fully virtual match
 * method.
 */
template<typename Type>
class AbstractArgumentMatcher: public BaseArgumentMatcher
{
public:
    AbstractArgumentMatcher()
        : BaseArgumentMatcher()
    {
    }

    virtual ~AbstractArgumentMatcher()
    {
    }

    /**
     * Returns whether the object matches the argument.
     *
     * @param arg The argument to match.
     * @return Whether the object matches the argument.
     */
    virtual bool match(Type arg) const = 0;
};

#endif /* ABSTRACT_ARGUMENT_MATCHER_HPP_ */
