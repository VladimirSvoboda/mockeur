/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file CallEntry.hpp
 *
 * Declaration and definition of the CallEntry class.
 */

#ifndef CALLENTRY_HPP_
#define CALLENTRY_HPP_

#include "AbstractCallEntry.hpp"
#include "internal/CallEntry_impl.hpp"

/**
 * Class to store a call history entry and to tell whether the entry is
 * accepted by an instance of argument matchers.
 */
template<typename ... ArgTypes>
class CallEntry: public CallEntry_impl<ArgTypes...>, public AbstractCallEntry<ArgTypes...>
{
public:
    /**
     * Constructor of CallEntry
     *
     * @param args Arguments to store
     */
    CallEntry(ArgTypes ... args)
        : CallEntry_impl<ArgTypes...>(args...)
    {
    }

    /**
     * Destructor of CallEntry
     */
    ~CallEntry()
    {
    }

    bool acceptedBy(AbstractArgumentMatcher<ArgTypes>* ... matchersPtr) const
    {
        return CallEntry_impl<ArgTypes...>::acceptedBy(matchersPtr...);
    }
};

#endif /* CALLENTRY_HPP_ */
