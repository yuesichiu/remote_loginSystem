/*************************************************************************
	> File Name: thrd_func.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Sun 08 May 2016 05:13:31 PM CST
 ************************************************************************/

#include "std.h"

/*
* 函数名称：thrd_func
* 函数功能：客户端的自线程函数，接收数据包
* 函数参数：文件描述符
* 函数返回值：无
* */
void* thrd_func(void* arg){
    client_time = time(NULL);
    alarm(5);
    int fd = *(int*)arg;
    send_packet recvPack;
    while(1){
        if(time(NULL) - client_time > 15){
            printf("%d-%d\n", (int)time(NULL), (int)client_time);
            printf(RED"您已下线，请重新登录！\n"NONE);
            WAIT;
        }
        memset(&recvPack, 0, sizeof(recvPack));
        int flag = read(fd, &recvPack, sizeof(recvPack));
        if(flag <= 0){
            continue;
        }
        printf("---client thrd_fund type: %d\n", recvPack.data_type);
        switch(recvPack.data_type){
            case TYPE_HEART:
                recv_heart();
                break;
            case TYPE_ONLINE:
                recv_online(recvPack);
                break;
            case TYPE_CHAT:
                recv_singleChat(recvPack);
                break;
            case TYPE_NOTONLINE:
                recv_notOnLine();
                break;
            case TYPE_GROUPCHAT:
                recv_groupChat(recvPack);
                break;
            case TYPE_SIGSUC:
                sigleSucc();
                break;
            case TYPE_SIGFAI:
                sigleFail();
                break;
            default:
            {
                if(strlen(recvPack.data) > 0){
                    printf(GREEN"命令执行结果：\n%s\n"NONE, recvPack.data);
                    printf(YELLOW"请输入命令:\n"NONE);
                }else{
                    printf("unknown type!\n");
                    //WAIT;
                }
                break;
            }
        }
    }
    return (void*)0;
}

/*
* 函数名称：sigleSucc
* 函数功能：单聊在线检测成功处理
* 函数参数：无
* 函数返回值：无
* */
void sigleSucc(){
    printf(YELLOW"请输入聊天内容(输入exit退出)：\n"NONE);
}

/*
* 函数名称：sigleFail
* 函数功能：单聊姓名检测失败处理
* 函数参数：无
* 函数返回值：无
* */
void sigleFail(){
    printf(RED"好友不存在！输入exit退出！\n"NONE);    
}

/*
* 函数名称：recv_groupChat
* 函数功能：群聊数据包处理
* 函数参数：recvPack 
* 函数返回值：无
* */
void recv_groupChat(send_packet recvPack){
   printf(GREEN"%s 发来群聊信息： %s\n"NONE, recvPack.chat_name, recvPack.data); 
}

/*
* 函数名称：recv_notOnLine
* 函数功能：单聊在线检测失败处理
* 函数参数：无
* 函数返回值：无
* */
void recv_notOnLine(){
    printf(RED"您要私聊的好友不在线, 输入exit退出！"NONE);
}

/*
* 函数名称：recv_singleChat
* 函数功能：单聊数据处理
* 函数参数：无
* 函数返回值：无
* */
void recv_singleChat(send_packet recvPack){
   printf(GREEN"%s 发来私聊信息： %s\n"NONE, recvPack.chat_name, recvPack.data); 
}

/*
* 函数名称：recv_online
* 函数功能：打印在线好友
* 函数参数：recvPack
* 函数返回值：无
* */
void recv_online(send_packet recvPack){
    printf(GREEN"%s\t"NONE, recvPack.chat_name);     
    fflush(stdout);
}

/*
* 函数名称：recv_heart
* 函数功能：心跳包处理
* 函数参数：无
* 函数返回值：无
* */
void recv_heart(){
    client_time = time(NULL);
}

