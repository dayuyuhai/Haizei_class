/*************************************************************************
	> File Name: common/color.h
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2020 04:19:42 PM CST
 ************************************************************************/

#ifndef COLOR_H
#define COLOR_H

#define NONE    "\e[0m"           //清除颜色
#define BLACK   "\e[0;30" 
#define L_BLACK "\e[1;30m" 
#define RED     "\e[0;31m" 
#define L_RED   "\e[1;31m" 
#define GREEN   "\e[0;32m" 
#define L_GREEN "\e[1;32m" 
#define BROWN   "\e[0;33m" 
#define YELLOW  "\e[1;33m" 
#define BLUE    "\e[0;34m" 
#define L_BLUE  "\e[1;34m" 
#define PURPLE  "\e[0;35m" 
#define L_PURPLE  "\e[1;35m" 
#define CYAN    "\e[0;36m"        //青色
#define L_CYAN  "\e[1;36m" 
#define GRAY    "\e[0;37m" 
#define WHITE   "\e[1;37m" 
#define BOLD    "\e[1m"           //白色，粗体
#define UNDERLINE  "\e[4m"        //下划线，白色，正常大小
#define BLINK   "\e[5m"           //闪烁，白色，正常大小
#define REVERSE "\e[7m"           //反转，景白，字黑
#define HIDE    "\e[8m"           //隐藏
#define CLEAR   "\e[2J"           //清除
#define CLRLINE "\r\e[K"          //清除行

#endif
