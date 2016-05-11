/*************************************************************************
	> File Name: control.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Thu 05 May 2016 08:57:48 AM CST
 ************************************************************************/

#include "std.h"

/*
* 函数名称：main_menu_control
* 函数功能：主菜单控制函数
* 函数参数：sodkfd
* 函数返回值：无
* */
void main_menu_control(int sockfd){
    int choose = 0;
    int flag = 0;
    while(1){
        do{
            system("clear");
            main_menu();
            flag = scanf("%d", &choose);
            CLEAN_BUFF; 
        }while(0 == flag || choose >2  || choose < 0);

        switch(choose){
            case 0:  
                //退出
                logout(sockfd);
                WAIT;
                return;
            case 1:
                //注册
                regist(sockfd);
                break;
            case 2:
                //登录
                login(sockfd);
                break;
            default:
                printf(RED"无此选项！\n"NONE);
                WAIT;
                break;
        }
    }
}


/*
* 函数名称：chatRoom_menu_control
* 函数功能：聊天室菜单控制函数
* 函数参数：sockfd
* 函数返回值：无
* */
void chatRoom_menu_control(int sockfd){
    int choose = 0;
    int flag = 0;
    while(1){
        do{
            system("clear");
            chatRoom_menu();
            flag = scanf("%d", &choose);
            CLEAN_BUFF; 
        }while(0 == flag || choose >4  || choose < 0);
        switch(choose){
            case 0:
                printf("已退出聊天室！\n");
                WAIT;
                return;
            case 1:  
            //向服务器发送指令
                send_comnd(sockfd);
                WAIT;
                break;
            case 2: 
            //单聊
                singleChat();
                WAIT;
                break;
            case 3:
            //群聊
                groupChat();
                break;
            case 4:
            //查询在线好友
                online_search();
                WAIT;
                break;  
            default:
                printf(RED"无此选项！\n"NONE);
                WAIT;
                break;
        }
    }
}

/*
* 函数名称：regist
* 函数功能：注册
* 函数参数：sockfd
* 函数返回值：无
* */
void regist(int sockfd){
    int num = 0;
    while(1){
        if(num >= 3){
            printf(RED"输入次数过多，请重新注册！\n"NONE);
            return;
        }
        num ++;
        char name[NUM] = "";
        char passwd[NUM] = "";
        int flag1, flag2 = -1;
        flag1 = get_name(name);
        if(-1 == flag1){
            return;
        }
        flag2 = get_newPasswd(passwd);
        if(-1 == flag2){
            return;
        }

        send_packet sendPack;
        sendPack.data_type = 1;
        strcpy(sendPack.user_name, name);
        strcpy(sendPack.user_passwd, passwd);
        int flag = -1;
        flag = write(sockfd, &sendPack, sizeof(sendPack));
        if(flag > 0){
            send_packet recvPack;
            read(sockfd, &recvPack, sizeof(sendPack)); 
            //printf("%d\n", recvPack.data_type);
            if(TYPE_REGSUC == recvPack.data_type){
                printf("注册成功！请重新登录！\n");
                WAIT;
                return;
            }else{
                printf("用户名重复，请重新输入！\n");
            }
        }
    }
}


/*
* 函数名称：logout
* 函数功能：退出登录
* 函数参数：sockfd
* 函数返回值：无
* */
void logout(int sockfd){
    send_packet sendPack;
    sendPack.data_type = 6;
    write(sockfd, &sendPack, sizeof(sendPack));
    printf("已退出！\n");
}

/*
* 函数名称：login
* 函数功能：登录
* 函数参数：sockfd
* 函数返回值：无
* */
void login(int sockfd){
    int num = 0;
    while(1){
        if(num >= 3){
            printf(RED"用户名或密码输入错误三次，请重新登录！\n"NONE);
            WAIT;
            return;
        }
        char name[NUM] = "";
        char *passwd = "";
        int flag1;
        flag1 = get_name(name);
        if(-1 == flag1){
            return;
        }
        int flag = 0;
        int len = 0;
        do{
            if(num > 2){
                printf(RED"密码输错三次，请重新登录！\n"NONE);
                WAIT;
                return;
            }
            if(1 == flag){
                printf(RED"请输入5-20位的密码！\n"NONE);
                num ++;
            }
            passwd = getpass(YELLOW"请输入密码："NONE);
            len = strlen(passwd);
            flag = 1;
        }while(len < 5 || len > NUM-1);
        

        send_packet sendPack;
        sendPack.data_type = 0;
        strcpy(sendPack.user_name, name);
        strcpy(sendPack.user_passwd, passwd);
        int write_flag = -1;
        write_flag = write(sockfd, &sendPack, sizeof(sendPack));
        if(write_flag > 0){
            send_packet recvPack;
            //int ret = -1;
            read(sockfd, &recvPack, sizeof(sendPack)); 
            //printf("read ret: %d\n", ret);
            if(TYPE_LOGSUC == recvPack.data_type){
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

                pthread_t th;
                int pthrd_creaErr;
                if((pthrd_creaErr = pthread_create(&th, &attr, thrd_func, (void*)&sockfd)) != 0){
                    perror("pthread create error!\n");
                    exit(1);
                }
                pthread_attr_destroy(&attr);

                printf("log success!\n");
                WAIT;
                chatRoom_menu_control(sockfd);
                return;
            }else if(TYPE_LOGRE == recvPack.data_type){
                printf(RED"该帐户已在其它客户端登录！\n"NONE);
                WAIT;
                return;
            }else{
                printf(RED"用户名或密码错误，请重新输入！\n"NONE);
                num ++;
            }
        }
    }
}

/*
* 函数名称：send_comnd
* 函数功能：向客户端发送命令
* 函数参数：sockfd
* 函数返回值：无
* */
void send_comnd(int sockfd){
    printf(YELLOW"请输入命令:\n"NONE);
    while(1){
        send_packet sendPack;
        sendPack.data_type = 4;
        memset(sendPack.data, 0, sizeof(sendPack.data));
        fgets(sendPack.data, sizeof(sendPack.data), stdin);//clean buff yao huiche?
        if(strlen(sendPack.data)-1 < 0){
            continue;
        }
        if(0 == strncmp(sendPack.data, "exit", 4)){
            printf(YELLOW"已退出！\n"NONE);
            break;
        }

        //int flag = -1;
        fflush(stdout);
        write(sockfd, &sendPack, sizeof(sendPack));
        //printf("send_somnd write return : %d\n", flag);
    }
}

/*
* 函数名称：singleChat
* 函数功能:一对一聊天
* 函数参数：无
* 函数返回值：无
* */
void singleChat(){
    send_packet sendPack;
    sendPack.data_type = TYPE_CHAT;
    printf(YELLOW"请输入好友姓名：\n"NONE);
    scanf("%s", sendPack.chat_name);
    CLEAN_BUFF;
    printf(YELLOW"请输入聊天内容(输入exit退出)：\n"NONE);
    while(1){
        memset(sendPack.data, 0, sizeof(sendPack.data));
        fgets(sendPack.data, sizeof(sendPack.data), stdin);
        if(strlen(sendPack.data)-1 < 0){
            continue;
        }
        if(0 == strncmp(sendPack.data, "exit", 4)){
            printf(YELLOW"已退出聊天！\n"NONE);
            break;
        }

        int flag = -1;
        fflush(stdout);
        flag = write(sockfd, &sendPack, sizeof(sendPack));
        printf("---chat %d-%s--\n", flag, sendPack.data);
    }
}

/*
* 函数名称：groupChat
* 函数功能：群聊
* 函数参数：无
* 函数返回值：无
* */
void groupChat(){
    send_packet sendPack;
    sendPack.data_type = TYPE_GROUPCHAT;
    while(1){
        memset(sendPack.data, 0, sizeof(sendPack.data));
        printf(YELLOW"请输入聊天内容(输入exit退出)：\n"NONE);
        fgets(sendPack.data, sizeof(sendPack.data), stdin);
        if(strlen(sendPack.data)-1 < 0){
            continue;
        }
        if(0 == strncmp(sendPack.data, "exit", 4)){
            printf(RED"退出聊天！\n"NONE);
            break;
        }

        int flag = -1;
        fflush(stdout);
        flag = write(sockfd, &sendPack, sizeof(sendPack));
        printf("---group chat %d---\n", flag);
    }
    
}

/*
* 函数名称：online_search
* 函数功能：查询在线好友
* 函数参数：无
* 函数返回值：无
* */
void online_search(){
    send_packet sendPack;
    sendPack.data_type = 5;
    write(sockfd, &sendPack, sizeof(sendPack));
}

