/*************************************************************************
	> File Name: link.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Tue 05 Apr 2016 02:42:40 PM CST
 ************************************************************************/

#ifndef _LINK_H
#define _LINK_H

pthread_mutex_t mutex;

typedef struct Link{
    void *value_p;
    int value_size;
    struct Link *next;
    struct Link *prev;
}link_n, *link_p;

/*
* 函数：creat_link 
* 函数功能：创建链表
* 函数参数：链表内value大小
* 返回值：头结点指针
*/
extern link_p creat_link(int size);

/*
* 函数：add_link
* 函数功能：增加链表节点
* 函数参数：链表头指针， 要添加的节点的数据域指针
* 返回值：成功返回1， 不成功返回-1
*/
extern int add_link(link_p head, link_p node_element);

/*
* 函数：delete_link
* 函数功能: 删除节点
* 函数参数：链表头指针， 删除所依据的信息， 比较函数的函数指针
* 返回值：成功返回1， 不成功返回-1
*/
extern int delete_link(link_p head, void *value_element, int (*p)(void *elem1, void *elem2));

/*
* 函数：display_link
* 函数功能：陈列链表
* 函数参数：链表头指针， 打印函数的函数指针
* 返回值：无
*/
extern void display_link(link_p head, void (*p)(void *value_elem));

/*
* 函数：save_link
* 函数功能：保存链表到文件
* 函数参数：链表头指针， 文件路径， 具体的保存函数的函数指针
* 返回值：成功返回1， 失败返回-1
*/
extern int save_link(link_p head, char *path, int (*p)(link_p head, char *path));

/*
* 函数：load_link
* 函数功能：读文件到链表
* 函数参数：链表头指针， 文件路径， 具体的读文件函数的函数指针
* 返回值：
*/
extern int load_link(link_p head, char *path, int (*p)(link_p head, char *path));

/*
* 函数：is_empty
* 函数功能：判断链表是否为空
* 函数参数：链表头指针
* 返回值：是空返回1， 不是返回-1
*/
extern int is_empty(link_p head);


/*
* 函数：update_link
* 函数功能：对链表内容进行更改
* 函数参数：链表结构体指针，新的元素， 执行更改的函数指针 
* 返回值：无
*/
extern void update_link(void *update_struct, void *elem_change, 
 void (*pchange)(void *elem1, void *elem2));


/*
* 函数：search_link
* 函数功能：链表查找
* 函数参数：链表头指针，进行查找所依据的值， 执行查找的函数指针
* 返回值：链表节点类型指针
*/
extern link_p search_link(link_p head, void *search_elem, 
 int (*psearch)(void *elem1, void *elem2));


/*
* 函数：destroy_link
* 函数功能：销毁链表
* 函数参数：链表头节点
* 返回值：无
*/
extern void destroy_link(link_p head);


/*
* 函数：searchAll_link
* 函数功能：链表查找,全部找一遍，对全部符合情况的数据进行处理
* 函数参数：链表头指针，进行查找所依据的值， 执行查找的条件判断函数指针
* 返回值：复合查找条件的节点总数
*/
extern int searchAll_link(link_p head, int *search_elem, 
 int *elem, int (*psearch)(int *elem1, int *elem2, int *elem3));


#endif
