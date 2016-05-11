/*************************************************************************
	> File Name: control.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 08:59:31 AM CST
 ************************************************************************/

#ifndef _CONTROL_H
#define _CONTROL_H

/*
* 函数：server_control
* 函数功能：服务器控制函数
* 函数参数：文件描述符
* 返回值：无
*/
extern void server_control(int fd);

/*
* 函数：control_cmd
* 函数功能：命令处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
extern void control_cmd(int fd, send_packet* recvPack);

/*
* 函数：control_login
* 函数功能：登录处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
extern void control_login(int fd, send_packet* recvPack);

/*
* 函数：control_regist
* 函数功能：注册处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
extern void control_regist(int fd, send_packet* recvPack);

/*
* 函数：control_heart
* 函数功能：心跳处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
extern void control_heart(int fd, send_packet* recvPack);

/*
* 函数：control_logExit
* 函数功能：退出登录
* 函数参数：文件描述符 
* 返回值：无
*/
extern void control_logExit(int fd);

/*
* 函数：control_onlineSearch
* 函数功能：查找在线好友
* 函数参数：文件描述符 
* 返回值：无
*/
extern void control_onlineSearch(int fd);

/*
* 函数：control_singleChat
* 函数功能：单聊处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
extern void control_singleChat(int fd, send_packet *recvPack);

/*
* 函数：control_groupChat
* 函数功能：群聊处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
extern void control_groupChat(int fd, send_packet *recvPack);

/*
* 函数：control_cliErr
* 函数功能：客户端非正常退出处理
* 函数参数：文件描述符
* 返回值：无
*/
extern void control_cliErr(int fd);

#endif
