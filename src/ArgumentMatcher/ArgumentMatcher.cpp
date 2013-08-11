/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file ArgumentMatcher.cpp
 * @brief Implementation of ArgumentMatcher.hpp
 */

#include "ArgumentMatcher/ArgumentMatcher.hpp"

std::list<BaseArgumentMatcher*> ArgumentMatcher::fixedValueMatcher = std::list<BaseArgumentMatcher*>();

TypeArgumentMatcher<int> ArgumentMatcher::anyIntMatcher = TypeArgumentMatcher<int>();
TypeArgumentMatcher<char> ArgumentMatcher::anyCharMatcher = TypeArgumentMatcher<char>();
TypeArgumentMatcher<char*> ArgumentMatcher::anyCharPointerMatcher = TypeArgumentMatcher<char*>();
FixedValueArgumentMatcher<void*> ArgumentMatcher::isNullMatcher = FixedValueArgumentMatcher<void*>(nullptr);
TypeArgumentMatcher<void*> ArgumentMatcher::anyVoidPointerMatcher = TypeArgumentMatcher<void*>();

void ArgumentMatcher::clear()
{
    for (auto it = ArgumentMatcher::fixedValueMatcher.begin(); it != ArgumentMatcher::fixedValueMatcher.end(); ++it) {
        delete *it;
    }

    ArgumentMatcher::fixedValueMatcher.clear();
}

TypeArgumentMatcher<int>* ArgumentMatcher::anyInt()
{
    return &anyIntMatcher;
}
TypeArgumentMatcher<char>* ArgumentMatcher::anyChar()
{
    return &anyCharMatcher;
}
FixedValueArgumentMatcher<void*>* ArgumentMatcher::isNull()
{
    return &isNullMatcher;
}

TypeArgumentMatcher<void*>* ArgumentMatcher::anyVoidPointer()
{
    return &anyVoidPointerMatcher;
}
