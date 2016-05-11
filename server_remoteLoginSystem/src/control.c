/*************************************************************************
	> File Name: control.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 08:57:48 AM CST
 ************************************************************************/

#include "std.h"

/*
* 函数：server_control
* 函数功能：服务器控制函数
* 函数参数：文件描述符
* 返回值：无
*/
void server_control(int fd){
    send_packet recvPack;
    memset(&recvPack,0,sizeof(recvPack));
    int flag = -1;
    flag = read(fd, &recvPack, sizeof(recvPack));
    if(flag <= 0){
        return;
    }
    printf("server rcv type: %d\n", recvPack.data_type);
    switch(recvPack.data_type){
        case TYPE_LOGIN:
            control_login(fd, &recvPack);
            break;
        case TYPE_CLIERR:
            control_cliErr(fd);
            break;
        case TYPE_REG:
            control_regist(fd, &recvPack);
            break;
        case TYPE_CMD:
            control_cmd(fd, &recvPack);
            break;
        case TYPE_HEART:
            control_heart(fd, &recvPack);
            break;
        case TYPE_ONLINE:
            control_onlineSearch(fd);
            break;
        case TYPE_GROUPCHAT:
            control_groupChat(fd, &recvPack);
            break;
        case TYPE_EXIT:
            control_logExit(fd);
            break; 
        case TYPE_CHAT:
            control_singleChat(fd, &recvPack);
            break;
        default:
            printf("unknown type!\n");
            break;
    }
   return; 
}

/*
* 函数：control_cliErr
* 函数功能：客户端非正常退出处理
* 函数参数：文件描述符
* 返回值：无
*/
void control_cliErr(int fd){
    link_p goal_struct = searchStruct_fd(fd);
    if(NULL == goal_struct){
        return;
    }
    user_p goal_node = ((user_p)goal_struct->value_p); 
    goal_node->linkTime = 0;
    goal_node->fd = -1;
    goal_node->online_flag = 0;
    memset(goal_node->ip, 0, sizeof(goal_node->ip));
    time_t curr_time = time(NULL);
    fprintf(fp_log, "%s%s非正常退出！\n", ctime(&curr_time), goal_node->name);
    close(fd);
    remove_fd(vfd, fd); 
}

/*
* 函数：control_groupChat
* 函数功能：群聊处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
void control_groupChat(int fd, send_packet *recvPack){
    assert(NULL != recvPack);

    link_p curr_head = user_head->next;
    printf("group chat: %s---\n", recvPack->data);
    send_packet sendPack;
    memset(&sendPack, 0, sizeof(sendPack));
    while(curr_head != user_head){
        if(1 == ((user_p)(curr_head->value_p))->online_flag){
            if(fd == ((user_p)(curr_head->value_p))->fd){
                curr_head = curr_head->next;
                continue;
            }else{
                int fd_des = ((user_p)(curr_head->value_p))->fd;
                getNameByFd(fd, sendPack.chat_name);
                strcpy(sendPack.data, recvPack->data);
                sendPack.data_type = TYPE_GROUPCHAT;
                write(fd_des, &sendPack, sizeof(sendPack));
            }
        } 
        curr_head = curr_head->next;
    }
}

/*
* 函数：control_singleChat
* 函数功能：单聊处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
void control_singleChat(int fd, send_packet *recvPack){
    assert(NULL != recvPack);

    link_p curr_head = user_head->next;
    printf("signal chat: %s---\n", recvPack->chat_name);
    send_packet sendPack;
    memset(&sendPack, 0, sizeof(sendPack));
    while(curr_head != user_head){
        if(0 == strcmp(((user_p)(curr_head->value_p))->name, 
                       recvPack->chat_name)){
            if(0 == ((user_p)(curr_head->value_p))->online_flag){
                sendPack.data_type = TYPE_NOTONLINE;
            }else{
                int fd_des = ((user_p)(curr_head->value_p))->fd;
                getNameByFd(fd, sendPack.chat_name);
                strcpy(sendPack.data, recvPack->data);
                sendPack.data_type = TYPE_CHAT;
                int flag = -1;
                flag = write(fd_des, &sendPack, sizeof(sendPack));
                printf("---sig---%d---\n", flag);
                sendPack.data_type = TYPE_SIGSUC;
            }
            write(fd, &sendPack, sizeof(sendPack));
            return;
        } 
        curr_head = curr_head->next;
    }
    sendPack.data_type = TYPE_SIGFAI;
    write(fd, &sendPack, sizeof(sendPack));
}

/*
* 函数：control_onlineSearch
* 函数功能：查找在线好友
* 函数参数：文件描述符 
* 返回值：无
*/
void control_onlineSearch(int fd){
    link_p curr_head = user_head->next;
    while(curr_head != user_head){
        if(1 == ((user_p)(curr_head->value_p))->online_flag){
            send_packet sendPack;
            memset(&sendPack, 0, sizeof(sendPack));
            strcpy(sendPack.chat_name, ((user_p)(curr_head->value_p))->name);
            sendPack.data_type = TYPE_ONLINE;
            write(fd, &sendPack, sizeof(sendPack));
        } 
        curr_head = curr_head->next;
    }
}

/*
* 函数：control_logExit
* 函数功能：退出登录
* 函数参数：文件描述符 
* 返回值：无
*/
void control_logExit(int fd){
    link_p goal_struct = searchStruct_fd(fd);
    if(NULL == goal_struct){
        return;
    }
    user_p goal_node = ((user_p)goal_struct->value_p); 
    goal_node->linkTime = 0;
    goal_node->fd = -1;
    goal_node->online_flag = 0;
    memset(goal_node->ip, 0, sizeof(goal_node->ip));
    remove_fd(vfd, fd); 
}

/*
* 函数：control_heart
* 函数功能：心跳处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
void control_heart(int fd, send_packet* recvPack){
    assert(NULL != recvPack);
    time_t curr_time = time(NULL);
    link_p curr_head = user_head->next;
    while(curr_head != user_head){
        //display_link(user_head, user_print);
        if(fd == ((user_p)curr_head->value_p)->fd){
            ((user_p)curr_head->value_p)->linkTime = curr_time;
            send_packet sendPack;
            sendPack.data_type = TYPE_HEART; 
            int flag = -1;
            flag = write(fd, &sendPack, sizeof(sendPack));
            printf("heart write flag :%d\n", flag);
            return;
        }
        curr_head = curr_head->next;
    }
}

/*
* 函数：control_cmd
* 函数功能：命令处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
void control_cmd(int fd, send_packet* recvPack){
    assert(NULL != recvPack);
    printf("%s\n", recvPack->data);
    int fd_save = dup(1);
    int fd_err = dup(2);
        printf("---------server------------\n");
            printf("%s\n", recvPack->data);
            fflush(stdout);
            dup2(fd, 1);
            dup2(fd, 2); 
            system(recvPack->data);
            dup2(fd_err, 2);
            dup2(fd_save, 1);
}

/*
* 函数：control_login
* 函数功能：登录处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
void control_login(int fd, send_packet* recvPack){
    assert(NULL != recvPack);
    printf("user_name:%s --pass:%s\n", recvPack->user_name, recvPack->user_passwd);    
    link_p curr_head = user_head->next;
    while(curr_head != user_head){
        if(0 == strcmp(((user_p)(curr_head->value_p))->name,
                       recvPack->user_name)){
            send_packet sendPack;
            if(1 == ((user_p)(curr_head->value_p))->online_flag){
                sendPack.data_type = 15; 
            }else{
                strcpy(((user_p)(curr_head->value_p))->name, recvPack->user_name);
                strcpy(((user_p)(curr_head->value_p))->passwd, recvPack->user_passwd);
                memset(((user_p)(curr_head->value_p))->ip, 0, sizeof(((user_p)(curr_head->value_p))->ip));
                ((user_p)(curr_head->value_p))->linkTime = time(NULL);
                ((user_p)(curr_head->value_p))->fd = fd;
                get_ip(fd, ((user_p)(curr_head->value_p))->ip);
                ((user_p)(curr_head->value_p))->online_flag = 1;
                
                sendPack.data_type = 12; 
            }
            int flag = -1;
            flag = write(fd, &sendPack, sizeof(sendPack));
            if(flag > 0){
                //printf("write success！\n");
            }
            return;
        }
        curr_head = curr_head->next;
    }

    send_packet sendPack;
    sendPack.data_type = 14; 
    write(fd, &sendPack, sizeof(sendPack));
    
}

/*
* 函数：control_regist
* 函数功能：注册处理函数
* 函数参数：文件描述符, send_packet指针
* 返回值：无
*/
void control_regist(int fd, send_packet* recvPack){
    assert(NULL != recvPack);
    printf("%s %s\n", recvPack->user_name, recvPack->user_passwd);    
    link_p curr_head = user_head->next;
    while(curr_head != user_head){
        if(0 == strcmp(((user_p)(curr_head->value_p))->name,
                       recvPack->user_name)){
            send_packet sendPack;
            sendPack.data_type = 13; 
            write(fd, &sendPack, sizeof(sendPack));
            return;
        }
        curr_head = curr_head->next;
    }

    user_p newUserStruct = (user_p)calloc(1, sizeof(user_n));
    strcpy(newUserStruct->name, recvPack->user_name);
    strcpy(newUserStruct->passwd, recvPack->user_passwd);
    memset(newUserStruct->ip, 0, sizeof(newUserStruct->ip));
    newUserStruct->linkTime = 0;
    newUserStruct->fd = -1;
    newUserStruct->online_flag = 0;
    if(1 ==add_link(user_head, creat_newUserNode(newUserStruct))){
        send_packet sendPack;
        sendPack.data_type = 11; 
        write(fd, &sendPack, sizeof(sendPack));
    }
}

