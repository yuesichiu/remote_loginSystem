/*************************************************************************
	> File Name: main_func.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Sun 08 May 2016 11:38:37 PM CST
 ************************************************************************/

#include "std.h"

/*
* 函数：alarm_handler 
* 函数功能：定时器处理函数
* 函数参数：无
* 返回值：无
*/
void alarm_handler(){
    link_p curr_head = user_head->next;
    time_t curr_time = time(NULL);

    alarm(1);
    while(curr_head != user_head){
        if(1 == ((user_p)(curr_head->value_p))->online_flag && 
           curr_time - ((user_p)(curr_head->value_p))->linkTime > 15){
            fprintf(fp_log, "%s%s die!\n", ctime(&curr_time), ((user_p)(curr_head->value_p))->name);
            remove_fd(vfd, ((user_p)curr_head->value_p)->fd);
            ((user_p)curr_head->value_p)->fd = -1;  
            ((user_p)curr_head->value_p)->online_flag = 0;
            ((user_p)curr_head->value_p)->linkTime = 0;
            memset(((user_p)curr_head->value_p)->ip, 0, sizeof(((user_p)curr_head->value_p)->ip));
        }
        curr_head = curr_head->next;
    }
}

/*
* 函数：sigint_handler 
* 函数功能：sigint信号处理函数
* 函数参数：无
* 返回值：无
*/
void sigint_handler(){
    printf("服务器非正常退出！\n");
    save_link(user_head, FILE_PATH, save_user);
    destroy_link(user_head);
    destroy_vector_fd(vfd);
    user_head = NULL;
    close(sockfd);
    fclose(fp_log);
    exit(1);
}
