/*************************************************************************
	> File Name: remote_loginSystem.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 09:05:57 AM CST
 ************************************************************************/

#include "std.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("usage: %s ip port\n", argv[0]);
        exit(1);
    }

//------------------------------更新client_time全局变量--------------------//
    client_time = time(NULL);

//------------------------------捕捉信号-----------------------------------//
    signal(SIGALRM, alarm_handler);
    signal(SIGPIPE, pipe_handler);
    signal(SIGINT, sigint_handler);

//------------------------------连接服务器---------------------------------//
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("socket error!\n");
        exit(1);
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1],&serveraddr.sin_addr.s_addr);

    if(connect(sockfd, (struct sockaddr*)&serveraddr,
               sizeof(serveraddr)) < 0){
        perror("connect error!\n");           
        exit(1);
    }

//------------------------------进入主菜单控制函数------------------------//
    main_menu_control(sockfd); 

    return 0;
}
