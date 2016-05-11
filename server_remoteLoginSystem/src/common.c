/*************************************************************************
	> File Name: common.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Wed 06 Apr 2016 08:58:46 PM CST
 ************************************************************************/

#include "std.h"

/*
 * 函数名：print_int
 * 函数功能：打印int型值
 * 函数参数：字符串指针，int型指针
 * 函数返回值：无
 * */
void print_int(char *str, int *elem){
    if(NULL == str || NULL == elem){
        printf("The point is NULL !\n");
        return;
    }

    printf(GREEN"%s %d\n"NONE, str, *elem);
 }

/*
 * 函数名：get_ip
 * 函数功能：根据文件描述符得到ip
 * 函数参数：文件描述符， 存放结果的字符串指针
 * 函数返回值：无
 * */
void get_ip(int fd, char* des_ip){
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr); 
    if(getpeername(fd,(struct sockaddr*)&addr, &len) < 0){
        perror("getpeername error\n");
        return;
    }
    char ip[16];
    memset(ip, 0, sizeof(ip));
    //int port = ntohs(addr.sin_port);
    inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, sizeof(ip));
    strcpy(des_ip, ip); 
    //printf("%16s(%5d) \n", ip, port);
}

/*
 * 函数名：searchStruct_fd
 * 函数功能：根据文件描述符得到结构体
 * 函数参数：文件描述符
 * 函数返回值：成功返回结构体指针，失败返回NULL
 * */
link_p searchStruct_fd(int fd){
    link_p curr_head = user_head->next;
    while(curr_head != user_head){
        if(((user_p)curr_head->value_p)->fd == fd){
            return curr_head;
        }
        curr_head = curr_head->next;
    }

    return NULL;
}

/*
 * 函数名：getNameByFd
 * 函数功能：根据文件描述符得到名字
 * 函数参数：文件描述符， 字符串指针
 * 函数返回值:无
 * */
void getNameByFd(int fd, char* name){
    assert(NULL != name);

    link_p curr_head = user_head->next;
    while(curr_head != user_head){
        if(((user_p)curr_head->value_p)->fd == fd){
            strcpy(name, ((user_p)curr_head->value_p)->name);
            return;
        }
        curr_head = curr_head->next;
    }

}
