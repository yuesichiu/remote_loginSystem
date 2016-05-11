/*************************************************************************
	> File Name: thread_function.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 07:52:00 PM CST
 ************************************************************************/

#include "std.h"

/*
* 函数：add_set 
* 函数功能：初始化文件描述符集
* 函数参数：文件描述符集
* 返回值：数值最大的描述符
*/
static int add_set(fd_set *set){
    FD_ZERO(set);//清除一个文件描述符集
    int max_fd = vfd->fd[0];
    int i = 0;
    for(; i < vfd->counter; i++){
        int fd = get_fd(vfd, i);//从动态数组中得到描述符
        if(fd > max_fd){
            max_fd = fd;
        }
        FD_SET(fd, set);//将一个文件描述符加入到文件描述符集中
    }
    return max_fd;
}

/*
* 函数：out_addr 
* 函数功能：获取地址和端口
* 函数参数：sockaddr_in 类型变量
* 返回值：无
*/
void out_addr(struct sockaddr_in *clientaddr){
    int port = ntohs(clientaddr->sin_port);
    char ip[16];
    memset(ip, 0, sizeof(ip));
    inet_ntop(AF_INET, 
              &clientaddr->sin_addr.s_addr, ip, sizeof(ip));
    printf("client: %s(%d) connected\n", ip, port);

}

/*
* 函数：thrd_func 
* 函数功能：线程处理函数
* 函数参数：void指针
* 返回值：万有指针
*/
void* thrd_func(void *arg){
    struct timeval t;
    t.tv_sec = 2;//select等待的时间
    t.tv_usec = 0;
    int n = 0;
    int maxfd;
    fd_set set;//建新的描述符集
    maxfd = add_set(&set);//填充

    while(1){
        n = select(maxfd + 1, &set, NULL, NULL, &t);
        if(n > 0){
            int i = 0;
            for(; i < vfd->counter; i++){
                int fd = get_fd(vfd, i);
                if(FD_ISSET(fd, &set)){//检测哪些描述符准备好
                    server_control(fd);//处理描述符
                }
            }
        }        
        t.tv_sec = 2;
        t.tv_usec = 0;

        maxfd = add_set(&set);//再次载入
    }


    return (void*)0;
}
