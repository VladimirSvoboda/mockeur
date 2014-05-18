/*
 * (c) Copyright 2013-2014 Vladimir Svoboda
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

/**
 * @file FtpClient.hpp
 * @brief This file contains the interface of a FTP client which is used for
 *        unit test purpose.
 */

#ifndef FTPCLIENT_H_
#define FTPCLIENT_H_

typedef struct
{
    const char* content;
    unsigned int length;
} File_s;

/**
 * Data representation model defined in FTP
 */
enum DataModel
{
    ASCII,
    BINARY,
    EBCDIC,
    LOCAL
};

/**
 * Send the provided bytes over a FTP connection.
 * Important: this function will be mocked.
 *
 * @param content The content to send
 * @param length The length of the content
 *
 * @return The number of bytes sent
 */
int ftp_send(const char* content, unsigned int length);

/**
 * Return the data model currently use to send data
 *
 * @return The data model currently use to send data
 */
enum DataModel ftp_getDataModel(void);

/**
 * Set the data model to use for further transfer.
 *
 * @param dataModel The data model to use
 */
void ftp_setDataModel(enum DataModel dataModel);

/**
 * Try to send the provided file to some FTP server and return whether it
 * succeed or not.
 *
 * @param filePtr The pointer to the file object
 *
 * @return Whether the file has been sent
 */
int sendFile (File_s* filePtr);

#endif /* FTPCLIENT_H_ */
