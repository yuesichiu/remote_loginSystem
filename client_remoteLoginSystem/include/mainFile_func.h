/*************************************************************************
	> File Name: mainFile_func.h
	> Author: Eric K. Dai 
	> Mail: dailucool@163.com
	> Created Time: Sat 07 May 2016 05:08:58 PM CST
 ************************************************************************/

#ifndef _MAINFILE_FUNC_H
#define _MAINFILE_FUNC_H

/*
* 函数名称：alarm_handler
* 函数功能：alarm信号处理函数
* 函数参数：无
* 函数返回值：无
* */
extern void alarm_handler();

/*
* 函数名称：pipe_handler
* 函数功能：pipe信号处理函数
* 函数参数：无
* 函数返回值：无
* */
extern void pipe_handler();

/*
* 函数名称：sigint_handler
* 函数功能：sigint信号处理函数
* 函数参数：无
* 函数返回值：无
* */
extern void sigint_handler();
#endif
