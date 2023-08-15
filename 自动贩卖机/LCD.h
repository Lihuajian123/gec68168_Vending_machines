#ifndef _LCD_H
#define _LCD_H
#include "font.h"
//显示24位bmp图片的函数
int show_bmp(char *pathname);
//触摸屏坐标获取的函数声明
int getcrood(int *gx, int *gy);
//显示160*220图片
int show_anybmp(int w,int h,int x,int y,char *bmpname);
//显示字体
//初始化Lcd
struct LcdDevice *init_lcd(const char *device);
#endif