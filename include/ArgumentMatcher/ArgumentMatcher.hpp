/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE.txt in this distribution.
 */

/**
 * @file ArgumentMatcher.hpp
 * @brief Declaration of the class ArgumentMatcher
 */

#ifndef ARGUMENT_MATCHER_HPP_
#define ARGUMENT_MATCHER_HPP_

#include <list>

#include "FixedValueArgumentMatcher.hpp"
#include "TypeArgumentMatcher.hpp"

/**
 * Utility class to easily create common ArgumentMatcher.
 */
class ArgumentMatcher
{
public:
    ArgumentMatcher()
    {
    }

    /**
     * Delete all the created matchers.
     */
    static void clear();

    /**
     * Dynamically creates a matcher for the provided value.
     *
     * @param arg The value to match.
     * @return A pointer to a newly created matcher.
     */
    template<typename Type>
    static FixedValueArgumentMatcher<Type>* eq(Type arg)
    {
        FixedValueArgumentMatcher<Type>* matcher = new FixedValueArgumentMatcher<Type>(arg);

        fixedValueMatcher.push_back(matcher);

        return matcher;
    }

    /**
     * Dynamically creates a matcher for the provided type.
     *
     * @return A pointer to a newly created matcher.
     */
    template<typename Type>
    static TypeArgumentMatcher<Type>* any()
    {
        TypeArgumentMatcher<Type>* matcher = new TypeArgumentMatcher<Type>();

        fixedValueMatcher.push_back(matcher);

        return matcher;
    }

    static TypeArgumentMatcher<int>* anyInt();
    static TypeArgumentMatcher<char>* anyChar();
    static TypeArgumentMatcher<char*>* anyCharPointer();
    static FixedValueArgumentMatcher<void*>* isNull();
    static TypeArgumentMatcher<void*>* anyVoidPointer();

private:
    static std::list<BaseArgumentMatcher*> fixedValueMatcher;

    static TypeArgumentMatcher<int> anyIntMatcher;
    static TypeArgumentMatcher<char> anyCharMatcher;
    static TypeArgumentMatcher<char*> anyCharPointerMatcher;
    static FixedValueArgumentMatcher<void*> isNullMatcher;
    static TypeArgumentMatcher<void*> anyVoidPointerMatcher;
};

#endif /* ARGUMENT_MATCHER_HPP_ */
