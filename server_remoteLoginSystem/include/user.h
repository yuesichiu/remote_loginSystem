/*************************************************************************
	> File Name: user.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Wed 06 Apr 2016 01:55:02 PM CST
 ************************************************************************/

#ifndef _USER_H
#define _USER_H

/*
 * 函数名：compare_userId
 * 函数功能：比较用户ID是否一致
 * 函数参数：用户结构体， 指针
 * 函数返回值：一致返回0，不一致返回其它数
 * */
extern int compare_userId(void *elem1, void *elem2);


/*
 * 函数：user_regist
 * 函数功能：注册新用户
 * 函数参数：用户链表头指针
 * 返回值：成功返回1， 不成功返回-1
 * */
extern int user_regist(int fd);


/*
 * 函数：save_user
 * 函数功能：保存用户链表
 * 函数参数：链表头指针， 保存路径
 * 返回值：成功返回1， 不成功返回-1
 * */
extern int save_user(link_p user_head, char* path);


/*
 * 函数：load_user
 * 函数功能：读取用户链表
 * 函数参数：链表头指针， 保存路径
 * 返回值：成功返回1， 不成功返回-1
 * */
extern int load_user(link_p user_head, char* path);


/*
 * 函数：delete_user
 * 函数功能：删除用户
 * 函数参数：链表头指针
 * 返回值：void
 * */
extern void delete_user(link_p head);

/*
 * 函数：user_print
 * 函数功能：打印用户信息
 * 函数参数：结构体指针
 * 返回值：无
 * */
extern void user_print(void *value_elem);

/*
 * 函数：creat_newUserNode
 * 函数功能：创建新的用户结构体
 * 函数参数：用户结构体类型指针
 * 返回值：链表结构体指针
 * */
extern link_p creat_newUserNode(user_p new_user_p);
#endif
