/*
 * =====================================================================================
 *
 *       Filename:  color.c
 *
 *    Description:  ANSI 颜色码,输出彩色文字
 *                  适用于C printf Base printf
 *
 *        Created:  12/22/2012 10:37:00 AM
 *         Author:  YOUR NAME (), 
 *
 * =====================================================================================
 */

#include <stdio.h>

/*
 * ANSI 格式
 * 转义字符[1个或多个数字用";"分割以m结束
 * 转义字符可以是\e or \033(\e)的八进制值
 * e.g. \033[x;x;xm ==\e[x;x;xm
 * 可以把多个属性合起来，也可以分开
 * e.g. \e[x;y;zm == \e[xm\e[ym\e[zm
 *
 * 常用x:值
 * 0:关闭所有效果
 * 1:粗体
 * 2:浅色（默认）
 * 4:下划线
 * 5:闪烁
 * 7:翻转
 *
 * 
 * 30:黑色
 * 31:红色
 * 32:绿色
 * 33:黄色
 * 34:蓝色
 * 35:紫色
 * 36：青色
 * 37：白色
 * 
 * 40：黑色背景
 * 41：红色背景
 * 42：绿色背景
 * 4x.:对应3x颜色背景
 * Final color will be 30 + value for foreground and 40 + value for background
 * 原始的色彩只有8个颜色
 *
 * 如果要使用RGB 设置，需要以38;2;<r>;<g>;<b>m 开始
 *
 * 在256-color 模式下需要使用 38;5;<code>;m
 *   code 的计算方程为??
 */

/* Bash 使用时要把颜色字符用\[ANSI-CODE\] 括主*/
//彩虹色 lolcat

/*
static const char* log_color[] = {
	"\e[1m\e[35m", "\e[1m\e[33m", "\e[1m\e[34m", "\e[1m\e[31m",
	"\e[1m\e[32m", "\e[1m\e[36m", "\e[1m\e[1m", "\e[1m\e[37m",	"\e[1m\e[37m"
};


//取消所有效果
static const char* color_end = "\e[m";
*/

int main() {
    //EE已经设置，所有的输出都会被改变，如果要关闭效果要使用/e[0m
    printf("\e[1m\e[30m\n");
    printf("hello\n");
    printf("\e[0m\n");
    printf("hello\n");

    return 0;
}
