/*************************************************************************
	> File Name: vector_fd.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Fri 06 May 2016 03:02:51 PM CST
 ************************************************************************/

#include "std.h"

/*
* 函数：expand_capacity
* 函数功能：扩展数组
* 函数参数：vfd
* 返回值:无
*/
static void expand_capacity(vector_fd *vfd){
    if(vfd->counter >= vfd->max_counter){
        int *fds = (int*)calloc(vfd->counter + 5, sizeof(int));
        assert(fds != NULL);
        memcpy(fds, vfd->fd, sizeof(int) * vfd->counter);
        free(vfd->fd);
        vfd->fd = fds;
        vfd->max_counter += 5;
    }
}

/*
* 函数：indexof
* 函数功能：找数组下标
* 函数参数：vfd fd
* 返回值:下标，不成功返回-1
*/
static int indexof(vector_fd *vfd, int fd){
    int i = 0;
    for(; i < vfd->counter; i++){
        if(vfd->fd[i] == fd){
            return i;
        }
    }

    return -1;
}

/*
* 函数：create_vector_fd
* 函数功能：创建数组
* 函数参数：无
* 返回值:数组首地址
*/
vector_fd* create_vector_fd(void){
    vector_fd *vfd = (vector_fd*)calloc(1, sizeof(vector_fd));
    assert(vfd != NULL);
    vfd->fd = (int*)calloc(5, sizeof(int));
    assert(vfd->fd != NULL);
    vfd->counter = 0;
    vfd->max_counter = 0;
    return vfd;
}

/*
* 函数：destroy_vector_fd
* 函数功能：销毁数组
* 函数参数：vfd
* 返回值:无
*/
void destroy_vector_fd(vector_fd* vfd){
    assert(vfd != NULL);
    free(vfd->fd);
    free(vfd);
}

/*
* 函数：add_fd
* 函数功能：找数组下标
* 函数参数：vfd fd
* 返回值:无
*/
void add_fd(vector_fd *vfd, int fd){
    assert(vfd != NULL);
    expand_capacity(vfd);
    vfd->fd[vfd->counter++] = fd;
}

/*
* 函数：get_fd
* 函数功能：找数组下标
* 函数参数：vfd 要找的下标index
* 返回值:要找的fd
*/
int get_fd(vector_fd *vfd, int index){
    assert(vfd != NULL);
    if(index < 0 || index > vfd->counter - 1){
        return 0;
    }

    return vfd->fd[index];
}

/*
* 函数：remove_fd
* 函数功能：找数组下标
* 函数参数：vfd fd
* 返回值:数组里的数量
*/
void remove_fd(vector_fd *vfd, int fd){
    assert(vfd != NULL);
    int index = indexof(vfd, fd);
    if(-1 == index){
        return;
    }
    int i = index;
    for(; i < vfd->counter - 1; i++){
        vfd->fd[i] = vfd->fd[i + 1];
    }
    vfd->counter--;
}
