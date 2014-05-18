/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE.txt in this distribution.
 */

/**
 * @file TypeArgumentMatcher.hpp
 * @brief Declaration and definition of the class TypeArgumentMatcher
 */

#ifndef TYPE_ARGUMENT_MATCHER_HPP_
#define TYPE_ARGUMENT_MATCHER_HPP_

#include "AbstractArgumentMatcher.hpp"

/**
 * This matcher matches any object of the type on which it is templatized.
 */
template<typename Type>
class TypeArgumentMatcher: public AbstractArgumentMatcher<Type>
{
public:
    TypeArgumentMatcher()
        : AbstractArgumentMatcher<Type>()
    {
    }

    bool match(Type) const
    {
        return true;
    }
};

#endif /* TYPE_ARGUMENT_MATCHER_HPP_ */
