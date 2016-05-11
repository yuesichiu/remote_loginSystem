/*************************************************************************
	> File Name: thread_function.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 07:52:33 PM CST
 ************************************************************************/

#ifndef _THREAD_FUNCTION_H
#define _THREAD_FUNCTION_H

/*
* 函数：out_addr 
* 函数功能：获取地址和端口
* 函数参数：sockaddr_in 类型变量
* 返回值：无
*/
extern void out_addr(struct sockaddr_in *clientaddr);

/*
* 函数：thrd_func 
* 函数功能：线程处理函数
* 函数参数：void指针
* 返回值：万有指针
*/
extern void* thrd_func(void *arg);

#endif
