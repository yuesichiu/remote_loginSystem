/*************************************************************************
	> File Name: view.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 08:56:59 AM CST
 ************************************************************************/

#include "std.h"

/*
* 函数名称：main_menu
* 函数功能：客户端主菜单
* 函数参数：无
* 函数返回值：无
* */
void main_menu(){
    printf(GREEN"         * 客 户 端 *             \n");
    printf("-----------------------------\n\n");
    printf("           1.注册                 \n");
    printf("           2.登录                 \n");
    printf("           0.退出                 \n\n");
    printf("-----------------------------\n"NONE);
    printf(YELLOW"请选择：\n"NONE);
} 

/*
* 函数名称：chatRoom_menu
* 函数功能：客户端聊天菜单
* 函数参数：无
* 函数返回值：无
* */
void chatRoom_menu(){
    printf(GREEN"        * 聊 天 室 *           \n");
    printf("-----------------------------\n\n");
    printf("     1.向服务器发送命令     \n");
    printf("     2.单聊                 \n");
    printf("     3.群聊                 \n");
    printf("     4.查询在线好友         \n");
    printf("     0.退出聊天室           \n\n");
    printf("----------------------------\n"NONE);
    printf(YELLOW"请选择：\n"NONE);
}

