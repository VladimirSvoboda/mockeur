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

/* Declaration of the mocks and definition of the mocked function */
Mock<int, const char*, unsigned int> mock_ftp_send;
Mock<enum DataModel> mock_ftp_getDataModel;
Mock<void, enum DataModel> mock_ftp_setDataModel;

int ftp_send(const char* content, unsigned int length)
{
    return mock_ftp_send.value(content, length);
}

enum DataModel ftp_getDataModel(void)
{
    return mock_ftp_getDataModel.value();
}

void ftp_setDataModel(enum DataModel dataModel)
{
    mock_ftp_setDataModel.value(dataModel);
}

void tearDown()
{
    mock_ftp_send.clear();
    mock_ftp_getDataModel.clear();
    mock_ftp_setDataModel.clear();
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

    mock_ftp_getDataModel.when()->thenReturn(BINARY);

    int succeedToSend = sendFile(filePtr);

    assert(1u == mock_ftp_send.numberOfCalls(ArgumentMatcher::eq<const char*>(filePtr->content),
                                             ArgumentMatcher::eq<unsigned int>(filePtr->length)));
    assert(1u == mock_ftp_getDataModel.numberOfCalls());
    assert(0u == mock_ftp_setDataModel.numberOfCalls(ArgumentMatcher::any<enum DataModel>()));
    assert(succeedToSend);

    tearDown();
}

void testUnableToSendAnyByte(void)
{
    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::any<unsigned int>())
                 ->thenReturn(0);

    mock_ftp_getDataModel.when()->thenReturn(ASCII);
    mock_ftp_setDataModel.when(ArgumentMatcher::any<enum DataModel>())->then(
        [] (enum DataModel) {}
    );

    int succeedToSend = sendFile(filePtr);

    assert(1u == mock_ftp_send.numberOfCalls(ArgumentMatcher::any<const char*>(),
                                             ArgumentMatcher::any<unsigned int>()));
    assert(1u == mock_ftp_getDataModel.numberOfCalls());
    assert(1u == mock_ftp_setDataModel.numberOfCalls(ArgumentMatcher::eq<enum DataModel>(BINARY)));
    assert(!succeedToSend);

    tearDown();
}

void testSendInTwoTimesWithSpecializedMatcher(void)
{
    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    mock_ftp_getDataModel.when()->thenReturn(BINARY);

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
    assert(1u == mock_ftp_getDataModel.numberOfCalls());
    assert(0u == mock_ftp_setDataModel.numberOfCalls(ArgumentMatcher::any<enum DataModel>()));
    assert(succeedToSend);

    tearDown();
}

void testSetPolicy(void)
{
    AlternativeMockPolicy<int, const char*, unsigned int> mockPolicy;

    mock_ftp_send.when(ArgumentMatcher::any<const char*>(),
                       ArgumentMatcher::eq<unsigned int>(128u))
                 ->thenReturn(0);
    mock_ftp_send.setPolicy(&mockPolicy);

    mock_ftp_getDataModel.when()->thenReturn(BINARY);

    File_s* filePtr = new File_s;
    filePtr->content = "Hello world!";
    filePtr->length = 13;

    try {
        sendFile(filePtr);

        assert(false);
    } catch (std::runtime_error e) {
        /* Expected */
    }

    tearDown();
}

int main (int, const char* [])
{
    testDirectlySendFullContent();
    testUnableToSendAnyByte();
    testSendInTwoTimesWithSpecializedMatcher();
    testSetPolicy();

    return EXIT_SUCCESS;
}
