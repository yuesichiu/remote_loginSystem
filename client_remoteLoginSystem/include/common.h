/*************************************************************************
  > File Name: common.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Wed 06 Apr 2016 09:00:17 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

/*
 * 函数名：get_name
 * 函数功能：从标准输入得到用户名，拷贝到以参数为首地址的数组
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
extern int get_name(char *username);


/*
 * 函数名：get_passwd
 * 函数功能：从标准输入得到密码，拷贝到以参数为首地址的数组
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
extern int get_passwd(char *passwd);


/*
 * 函数名：get_newPasswd
 * 函数功能：注册时得到新密码
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
extern int get_newPasswd(char *passwd);


/*
 * 函数名：get_passwdThree
 * 函数功能：得到输入密码，输入次数不超过三次
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
extern int get_passwdThree(char *passwd);


/*
 * 函数名：print_int
 * 函数功能：打印int型值
 * 函数参数：字符串指针，int型指针
 * 函数返回值：无
 * */
extern void print_int(char *str, int *elem);

/*
 * 函数名：get_int
 * 函数功能：得到int型变量
 * 函数参数：字符串首地址， 打印的值的地址， 最小最大范围
 * 函数返回值：无
 * */
extern void get_int(char *str, int *value, int min, int max);

#endif
