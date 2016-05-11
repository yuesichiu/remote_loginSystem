/*************************************************************************
	> File Name: lottery_user.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Wed 06 Apr 2016 01:54:11 PM CST
 ************************************************************************/

#include "std.h"

/*
 * 函数：creat_newuserNode
 * 函数功能：创建一个新的用户节点
 * 函数参数：用户结构体指针
 * 返回值：成功返回节点指针， 不成功返回NULL
 */
link_p creat_newUserNode(user_p new_user_p){
    //value_p value_size
    if(NULL == new_user_p){
        printf("The point is NULL! code: creat_newuserNode 01\n");
        return NULL;
    }

    link_p new_node = (link_p)calloc(1, sizeof(link_n));
    if(NULL == new_node){
        printf("Get new memory fail !\n");
        return NULL;
    }
    new_node->value_p = new_user_p;
    new_node->value_size = sizeof(user_n);
    new_node->prev = new_node->next = NULL;
    return new_node;
}

/*
 * 函数：save_user
 * 函数功能：保存用户链表
 * 函数参数：链表头指针， 保存路径
 * 返回值：成功返回1， 不成功返回-1
 * */
int save_user(link_p user_head, char* path){
    if(NULL == user_head || NULL == path){
        printf("The point is NULL !\n");
        return -1;
    }

    FILE* pfile = fopen(path, "wb");//路径要改
    if(NULL == pfile){
        printf("File open fail !\n");
        return -1;
    }

    link_p curr =  user_head->next;
    user_save* save_data = (user_save*)calloc(1, sizeof(user_save));

    while(curr != user_head){
        strcpy(save_data->name, ((user_save*)curr->value_p)->name);
        strcpy(save_data->passwd, ((user_save*)curr->value_p)->passwd);
        int flag = fwrite(save_data, sizeof(user_save), 1, pfile);
        if(flag < 1){
            printf("Save error! code: save_user! \n");
            return -1;
        }
        curr = curr->next;
    }
    fclose(pfile);
    pfile = NULL;
    curr = NULL;
    return 1;
}


/*
 * 函数：load_user
 * 函数功能：读取用户链表
 * 函数参数：链表头指针， 保存路径
 * 返回值：成功返回1， 不成功返回-1
 * */
int load_user(link_p user_head, char* path){
    if(NULL == user_head || NULL == path){
        printf("The point is NULL !\n");
        return -1;
    }

    FILE* pfile = fopen(path, "rb");
    if(NULL == pfile){
        system("touch ../user.db");
        return 1;
    }

    while(1){
        link_p user_temp = (link_p)calloc(1, sizeof(link_n));
        if(NULL == user_temp){
            printf("Get memory fail!\n");
            return -1;
        }
        user_p user_node = (user_p)calloc(1, sizeof(user_n));
        if(NULL == user_node){
            printf("Get memory error!\n");
            return -1;
        }

        user_temp->value_p = user_node;
        user_temp->value_size = sizeof(user_n);

        user_temp->prev = NULL;
        user_temp->next =NULL;

        user_save* load_data = (user_save*)calloc(1, sizeof(user_save));
        int flag = fread(load_data, sizeof(user_save), 1, pfile);
        if(1 != flag){
            fclose(pfile);
            pfile = NULL;
            user_temp = NULL;
            return 1;
        }

        strcpy(user_node->name,load_data->name);
        strcpy(user_node->passwd,load_data->passwd);

        memset(user_node->ip, 0, sizeof(user_node->ip));
        user_node->linkTime = 0;
        user_node->fd = -1;
        user_node->online_flag = 0;

        if(1 != add_link(user_head, user_temp)){
            fclose(pfile);
            pfile = NULL;
            user_temp = NULL;
            printf("Read error!\n");
            return -1; 
        }
    }
}


/*
 * 函数：delete_user
 * 函数功能：删除用户
 * 函数参数：链表头指针
 * 返回值：无
 * */
void delete_user(link_p head){
        printf("Please input your user ID !\n");
        int *dele_id = NULL;
        scanf("%d", dele_id);
       // delete_link(head, dele_id, compare_userId);
}


/*
 * 函数：user_print
 * 函数功能：打印用户信息
 * 函数参数：结构体指针
 * 返回值：无
 * */
void user_print(void *value_elem){
    if(NULL == value_elem){
        printf("The point is NULL！\n");
        return;
    }
    user_p curr_user = (user_p)value_elem;
    printf(GREEN"*********************************\n"NONE);
    printf(GREEN"用户名：\t\t%s\n"NONE, curr_user->name);
    printf(GREEN"用户ip：\t\t%s\n"NONE, curr_user->ip);
    print_int("用户fd：\t\t", &curr_user->fd);
    print_int("用户在线状态：\t\t", &curr_user->online_flag);
    printf(GREEN"*********************************\n"NONE);
    printf("\n");
}
