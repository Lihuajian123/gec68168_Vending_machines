#ifndef _LINK_LIST_H
#define _LINK_LIST_H
struct goods
{
    char bmp_path[100];//存放的是图片路径
    char  name[20];     //商品名字
    int  num;          //数量
    float price;       //价格 
}; 

//定义双向循环链表
struct single_list
{
    //char bmp_path[100];//存放的是图片路径
    struct goods goods_list;//数据域，存放的数据内容
    struct single_list *prev;//指针域，存放上一个数据的地址
    struct single_list *next;//指针域，存放下一个数据的地址
};
//链表功能函数的声明
struct single_list *slist_init();   //初始化链表
//尾插数据
//int slist_add_tail(char *newpath,char *name,int num,float price,struct single_list *list);
int slist_add_tail(char *newpath,struct single_list *list);
int add_data(char *name,int num,float price,struct single_list *list);
//插入数据
//int slist_add(char *oldpath,char *newpath,struct single_list *list);
int slist_add(char *newpath,char *name,int num,float price,struct single_list *list);
//修改数据
//int up_data(void *newdata,int key,struct single_list *list);
int del_goods(struct single_list *list1,struct single_list *list);
//选择修改商品内容函数
//int up_goods(int key,struct single_list *list,struct single_list *list1);
int up_goods(int key,void *newdata,struct single_list *list,struct single_list *list1);
//增加商品函数
int add_goods(struct single_list *list);
//删除数据
//int list_delete(char *delpath, struct single_list *list);
int list_delete(struct single_list *p);
//删除商品的函数
//int del_goods(struct single_list *list);
int del_goods(struct single_list *list1,struct single_list *list);
//打印数据
int slist_show(struct single_list *list);
void read_goods_to_list(struct single_list *list);
//将信息写入txt文件中保存
void save_goods_to_file(struct single_list *list);
#endif