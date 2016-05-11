/*************************************************************************
	> File Name: common.c
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Wed 06 Apr 2016 08:58:46 PM CST
 ************************************************************************/

#include "std.h"

/*
 * 函数名：get_name
 * 函数功能：从标准输入得到用户名，拷贝到以参数为首地址的数组
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
int get_name(char *username){
    if(NULL == username){
        printf("The point is NULL ! code: get_name 01\n");
        return -1;
    }

    int flag = 0;
    int len = 0;
    char new_name[NUM] = {0};
    int count = 0;
    do{
        if(count > 2){
            printf(RED"姓名输错三次，请重新输入！\n"NONE);
            WAIT;
            return -1;
        }
        if(1 == flag){
           printf(RED"请输入5-20个字符的用户名！\n"NONE);
        }
        printf(YELLOW"\n\n请输入用户名:"NONE);
        scanf("%21s", new_name);
        CLEAN_BUFF;
        len = strlen(new_name);
        flag = 1;
        count ++;
    }while(len < 5 || len > NUM-1);
    strcpy(username, new_name);
    return 1;
}


/*
 * 函数名：get_passwd
 * 函数功能：从标准输入得到密码，拷贝到以参数为首地址的数组
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
 int get_passwd(char *passwd){
    if(NULL == passwd){
        printf("The point is NULL ! code: get_passwd 01\n");
         return -1;
    }

    int flag = 0;
    char *p = NULL;
    int len = 0;
    int count = 0;
    do{
        if(count > 2){
            printf(RED"密码输错三次，请重新输入！\n"NONE);
            WAIT;
            return -1;
        }
        if(1 == flag){
            printf(RED"请输入5-20位的密码！\n"NONE);
        }
        p = getpass(YELLOW"请输入密码："NONE);
        len = strlen(p);
        flag = 1;
        count ++;
    }while(len < 5 || len > NUM-1);
    strcpy(passwd, p);
    p = NULL;
    return 1;
}


/*
 * 函数名：get_newPasswd
 * 函数功能：注册时得到新密码
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */
int get_newPasswd(char *passwd){
    if(NULL == passwd){
        printf("The point is NULL ! code: get_newPasswd 01\n");
        return -1;
    }

    int flag = 0;
    char *p = (char*)calloc(NUM, sizeof(int));
    char *q = (char*)calloc(NUM, sizeof(int));
    do{
        if(1 == flag){
            printf(YELLOW"\n\n两次输入的密码不一样，请重新输入!\n"NONE);
        }
       
        get_passwd(p);
        printf(YELLOW"请再次输入密码!\n"NONE);
        get_passwd(q);
        flag = 1;
    }while(0 != strcmp(p, q));
    strcpy(passwd, p);
    free(q);
    free(p);
    p = NULL;
    q = NULL;
    return 1;
 }


/*
 * 函数名：get_passwdThree
 * 函数功能：得到输入密码，输入次数不超过三次
 * 函数参数：数组的首地址
 * 函数返回值：成功1，失败-1
 * */

int get_passwdThree(char *passwd){
    if(NULL == passwd){
        printf("The point is NULL !\n");
        return -1;
    }

    int flag = 0;
    char *p = (char*)calloc(NUM, sizeof(int));
    do{
        if(3 == flag){
            printf(RED"\n\n密码输错三次，请重新登陆！\n"NONE);
            WAIT;
            return -1;
        }
        if(flag > 0){
            printf(RED"\n\n密码错误，请重新输入！\n"NONE);
        }
        
        get_passwd(p);
        ++flag;
    }while(0 != strcmp(p, passwd));
    p = NULL;
    return 1;
 }

     
/*
 * 函数名：print_int
 * 函数功能：打印int型值
 * 函数参数：字符串指针，int型指针
 * 函数返回值：无
 * */
void print_int(char *str, int *elem){
    if(NULL == str || NULL == elem){
        printf("The point is NULL !\n");
        return;
    }

    printf(GREEN"%s %d\n"NONE, str, *elem);
 }


/*
 * 函数名：get_int
 * 函数功能：得到int型变量
 * 函数参数：字符串首地址， 打印的值的地址， 最小最大范围
 * 函数返回值：无
 * */
void get_int(char *str, int *value, int min, int max){
    if(NULL == str || NULL == value){
        printf("The point is NULL !\n");
        return;
    }

    int sign = 0;
    int flag = 0;
    int count = 0;
    do{
        if(count > 3){
            printf("三次了！改下返回值退出\n");
            return; 
        }
        if(1 == sign){
            printf(YELLOW"\n\n输入无效，请重新输入!\n"NONE);
        }
        printf(YELLOW"%s"NONE, str);
        flag = scanf("%d", value);
        CLEAN_BUFF;
        sign = 1;
        count ++;
    }while(flag < 1 || *value < min || *value > max);
}
