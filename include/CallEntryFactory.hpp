/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file CallEntryFactory.hpp
 *
 * Declaration of the CallEntryFactory class.
 */

#ifndef CALLENTRYFACTORY_HPP_
#define CALLENTRYFACTORY_HPP_

#include "AbstractCallEntry.hpp"

/**
 * Factory of CallEntry.
 */
template<typename ... ArgTypes>
class CallEntryFactory
{
public:
    /**
     * Constructor of CallEntryFactory
     */
    CallEntryFactory()
    {
    }

    /**
     * Destructor of CallEntryFactory
     */
    virtual ~CallEntryFactory()
    {
    }

    virtual AbstractCallEntry<ArgTypes...>* create(ArgTypes ... args) = 0;

    virtual void clear() = 0;
};

#endif /* CALLENTRYFACTORY_HPP_ */
