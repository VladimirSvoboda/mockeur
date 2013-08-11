/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file CallEntry_impl.hpp
 * @brief Declaration and definition of private structure CallEntry_impl
 */

#ifndef CALLENTRY_IMPL_HPP_
#define CALLENTRY_IMPL_HPP_

template<typename ... ArgumentTypes>
struct CallEntry_impl;

template<>
struct CallEntry_impl<>
{
public:
    CallEntry_impl()
    {
    }

    virtual ~CallEntry_impl()
    {
    }

    virtual bool acceptedBy() const
    {
        return true;
    }
};

/**
 * The structure is defined recursively.
 */
template<typename CurrentArgType, typename ... OtherArgTypes>
struct CallEntry_impl<CurrentArgType, OtherArgTypes...> : CallEntry_impl<OtherArgTypes...>
{
public:
    CallEntry_impl(CurrentArgType currentEntry, OtherArgTypes ... otherEntries)
        : CallEntry_impl<OtherArgTypes...>(otherEntries...), savedEntry(currentEntry)
    {
    }

    virtual ~CallEntry_impl()
    {
    }

    virtual bool acceptedBy(AbstractArgumentMatcher<CurrentArgType>* currentMatcher,
                    AbstractArgumentMatcher<OtherArgTypes>* ... otherMatchers) const
    {
        return currentMatcher->match(savedEntry) && CallEntry_impl<OtherArgTypes...>::acceptedBy(otherMatchers...);
    }

private:
    CurrentArgType savedEntry;
};


#endif /* CALLENTRY_IMPL_HPP_ */
