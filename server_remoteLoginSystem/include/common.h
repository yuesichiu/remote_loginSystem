/*************************************************************************
  > File Name: common.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Wed 06 Apr 2016 09:00:17 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

/*
 * 函数名：print_int
 * 函数功能：打印int型值
 * 函数参数：字符串指针，int型指针
 * 函数返回值：无
 * */
extern void print_int(char *str, int *elem);

/*
 * 函数名：get_ip
 * 函数功能：根据文件描述符得到ip
 * 函数参数：文件描述符， 存放结果的字符串指针
 * 函数返回值：无
 * */
extern void get_ip(int fd, char* des_ip);

/*
 * 函数名：searchStruct_fd
 * 函数功能：根据文件描述符得到结构体
 * 函数参数：文件描述符
 * 函数返回值：成功返回结构体指针，失败返回NULL
 * */
extern link_p searchStruct_fd(int fd);

/*
 * 函数名：getNameByFd
 * 函数功能：根据文件描述符得到名字
 * 函数参数：文件描述符， 字符串指针
 * 函数返回值:无
 * */
extern void getNameByFd(int fd, char* name);

#endif
