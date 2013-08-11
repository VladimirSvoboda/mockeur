/*
 * (c) Copyright 2013 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file Mock.hpp
 *
 * Declaration and definition of the Mock class. It is the entry point to the library.
 */

#ifndef MOCK_HPP_
#define MOCK_HPP_

#include <list>
#include <tuple>

#include "CallHandler.hpp"
#include "AbstractCallEntry.hpp"
#include "CallEntryFactory.hpp"
#include "internal/GenericCallEntryFactory.hpp"

/**
 * This class is templatized on the return type of the mock and the instance of the arguments' types.
 * Example:
 *  For a function declared as:
 *   char *strncat(char *dest, const char *src, size_t n)
 *  The related CallHandler instances must be templatized as:
 *   Mock<char*, char*, const char*, size_t>
 */
template<typename ReturnType, typename ... ArgumentTypes>
class Mock
{
public:
    /**
     * Default constructor of mock
     */
    Mock();

    /**
     * Constructor of mock which will use the provided call entry factory to store the call entries.
     *
     * @param callEntryFactory A pointer to the call entry factory to use
     */
    Mock(CallEntryFactory<ArgumentTypes...>* callEntryFactoryPtr);

    /**
     * Destructor of mock
     */
    virtual ~Mock();

    /**
     * Reset the mock to the initial state. The history and the instance of arguments matchers are removed.
     */
    void clear();

    /**
     * @brief Initialize the mock to match some arguments with an instance of argument matchers.
     * It returns a new CallHandler which must be initialized to return the expected value.
     *
     * @param matchersPtr Pointers to argument matchers (the instance of argument matchers).
     * @return A call handler which will match the same arguments as the instance of argument matchers.
     */
    CallHandler<ReturnType, ArgumentTypes...>* when(AbstractArgumentMatcher<ArgumentTypes>* ... matchersPtr);

    /**
     * @brief Returns the number of calls to this mock which are matched by the provided instance of argument matchers.
     * The provided arguments matchers may never have been used with the when() method.
     *
     * @param matchersPtr Pointers to argument matchers (the instance of argument matchers).
     *
     * @return The number of calls matched by the instance of argument matchers.
     */
    unsigned int numberOfCalls(AbstractArgumentMatcher<ArgumentTypes>* ... matchersPtr) const;

    /**
     * @brief Returns the value which has been stored for the provided instance of arguments.
     * If the mock has not been initialized for these values (no instance of matchers which matches this instance of
     * arguments), this function throws an exception.
     *
     * Remark: if a call to the mock is matched by multiple CallHandler, the first one that has been instantiated will
     * handle the call.
     *
     * @param args The arguments of the call to the mock (the instance of arguments).
     * @return The value which has been stored for the provided instance of arguments.
     */
    ReturnType value(ArgumentTypes ... args);

private:
    std::list<CallHandler<ReturnType, ArgumentTypes...>*> callHandlerList;
    std::list<AbstractCallEntry<ArgumentTypes...>*> callHistoryList;
    CallEntryFactory<ArgumentTypes...>* callEntryFactory;

    CallHandler<ReturnType, ArgumentTypes...>* getMatchingHandler(ArgumentTypes ... args) const;
};

template<typename ReturnType, typename ... ArgumentTypes>
Mock<ReturnType, ArgumentTypes...>::Mock()
    : Mock<ReturnType, ArgumentTypes...>::Mock(new GenericCallEntryFactory<ArgumentTypes...>)
{
}

template<typename ReturnType, typename ... ArgumentTypes>
Mock<ReturnType, ArgumentTypes...>::Mock(CallEntryFactory<ArgumentTypes...>* callEntryFactoryPtr)
    : callHandlerList(), callHistoryList(), callEntryFactory(callEntryFactoryPtr)
{
}

template<typename ReturnType, typename ... ArgumentTypes>
Mock<ReturnType, ArgumentTypes...>::~Mock()
{
    clear();
}

template<typename ReturnType, typename ... ArgumentTypes>
inline CallHandler<ReturnType, ArgumentTypes...> * Mock<ReturnType, ArgumentTypes...>::when(
    AbstractArgumentMatcher<ArgumentTypes>* ... matchersPtr)
{
    CallHandler<ReturnType, ArgumentTypes...> *callHandlerPtr = new CallHandler<ReturnType, ArgumentTypes...>(
        matchersPtr...);
    callHandlerList.push_back(callHandlerPtr);

    return callHandlerPtr;
}

template<typename ReturnType, typename ... ArgumentTypes>
inline ReturnType Mock<ReturnType, ArgumentTypes...>::value(ArgumentTypes ... args)
{
    CallHandler<ReturnType, ArgumentTypes...>* callHandlerPtr = getMatchingHandler(args...);

    callHistoryList.push_back(callEntryFactory->create(args...));

    return callHandlerPtr->value(args...);
}

template<typename ReturnType, typename ... ArgumentTypes>
inline unsigned int Mock<ReturnType, ArgumentTypes...>::numberOfCalls(
    AbstractArgumentMatcher<ArgumentTypes>* ... matchersPtr) const
{
    unsigned int nbrCall = 0;

    for (AbstractCallEntry<ArgumentTypes...>* callArgument : callHistoryList) {
        if (callArgument->acceptedBy(matchersPtr...))
            nbrCall++;
    }

    return nbrCall;
}

template<typename ReturnType, typename ... ArgumentTypes>
inline void Mock<ReturnType, ArgumentTypes...>::clear()
{
    for (auto it = callHandlerList.begin(); it != callHandlerList.end(); ++it)
        delete *it;

    callHandlerList.clear();

    callHistoryList.clear();

    callEntryFactory->clear();
}

template<typename ReturnType, typename ... ArgumentTypes>
inline CallHandler<ReturnType, ArgumentTypes...>* Mock<ReturnType, ArgumentTypes...>::getMatchingHandler(
    ArgumentTypes ... args) const
{
    for (CallHandler<ReturnType, ArgumentTypes...>* callHandlerPtr : callHandlerList) {
        if (callHandlerPtr->matchArguments(args...))
            return callHandlerPtr;
    }

    throw "Mock object is not configured for these values.";
}

#endif /* MOCK_HPP_ */
