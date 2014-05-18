/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file ArgumentMatchers.hpp
 *
 * Declaration and definition of the ArgumentMatcher class.
 * Inspiration for this implementation comes from the tuple class
 * implementation of GCC.
 */

#ifndef ARGUMENTMATCHERS_HPP_
#define ARGUMENTMATCHERS_HPP_

#include "internal/ArgumentMatchers_impl.hpp"

#include "ArgumentMatcher/AbstractArgumentMatcher.hpp"

/**
 * The ArgumentMatchers class is there for one thing, one thing only: tell
 * whether it matches an instance of arguments.
 * This class actually encapsulates an instance of argument matchers.
 */
template<typename ... ArgTypes>
class ArgumentMatchers: public ArgumentMatchers_impl<ArgTypes...>
{
public:
    /**
     * Constructor of ArgumentMatchers
     * @param args An instance of argument matchers.
     */
    ArgumentMatchers(AbstractArgumentMatcher<ArgTypes>* ... args)
        : ArgumentMatchers_impl<ArgTypes...>(args...)
    {
    }

    /**
     * Destructor of ArgumentMatchers
     */
    ~ArgumentMatchers()
    {
    }

    /**
     * Returns whether the current object matches the instance of arguments.
     *
     * @param args The instance of arguments
     * @return Whether the current object matches the instance of arguments.
     */
    bool matchArguments(ArgTypes ... args) const
    {
        return ArgumentMatchers_impl<ArgTypes...>::matchArguments(args...);
    }
};

#endif /* ARGUMENTMATCHERS_HPP_ */
