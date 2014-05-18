/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file MockTest.cpp
 * @brief Unit tests for the class Mock
 */

#include "Mock.hpp"
#include "ArgumentMatcher/ArgumentMatcher.hpp"

#include "AlternativeMockPolicy.hpp"

extern "C"
{
#include "FtpClient.h"
}

#include <cassert>
#include <cstdlib>
#include <stdexcept>

/* Declaration of the mock and definition of the mocked function */
Mock<int, const char*, unsigned int> mock_ftp_send;

int ftp_send(const char* content, unsigned int length)
{
    return mock_ftp_send.value(content, length);
}

/* First unit test */
void testDirectlySendFullContent(void)
{
    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::any<unsigned int>())
                 ->thenReturn(filePtr->length);

    int succeedToSend = sendFile(filePtr);

    assert(1u == mock_ftp_send.numberOfCalls(ArgumentMatcher::eq<const char*>(filePtr->content),
                                             ArgumentMatcher::eq<unsigned int>(filePtr->length)));
    assert(succeedToSend);

    mock_ftp_send.clear();
}

void testUnableToSendAnyByte(void)
{
    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::any<unsigned int>())
                 ->thenReturn(0);

    int succeedToSend = sendFile(filePtr);

    assert(1u == mock_ftp_send.numberOfCalls(ArgumentMatcher::any<const char*>(),
                                             ArgumentMatcher::any<unsigned int>()));
    assert(!succeedToSend);

    mock_ftp_send.clear();
}

void testSendInTwoTimesWithSpecializedMatcher(void)
{
    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    /* First time, it only send the first 5 bytes */
    mock_ftp_send.when(ArgumentMatcher::eq<const char*>(filePtr->content),
                       ArgumentMatcher::eq<unsigned int>(filePtr->length))
                 ->thenReturn(5);
    /* The second time, start to send since the 5th bytes. The remaining bytes
     * will all be sent. */
    mock_ftp_send.when(ArgumentMatcher::eq<const char*>(&(filePtr->content[5])),
                       ArgumentMatcher::eq<unsigned int>(8))
                 ->thenReturn(8);

    int succeedToSend = sendFile(filePtr);

    assert(2u == mock_ftp_send.numberOfCalls(ArgumentMatcher::any<const char*>(),
                                             ArgumentMatcher::any<unsigned int>()));
    assert(succeedToSend);

    mock_ftp_send.clear();
}

void testSetPolicy(void)
{
    AlternativeMockPolicy<int, const char*, unsigned int> mockPolicy;

    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::eq<unsigned int>(128u))
                 ->thenReturn(0);
    mock_ftp_send.setPolicy(&mockPolicy);

    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    try {
        sendFile(filePtr);

        assert(false);
    } catch (std::runtime_error e) {
        /* Expected */
    }

    mock_ftp_send.clear();
}

int main (int, const char* [])
{
    testDirectlySendFullContent();
    testUnableToSendAnyByte();
    testSendInTwoTimesWithSpecializedMatcher();
    testSetPolicy();

    return EXIT_SUCCESS;
}
