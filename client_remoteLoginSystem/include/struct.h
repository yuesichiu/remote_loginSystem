/*************************************************************************
	> File Name: struct.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 11:27:30 AM CST
 ************************************************************************/

#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct Send_packet{
    char data[2048];
    int data_type;
    int size;
    char user_name[NUM]; 
    char chat_name[NUM];
    char user_passwd[NUM];
}send_packet;

#endif
