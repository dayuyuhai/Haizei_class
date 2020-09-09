/*************************************************************************
	> File Name: haizei/linklist.h
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 18 Jun 2020 07:44:50 PM CST
 ************************************************************************/

#ifndef __HAIZEI_LINKLIST_H
#define __HAIZEI_LINKLIST_H

#define offset(T, name) ((long long)(&(((T *)(0))->name)))

#define Head(p, T, name) ((T *)(((char *)p) - offset(T, name)))


struct LinkNode {
	struct LinkNode *next;
};

#endif
