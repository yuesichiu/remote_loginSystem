/*************************************************************************
	> File Name: struct.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 02:13:57 PM CST
 ************************************************************************/

#ifndef _STRUCT_H
#define _STRUCT_H
typedef struct User_link{
    char name[NUM];
    char passwd[NUM];
    char ip[20];
    time_t linkTime;
    int  fd;
    int online_flag;
}user_n, *user_p;

typedef struct User_account{
    char name[NUM];
    char passwd[NUM];
}user_save;

typedef struct Send_packet{
    char data[2048];
    int data_type;
    int size;
    char user_name[NUM]; 
    char chat_name[NUM];
    char user_passwd[NUM];
}send_packet;

#endif
