#include "myhead.h"
#include "link_list.h"
#define FILE_TYPE ".bmp"
#define ADD_GOODS "5.bmp"
int openDIR(const char *dirpath,char *filetpye,struct single_list *list)
{
	int i=0;
    
    DIR *mydir;
    struct dirent *mydirent;
	char temp[100]={0};//存放绝对路径
    //打开目录
    mydir=opendir(dirpath);
    if(mydir==NULL)
	{
		perror("打开目录失败了!\n");
		return -1;
	}
    while ((mydirent=readdir(mydir))!=NULL)
    {
        //排除.和..的这两个特殊目录文件
        if(strcmp(mydirent->d_name,"..")==0||strcmp(mydirent->d_name,".")==0)
            continue;
        //判断文件是不是普通文件
        
        if(mydirent->d_type == DT_REG)//ubuntu运行时要删除单引号
        {
            if(strstr(mydirent->d_name,filetpye)!=0)
            {
                bzero(temp,100);
                snprintf(temp,512,"%s/%s",dirpath,mydirent->d_name);
                //不要录入要进行上架操作的商品
                if (strcmp(mydirent->d_name, ADD_GOODS) == 0);
                //进行链表的尾插
                else
                    slist_add_tail(temp,list);
            }
        }
        //判断是否存在子目录
        /* if(mydirent->d_type == DT_DIR )//ubuntu运行时要删除单引号
        {
            if(strstr(mydirent->d_name,filetpye)!=0)
            {
                bzero(temp,100);
                sprintf(temp,"%s/%s",dirpath,mydirent->d_name);
                openDIR(temp,FILE_TYPE,list);
            }
        } */
    }
    closedir(mydir);
    return 0;
}