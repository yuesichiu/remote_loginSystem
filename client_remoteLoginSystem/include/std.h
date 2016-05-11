/*************************************************************************
	> File Name: std.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 08:51:50 AM CST
 ************************************************************************/

#ifndef _STD_H
#define _STD_H

//-------------------自定义宏------------------------------------------//

//清标准输入缓存区
#define CLEAN_BUFF {\
    int ch = 0;\
    while((ch = getchar()) != '\n'\
    && ch != EOF);\
}

//按任意键继续
#define WAIT {\
    printf(YELLOW"\n---按回车键继续！---\n"NONE);\
    getchar();\
}

//颜色配置
#define     NONE              "\033[m"
#define     RED               "\033[0;32;31m"
#define     LIGHT_RED         "\033[1;31m"
#define     UNDER_LINE        "\033[4m"
#define     GREEN             "\033[0;32;32m"
#define     YELLOW            "\033[1;33m"

//协议包数据类型
#define TYPE_LOGIN  0  //登录数据包
#define TYPE_REG    1  //注册数据包 
#define TYPE_MSG    2  //消息数据包 
#define TYPE_HEART  3  //心跳数据包 
#define TYPE_CMD    4  //命令数据包 
#define TYPE_ONLINE 5  //查看在线用户 
#define TYPE_EXIT   6  //退出数据包
#define TYPE_ERR    7  //出错数据包
#define TYPE_OK     8  //正常数据包
#define TYPE_CHECK  9  //检查数据包
#define TYPE_CHAT   10 //单聊数据包
#define TYPE_REGSUC 11 //注册成功数据包
#define TYPE_LOGSUC 12 //登录成功数据包
#define TYPE_REGERR 13 //注册失败数据包
#define TYPE_LOGERR 14 //登录失败数据包
#define TYPE_LOGRE  15 //重复登录数据包
#define TYPE_NOTONLINE 16 //不在线提示数据包
#define TYPE_GROUPCHAT 17 //群聊数据包
#define TYPE_SIGSUC 18    //单聊可找到名字
#define TYPE_SIGFAI 19    //单聊不可找到名字
#define TYPE_SIGDATA 20   //聊天内容数据包
#define TYPE_CLIERR  21   //客户端非正常关闭

#define NUM 30  //密码和名字长度
//-------------------标准头文件--------------------------------------//
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>

//-------------------自定义头文件------------------------------------//
#include "struct.h"
#include "control.h"
#include "link.h"
#include "common.h"
#include "thrd_func.h"
#include "mainFile_func.h"
#include "view.h"

//-------------------全局变量------------------------------------//
int sockfd;
time_t client_time;

#endif
