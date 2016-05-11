/*************************************************************************
	> File Name: vector_fd.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Fri 06 May 2016 03:02:16 PM CST
 ************************************************************************/

#ifndef _VECTOR_FD_H
#define _VECTOR_FD_H

typedef struct Vector_fd{
    int *fd;
    int counter; //fd数量
    int max_counter;//数组大小
}vector_fd;

/*
* 函数：create_vector_fd
* 函数功能：创建数组
* 函数参数：无
* 返回值:数组首地址
*/
extern vector_fd* create_vector_fd(void);

/*
* 函数：destroy_vector_fd
* 函数功能：销毁数组
* 函数参数：vfd
* 返回值:无
*/
extern void destroy_vector_fd(vector_fd * vfd);

/*
* 函数：get_fd
* 函数功能：找数组下标
* 函数参数：vfd 要找的下标index
* 返回值:要找的fd
*/
extern int get_fd(vector_fd *, int index);

/*
* 函数：remove_fd
* 函数功能：找数组下标
* 函数参数：vfd fd
* 返回值:数组里的数量
*/
extern void remove_fd(vector_fd *, int fd);

/*
* 函数：add_fd
* 函数功能：找数组下标
* 函数参数：vfd fd
* 返回值:无
*/
extern void add_fd(vector_fd *, int fd);

#endif
