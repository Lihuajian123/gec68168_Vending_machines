#ifndef _OPENDIR_H
#define _OPENDIR_H
#define FILE_TYPE ".bmp"
#include "link_list.h"
//打开目录文件的函数
int openDIR(const char *dirpath,char *filetpye,struct single_list *list);

#endif