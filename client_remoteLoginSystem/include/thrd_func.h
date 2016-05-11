/*************************************************************************
	> File Name: thrd_func.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Sun 08 May 2016 05:14:12 PM CST
 ************************************************************************/

#ifndef _THRD_FUNC_H
#define _THRD_FUNC_H

/*
* 函数名称：sigleSucc
* 函数功能：单聊在线检测成功处理
* 函数参数：无
* 函数返回值：无
* */
extern void* thrd_func(void* arg);

/*
* 函数名称：recv_heart
* 函数功能：心跳包处理
* 函数参数：无
* 函数返回值：无
* */
extern void recv_heart();

/*
* 函数名称：recv_online
* 函数功能：打印在线好友
* 函数参数：recvPack
* 函数返回值：无
* */
extern void recv_online(send_packet recvPack);

/*
* 函数名称：recv_singleChat
* 函数功能：单聊数据处理
* 函数参数：无
* 函数返回值：无
* */
extern void recv_singleChat(send_packet recvPack);

/*
* 函数名称：recv_notOnLine
* 函数功能：单聊在线检测失败处理
* 函数参数：无
* 函数返回值：无
* */
extern void recv_notOnLine();

/*
* 函数名称：recv_groupChat
* 函数功能：群聊数据包处理
* 函数参数：recvPack 
* 函数返回值：无
* */
extern void recv_groupChat(send_packet recvPack);

/*
* 函数名称：sigleSucc
* 函数功能：单聊在线检测成功处理
* 函数参数：无
* 函数返回值：无
* */
extern void sigleSucc();

/*
* 函数名称：sigleFail
* 函数功能：单聊姓名检测失败处理
* 函数参数：无
* 函数返回值：无
* */
extern void sigleFail();
#endif
