mockeur
=======

A C++ mocking library for C code (hence, not using classes).
The main purpose of the library is to allow the developer to simulate the
behavior of a deep layer of the code in order to write its unit tests.

Important note:
The "real" code of the mocked function must not be compiled in the unit tests in
order to avoid the error: function already defined.

Example:
An application sends file over FTP and implements a retry procedure which must
be unit tested. Consider the following function sendFile (the target of the unit
test) which returns the number of retry which was needed to send the file.

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

Where ftp_send is declared in the file "ftp.h" as:
int ftp_send(const char*, unsigned int);

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

Features of mockeur:
- allow to mock functions with any number of arguments (uses C++11 variadic templates)
- easy to set a different behavior for each test (clear() method)
- easy implementation of "smart" behavior for a specific test (through the use of C++11 lambda functions)
- allow to check that a mock has been called with some specific arguments (through the use of argument matchers and the numberOfCalls method)

