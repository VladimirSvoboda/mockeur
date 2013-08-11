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
#include <cassert>
#include <cstdlib>

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

Mock<int, const char*, unsigned int> mock_ftp_send;

int ftp_send(const char* content, unsigned int length)
{
    return mock_ftp_send.value(content, length);
}

void testRetryProcedureOfSendFile()
{
    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::any<unsigned int>())
                 ->thenReturn(-1);

    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    int sendFileReturnCode = sendFile(filePtr);

    assert(1 == mock_ftp_send.numberOfCalls(ArgumentMatcher::any<const char*>(),
                                         ArgumentMatcher::any<unsigned int>()));
    assert(0 < sendFileReturnCode);
}

int main (int argc, const char* argv[])
{
    testRetryProcedureOfSendFile();

    return EXIT_SUCCESS;
}
