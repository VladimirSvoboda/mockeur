/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE.txt in this distribution.
 */

/**
 * @file ArgumentMatchers_impl.hpp
 * @brief Declaration and definition of the private structure ArgumentMatchers_impl
 */

#ifndef ARGUMENTMATCHERS_IMPL_HPP_
#define ARGUMENTMATCHERS_IMPL_HPP_

/**
 * Declaration of the ArgumentMatchers_impl
 */
template<typename ... ArgumentTypes>
struct ArgumentMatchers_impl;

/**
 * Implementation of ArgumentMatchers_impl without any template parameters (a matcher matching no argument).
 * It always returns true.
 */
template<>
struct ArgumentMatchers_impl<>
{
public:
    /**
     * Constructor of ArgumentMatchers_impl without template parameter
     */
    ArgumentMatchers_impl()
    {
    }

    /**
     * Destructor of ArgumentMatchers_impl without template parameter
     */
    virtual ~ArgumentMatchers_impl()
    {
    }

    /**
     * Returns true
     *
     * @return true
     */
    virtual bool matchArguments() const
    {
        return true;
    }
};

/**
 * Implementation of ArgumentMatchers_impl with at least one template parameter.
 * The structure is defined recursively. The parent class is either:
 *  - the structure itself with one template parameter less;
 *  - the above structure which takes no template parameter.
 *
 * It checks if it matches the current argument and if it is the case, forward the remaining checks to the parent class.
 */

template<typename CurrentArgType, typename ... OtherArgTypes>
struct ArgumentMatchers_impl<CurrentArgType, OtherArgTypes...> : ArgumentMatchers_impl<OtherArgTypes...>
{
public:
    /**
     * Constructor of ArgumentMatchers_impl with template parameters
     *
     * @param currentMatcher A pointer to the first ArgumentMatcher
     * @param otherMatchers Pointers to the remaining ArgumentMatchers
     */
    ArgumentMatchers_impl(AbstractArgumentMatcher<CurrentArgType> *currentMatcher,
                         AbstractArgumentMatcher<OtherArgTypes>*... otherMatchers)
        : ArgumentMatchers_impl<OtherArgTypes...>(otherMatchers...), argumentMatcher(currentMatcher)
    {
    }

    /**
     * Destructor of ArgumentMatchers_impl with template parameters
     */
    virtual ~ArgumentMatchers_impl()
    {
    }

    /**
     * Returns whether current object matches the instance of arguments.
     *
     * @param currentArg The first argument
     * @param otherArgs The other arguments
     * @return Whether current object matches the instance of arguments.
     */
    virtual bool matchArguments(CurrentArgType currentArg, OtherArgTypes ... otherArgs) const
    {
        return argumentMatcher->match(currentArg)
            && ArgumentMatchers_impl<OtherArgTypes...>::matchArguments(otherArgs...);
    }

private:
    /**
     * A pointer to the argument matcher of the current nesting argument.
     */
    AbstractArgumentMatcher<CurrentArgType>* argumentMatcher;
};

#endif /* ARGUMENTMATCHERS_IMPL_HPP_ */
