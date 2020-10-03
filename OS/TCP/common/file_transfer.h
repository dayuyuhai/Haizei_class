/*************************************************************************
	> File Name: file_transfer.h
	> Author: 
	> Mail: 
	> Created Time: Fri 18 Sep 2020 06:55:54 PM CST
 ************************************************************************/

#ifndef _FILE_TRANSFER_H
#define _FILE_TRANSFER_H

void send_file(const char *filename, int sockfd);
void recv_file(int sockfd);
#endif
