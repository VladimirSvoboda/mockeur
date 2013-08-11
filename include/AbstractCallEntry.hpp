/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file BaseCallEntry
 *
 * Declaration and definition of the AbstractCallEntry class.
 */

#ifndef ABSTRACTCALLENTRY_HPP_
#define ABSTRACTCALLENTRY_HPP_

template<typename ... ArgTypes>
class AbstractCallEntry
{
public:
    /**
     * Constructor of BaseCallEntry
     */
    AbstractCallEntry()
    {
    }

    /**
     * Destructor of BaseCallEntry
     */
    virtual ~AbstractCallEntry()
    {
    }

    /**
     * Returns whether the current object is matched by the instance of argument matchers.
     *
     * @param matchersPtr Pointers to argument matchers
     * @return Whether the current object is matched by the instance of argument matchers.
     */
    virtual bool acceptedBy(AbstractArgumentMatcher<ArgTypes>* ... matchersPtr) const = 0;
};

#endif /* ABSTRACTCALLENTRY_HPP_ */
