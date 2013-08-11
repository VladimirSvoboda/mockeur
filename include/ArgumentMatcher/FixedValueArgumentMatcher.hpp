/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE.txt in this distribution.
 */

/**
 * @file FixedValueArgumentMatcher.hpp
 * @brief Declaration and definition of the class FixedValueArgumentMatcher
 */

#ifndef FIXED_VALUE_ARGUMENT_MATCHER_HPP_
#define FIXED_VALUE_ARGUMENT_MATCHER_HPP_

#include "AbstractArgumentMatcher.hpp"

/**
 * This matcher matches using the "==" operator the object given at its constructor.
 */
template<typename Type>
class FixedValueArgumentMatcher: public AbstractArgumentMatcher<Type>
{
public:
    /**
     * Constructor of FixedValueArgumentMatcher
     * @param valueToMatch The value that has to be matched
     */
    FixedValueArgumentMatcher(Type valueToMatch)
        : AbstractArgumentMatcher<Type>(), valueMatched(valueToMatch)
    {
    }

    /**
     * Returns whether the argument equals (using the "==" operator) the stored value.
     *
     * @param valueToTest The argument to test
     * @return Whether the argument equals (using the "==" operator) the stored value.
     */
    bool match(Type valueToTest) const
    {
        return valueMatched == valueToTest;
    }

private:
    Type valueMatched;
};

#endif /* FIXED_VALUE_ARGUMENT_MATCHER_HPP_ */
