/*************************************************************************
	> File Name: include/linknode.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Mar 2021 11:58:34 AM CST
 ************************************************************************/

#ifndef _INCLUDELINKNODE_H
#define _INCLUDELINKNODE_H

#define offset(type, member) ((long long)(&(((type *)(0))->member)))
#define Head(type, member) ((type *)(((char *)member) - offset(type, member)))

struct LinkNode {
    struct LinkNode *next;
};
#endif
