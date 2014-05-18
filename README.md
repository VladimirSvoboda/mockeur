mockeur
=======

A C++ mocking library for C (hence without classes) code which allows to easily
simulate the behavior of a C function and thus to unit test it. The behavior of
the function can change in each test.
The main purpose of the library is to allow the developer to simulate the
behavior of a deep layer of the code in order to write its unit tests (e.g.
network layer, hardware abstraction layer...).

Important note:
The "real" code of the mocked function must not be compiled in the unit tests in
order to avoid the error: function already defined.
Or you must provide an argument to your linker allowing to have a function
defined multiple time ("-z muldefs" for GNU ld).

Example:
An application sends file over FTP and implements a retry procedure which must
be unit tested. Consider the following function sendFile (the target of the unit
test) which returns whether it succeed to send the file.

    /**
    * Try to send the provided file to some FTP server and return whether it
    * succeed or not.
    *
    * @param filePtr The pointer to the file object
    *
    * @return Whether the file has been sent
    */
    int sendFile (File_s* filePtr)
    {
        int bytesSent = 0;
        int totalBytesSent = 0;
        const int bytesToSend = filePtr->length;

        do {
            bytesSent = ftp_send(&(filePtr->content[bytesSent]), bytesToSend-totalBytesSent);

            totalBytesSent += bytesSent;
        } while (totalBytesSent < bytesToSend && bytesSent > 0);

        return totalBytesSent == bytesToSend;
    }

Where ftp_send is declared as (for example in ftp.h) :
    /**
    * Send the provided bytes over a FTP connection.
    *
    * @param content The content to send
    * @param length The length of the content
    *
    * @return The number of bytes sent
    */
    int ftp_send(const char* content, unsigned int length);

In this case, mockeur allows the developer to easily simulate the behavior of
ftp_send.

First the mock must be declared (it should be done once, for a whole
compilation unit):

    #include "ftp.h"

    Mock<int, const char*, unsigned int> mock_ftp_send; /* The mock object */

    int ftp_send(const char* content, unsigned int length)
    {
        return mock_ftp_send.value(content, length);
    }

Then, in the code of the test:

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

Features of mockeur:
- allow to mock functions with any number of arguments (uses C++11 variadic templates)
- easy to set a different behavior for each test (clear() method)
- easy implementation of "smart" behavior for a specific test (through the use of C++11 lambda functions)
- allow to check that a mock has been called with some specific arguments (through the use of argument matchers and the numberOfCalls method)
