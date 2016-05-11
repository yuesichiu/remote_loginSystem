/*************************************************************************
	> File Name: control.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 08:59:31 AM CST
 ************************************************************************/

#ifndef _CONTROL_H
#define _CONTROL_H

/*
* 函数名称：main_menu_control
* 函数功能：主菜单控制函数
* 函数参数：sockfd
* 函数返回值：无
* */
extern void main_menu_control(int sockfd);

/*
* 函数名称：chatRoom_menu_control
* 函数功能：聊天室菜单控制函数
* 函数参数：sockfd
* 函数返回值：无
* */
extern void chatRoom_menu_control(int sockfd);

/*
* 函数名称：regist
* 函数功能：注册
* 函数参数：sockfd
* 函数返回值：无
* */
extern void regist(int sockfd);
    
/*
* 函数名称：logout
* 函数功能：退出登录
* 函数参数：sockfd
* 函数返回值：无
* */
void logout(int sockfd);
/*
* 函数名称：login
* 函数功能：登录
* 函数参数：sockfd
* 函数返回值：无
* */
extern void login(int sockfd);

/*
* 函数名称：send_comnd
* 函数功能：向客户端发送命令
* 函数参数：sockfd
* 函数返回值：无
* */
extern void send_comnd(int sockfd);

/*
* 函数名称：singleChat
* 函数功能:一对一聊天
* 函数参数：无
* 函数返回值：无
* */
extern void singleChat();

/*
* 函数名称：groupChat
* 函数功能：群聊
* 函数参数：无
* 函数返回值：无
* */
extern void groupChat();

/*
* 函数名称：online_search
* 函数功能：查询在线好友
* 函数参数：无
* 函数返回值：无
* */
extern void online_search();

#endif
