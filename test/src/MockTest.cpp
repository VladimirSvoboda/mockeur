/*
 * (c) Copyright 2013 Vladimir Svoboda
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

#include <cassert>
#include <cstdlib>
#include <stdexcept>

/* Declare the structures and the behavior of the function to unit test */
extern "C"
{
typedef struct
{
    const char* content;
    unsigned int length;
} File_s;


int ftp_send(const char* content, unsigned int length);
int sendFile (File_s* filePtr);

int sendFile (File_s* filePtr)
{
    int numberOfRetry = 0;
    int sendErrorCode = ftp_send(filePtr->content, filePtr->length);

    if (sendErrorCode == -1) {
        numberOfRetry++;
        // some retry procedure
    }

    return numberOfRetry;
}
}

/* Declaration of the mock and definition of the mocked function */
Mock<int, const char*, unsigned int> mock_ftp_send;

int ftp_send(const char* content, unsigned int length)
{
    return mock_ftp_send.value(content, length);
}

/* First unit test */
void testRetryProcedureOfSendFile()
{
    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::any<unsigned int>())
                 ->thenReturn(-1);

    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    int sendFileReturnCode = sendFile(filePtr);

    assert(1u == mock_ftp_send.numberOfCalls(ArgumentMatcher::any<const char*>(),
                                             ArgumentMatcher::any<unsigned int>()));
    assert(0 < sendFileReturnCode);

    mock_ftp_send.clear();
}

void testSetPolicy()
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
        // Expected
    }

    mock_ftp_send.clear();
}

int main (int, const char* [])
{
    testRetryProcedureOfSendFile();
    testSetPolicy();

    return EXIT_SUCCESS;
}
