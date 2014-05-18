/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file FtpClient.c
 * @brief Implementation of high level functions of the FTP client (the
 *        functions which will not be mocked).
 */

#include "FtpClient.h"

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
