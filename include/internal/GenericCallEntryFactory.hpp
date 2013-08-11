/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file GenericCallEntryFactory.hpp
 * @brief Default implementation of the CallEntryFactory
 */

#ifndef GENERICCALLENTRYFACTORY_HPP_
#define GENERICCALLENTRYFACTORY_HPP_

#include "AbstractCallEntry.hpp"
#include "internal/CallEntry.hpp"

#include <list>

/**
 * Factory of CallEntry. It uses the copy constructor of the arguments.
 */
template<typename ... ArgTypes>
class GenericCallEntryFactory: public CallEntryFactory<ArgTypes...>
{
public:
    /**
     * Constructor of GenericCallEntryFactory
     */
    GenericCallEntryFactory()
        : createdItemList()
    {
    }

    /**
     * Destructor of GenericCallEntryFactory
     */
    ~GenericCallEntryFactory()
    {
        clear();
    }

    void clear() {
        createdItemList.clear();
    }

    AbstractCallEntry<ArgTypes...>* create(ArgTypes ... args)
    {
        createdItemList.push_back(CallEntry<ArgTypes...>(args...));

        return &(createdItemList.back());
    }

private:
    std::list<CallEntry<ArgTypes...> > createdItemList;
};

#endif /* GENERICCALLENTRYFACTORY_HPP_ */
