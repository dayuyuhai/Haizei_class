/*************************************************************************
	> File Name: popen_head.h
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Aug 2020 02:48:44 PM CST
 ************************************************************************/

#ifndef _POPEN_HEAD_H
#define _POPEN_HEAD_H

FILE *m_popen(const char *cmd, const char *type);
int m_pclose(FILE *fp);

#endif
