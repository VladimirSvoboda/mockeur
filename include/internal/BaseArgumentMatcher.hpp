/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file BaseArgumentMatcher.hpp
 * @brief Declaration and implementation of the class BaseArgumentMatcher.
 */

#ifndef BASEARGUMENTMATCHER_HPP_
#define BASEARGUMENTMATCHER_HPP_

/**
 * Base class without template for argument matchers.
 * This class is used to have a common non-templatized base class for every argument matcher.
 */
class BaseArgumentMatcher
{
public:
    BaseArgumentMatcher()
    {
    }

    virtual ~BaseArgumentMatcher()
    {
    }
};

#endif /* BASEARGUMENTMATCHER_HPP_ */
