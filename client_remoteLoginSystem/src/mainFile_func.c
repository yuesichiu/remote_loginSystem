/*************************************************************************
	> File Name: mainFile_func.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Sat 07 May 2016 05:08:06 PM CST
 ************************************************************************/

#include "std.h"

/*
* 函数名称：alarm_handler
* 函数功能：alarm信号处理函数
* 函数参数：无
* 函数返回值：无
* */
void alarm_handler(){
    send_packet sendPack;
    sendPack.data_type = 3;
    //int flag = -1;
    write(sockfd, &sendPack, sizeof(sendPack));
//    printf("heart return:%d\n", flag); 
    alarm(5);
}

/*
* 函数名称：pipe_handler
* 函数功能：pipe信号处理函数
* 函数参数：无
* 函数返回值：无
* */
void pipe_handler(){
    printf("服务器崩溃！客户端安全退出！\n");
    WAIT;
    close(sockfd);
    exit(0);
}

/*
* 函数名称：sigint_handler
* 函数功能：sigint信号处理函数
* 函数参数：无
* 函数返回值：无
* */
void sigint_handler(){
    printf("客户端非正常关闭！\n"); 
    send_packet sendPack;
    sendPack.data_type = TYPE_CLIERR;
    write(sockfd, &sendPack, sizeof(sendPack));
    close(sockfd);
    exit(0);
}
