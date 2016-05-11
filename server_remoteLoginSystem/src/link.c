/*************************************************************************
	> File Name: link.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Tue 05 Apr 2016 03:35:53 PM CST
 ************************************************************************/

#include "std.h"

/*
typedef struct Link{
    void *value_p;
    int value_size;
    struct Link *next;
    struct Link *prev;
}link_n, *link_p;

*/

/*
* 函数：creat_link 
* 函数功能：创建链表
* 函数参数：链表内value大小
* 返回值：头结点指针
*/
link_p creat_link(int size){
    link_p head = (link_p)calloc(1, sizeof(link_n));
    if(NULL == head){
        printf("head build faild!\n");
        return NULL;
    }
    head->value_p = NULL;
    head->value_size = size;
    head->prev = head;
    head->next = head;
    return head;
}


/*
* 函数：add_link
* 函数功能：增加链表节点
* 函数参数：链表头指针， 要添加的节点的数据域指针
* 返回值：成功返回1， 不成功返回-1
*/
int add_link(link_p head, link_p node_element){
    if(NULL == head || NULL == node_element){
        printf("The point is NULL!\n");
        return -1;
    } 
    
    pthread_mutex_lock(&mutex);
    if(node_element->value_size != head->value_size){
        printf("add error!\n");
        return -1;
    }

    link_p curr_head = head;
    node_element->prev = curr_head;
    node_element->next = curr_head->next;
    curr_head->next = node_element;
    node_element->next->prev = node_element;
    curr_head = NULL;
    pthread_mutex_unlock(&mutex);
    return 1;
}


/*
* 函数：delete_link
* 函数功能: 删除节点
* 函数参数：链表头指针， 删除所依据的信息， 比较函数的函数指针
* 返回值：成功返回1， 不成功返回-1, 查询不到返回2
*/
int delete_link(link_p head, void *value_element, int (*p)(void *elem1, void *elem2)){
    if(NULL == head || NULL == value_element || NULL == p){
        printf("The point is NULL!\n");
        return -1;
    }

    pthread_mutex_lock(&mutex);
    link_p curr = head->next;
    link_p dele = NULL;
    while(head != curr){
        dele = curr;
        curr = curr->next; 
        if(!p(dele->value_p, value_element)){
            dele->prev->next = dele->next;
            dele->next->prev = dele->prev;
            free(dele);
        }
    }
    curr = NULL;
    dele = NULL;
    pthread_mutex_unlock(&mutex);
    return 1;
}


/*
* 函数：display_link
* 函数功能：陈列链表
* 函数参数：链表头指针， 打印函数的函数指针
* 返回值：无
*/
void display_link(link_p head, void (*p)(void *value_elem)){
    if(NULL == head || NULL == p){
        printf("The point is NULL !\n");
        return;
    }
    
    link_p curr = head->next;
    while(head != curr){
        p(curr->value_p);
        curr = curr->next;
    }
    curr = NULL;
}


/*
* 函数：save_link
* 函数功能：保存链表到文件mZ* 函数参数：链表头指针， 文件路径， 具体的保存函数的函数指针
* 返回值：成功返回1， 失败返回-1
*/
int save_link(link_p head, char *path, int (*p)(link_p head, char *path)){
    if(NULL == head || NULL == path || NULL == p){
        printf("The point is NULL !\n");
        return -1;
    }

    pthread_mutex_lock(&mutex);
    return p(head, path);
    pthread_mutex_unlock(&mutex);
}


/*
* 函数：load_link
* 函数功能：读文件到链表
* 函数参数：链表头指针， 文件路径， 具体的读文件函数的函数指针
* 返回值：
*/

int load_link(link_p head, char *path, int (*p)(link_p head, char *path)){
    if(NULL == head || NULL == path || NULL == p){
        printf("The point is NULL !\n");
        return -1;
    }
    return p(head, path);
}


/*
* 函数：is_empty
* 函数功能：判断链表是否为空
* 函数参数：链表头指针
* 返回值：是空返回1， 不是返回2, 错误返回-1
*/
int is_empty(link_p head){
    if(NULL == head){
        printf("The point is NULL !\n");
        return -1;
    }
    else{
        if(head->next == head){
            return 1;
        }
        else{    
            return 2;
        }
    }
}


/*
* 函数：update_link
* 函数功能：对链表内容进行更改
* 函数参数：链表结构体指针，新的元素， 执行更改的函数指针 
* 返回值：无
*/
void update_link(void *update_struct, void *elem_change, 
 void (*pchange)(void *elem1, void *elem2)){

    if(NULL == update_struct || NULL == elem_change
       || NULL == pchange){
        printf("The point is NULL !\n");
        return;
    }
    
    pchange(update_struct, elem_change);
}


/*
* 函数：search_link
* 函数功能：链表查找
* 函数参数：链表头指针，进行查找所依据的值， 执行查找的条件判断函数指针
* 返回值：链表节点类型指针
*/
link_p search_link(link_p head, void *search_elem, 
 int (*psearch)(void *elem1, void *elem2)){

    if(NULL == head || NULL == search_elem 
       || NULL == psearch){
        printf("The point is NULL !\n");
           return NULL;
    }
    
    link_p curr_head = head->next;
    while(head != curr_head){
        if(0 == psearch(curr_head->value_p, search_elem)){
            return curr_head;
        }
        curr_head = curr_head->next;
    }
    return NULL;
}


/*
* 函数：destroy_link
* 函数功能：销毁链表
* 函数参数：链表头节点
* 返回值：无
*/
void destroy_link(link_p head){
    if(NULL == head){
        printf("The point is NULL !\n");
        return;
    }    
    
    link_p dele = head->next;
    link_p later = head->next->next;
    while(later != head){
        free(dele->value_p);
        free(dele);
        dele = later;
        later = later->next;
    }
    free(head);
    dele = NULL;
    later = NULL;
    head = NULL;
}


/*
* 函数：searchAll_link
* 函数功能：链表查找,全部找一遍，对全部符合情况的数据进行处理
* 函数参数：链表头指针，进行查找所依据的值， 执行查找的条件判断函数指针
* 返回值：复合查找条件的节点总数
*/
int searchAll_link(link_p head, int *search_elem, 
 int *elem, int (*psearch)(int *elem1, int *elem2, int *elem3)){

    if(NULL == head || NULL == search_elem 
       || NULL == psearch){
        printf("The point is NULL !\n");
           return -1;
    }
    
    int count = 0;
    int temp = 0;
    link_p curr_head = head->next;
    while(head != curr_head){
        temp = psearch(curr_head->value_p, search_elem, elem);
        if(temp > 0){
            count += temp;
        }
        curr_head = curr_head->next;
    }
    return count;
}
