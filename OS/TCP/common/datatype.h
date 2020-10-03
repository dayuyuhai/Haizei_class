/*************************************************************************
	> File Name: datatype.h
	> Author: 
	> Mail: 
	> Created Time: Fri 18 Sep 2020 06:54:45 PM CST
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H

struct FileMsg {
    char name[512];
    long size;
    char buff[4096];
};

#endif
