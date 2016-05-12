/*************************************************************************
	> File Name: remote_loginSystem.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 09:05:57 AM CST
 ************************************************************************/

#include "std.h"

int main(){
    //------------------------初始化锁----------------------------------//
    pthread_mutex_init(&mutex, NULL);

    //------------------------绑定信号处理函数--------------------------//
    signal(SIGALRM, alarm_handler);
    signal(SIGINT, sigint_handler);

    //------------------------创建并从文件读取链表----------------------//
    user_head = creat_link(sizeof(user_n)); 
    if(NULL == user_head){
        printf("The point is NULL !\n");
        return 0;
    }

    int flag = -1;
    flag = load_link(user_head, FILE_PATH, load_user);
    if(-1 == flag){
        printf("Read file fail !\n");
        return -1;
    }

    //------------------------打开日志文件------------------------------//
    fp_log = fopen("log", "a");
    if(NULL == fp_log){
        printf("open error!\n");
        exit(0);
    }
    
    //------------------------读取配置文件------------------------------//
    FILE* fp;
    fp = fopen("config.txt", "r");
    if(NULL == fp){
        printf("open error!\n");
        exit(0);
    }

    char ip[20]= ""; 
    char port[10] = "";
    fscanf(fp, "ERVER_IP = %s\nPORT = %s", ip, port);
    fclose(fp);
    //------------------------绑定ip并且进行监听------------------------//
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int ret;
    int opt = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 
    if(ret < 0){
        perror("setsockopt error!\n"); 
        exit(1);
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(port));
    serveraddr.sin_addr.s_addr = inet_addr(ip);
    if(bind(sockfd, (struct sockaddr*)&serveraddr, 
            sizeof(serveraddr)) < 0){
        perror("bind error!\n"); 
        exit(1);
    }

    if(listen(sockfd, 10) < 0){
        perror("listen error!\n");
        exit(1);
    }

   
    //------------------------创键fd动态数组----------------------------//
    vfd = create_vector_fd();

    //------------------------以分离属性创建线程------------------------//
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t th;
    int pthrd_creaErr;
    if((pthrd_creaErr = pthread_create(&th, &attr, thrd_func, (void*)0)) != 0){
        perror("pthread create error!\n");
        exit(1);
    }
    pthread_attr_destroy(&attr);

    //------------------------定时器开启------------------------//
    alarm(1);

    //------------------------主控线程把接收的客户端fd放入动态数组------------------------//
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);

    while(1){
        int fd = accept(sockfd,
        (struct sockaddr*)&clientaddr, &clientaddr_len);
        if(fd < 0){
            perror("accept error!\n");
            continue;
        }

        out_addr(&clientaddr);
        add_fd(vfd, fd);
    }
    return 0;
}
