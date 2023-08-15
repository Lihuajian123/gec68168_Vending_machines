#include "myhead.h"
#include "link_list.h"

//初始化(头节点)
struct single_list *slist_init()
{
    //定义结构体指针，申请堆空间
    struct single_list *list=malloc(sizeof(struct single_list));
    //指针指向哪里
    list->next= list; 
    list->prev= list;
    return list;
}
struct single_list *iqure_node()
{
    struct single_list *newnode=malloc(sizeof(struct single_list));
    newnode->prev=NULL;
    newnode->next=NULL;
    //指针指向哪里
    return newnode;
}
//尾插数据
int slist_add_tail(char *newpath,struct single_list *list)
{
    //定义结构体指针，申请堆空间
    struct single_list *newnode=iqure_node();
    strcpy(newnode->goods_list.bmp_path,newpath);
    struct single_list *p=list;
    while (p->next!=list)
        p=p->next;
    p->next=newnode;
    newnode->prev=p;

    newnode->next=list;
    list->prev=newnode;
    return 0;
}
//保存数据
int add_data(char *name,int num,float price,struct single_list *list)
{
    //定义结构体指针，申请堆空间
    struct single_list *newnode=list;
    strcpy(newnode->goods_list.name,name);
    newnode->goods_list.price=price;
    newnode->goods_list.num=num;
}
//插入数据
int slist_add(char *newpath,char *name,int num,float price,struct single_list *list)
{
    //定义结构体指针，申请堆空间
    struct single_list *newnode=iqure_node();
    strcpy(newnode->goods_list.bmp_path,newpath);
    strcpy(newnode->goods_list.name,name);
    newnode->goods_list.price=price;
    newnode->goods_list.num=num;
    struct single_list *p=list;
    while (p->next!=list)
        p=p->next;
    p->next=newnode;
    newnode->prev=p;

    newnode->next=list;
    list->prev=newnode;
    return 0;
}
//增加商品函数
int add_goods(struct single_list *list)
{
    struct single_list *newnode=iqure_node();
    char bmp_path[100];//存放的是图片路径
    char  name[20];     //商品名字
    int  num;          //数量
    float price;       //价格 
    printf("请输入商品图片路径：");
    scanf("%s",bmp_path);
    printf("请输入商品名字：");
    scanf("%s",name);
    printf("请输入商品的数量：");
    scanf("%d",&num);
    printf("请输入商品的价格：");
    scanf("%f",&price);
    
    struct single_list *p1=list->next;
    while (p1!=list)
        p1=p1->next;
    slist_add(bmp_path,name,num,price,p1);
}
/* int slist_add(char *oldpath,char *newpath,struct single_list *list)
{
    struct single_list *p=list->next;
    int flgs=0;//标志位

    while (p!=list)
    {
        if(strcmp(p->goods_list.bmp_path,oldpath)==0)
        {
             //定义结构体指针，申请堆空间
            struct single_list *newnode=malloc(sizeof(struct single_list));
            strcpy(newnode->goods_list.bmp_path,newpath);
            newnode->next= NULL; 
            newnode->prev= NULL;
            //指针指向哪里
            newnode->next=p->next;
            newnode->next->prev=newnode;
            p->next=newnode;
            newnode->prev=p;
            //p向下遍历
            p=newnode->next;
            flgs=1;
        }
        else
            p=p->next;
    }
    if(flgs==0)
        printf("未插入%s数据\n",newpath);
    return 0;
} */

//删除数据
/* int list_delete(char *delpath, struct single_list *list)
{
    int flgs = 0;
    struct single_list *p=list->next;
    while (p!=list)
    {
        if(strcmp(p->goods_list.name,delpath)==0)
        {
            struct single_list *temp = p;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p = p->next;
            temp->next=NULL;
            temp->prev=NULL;
            free(temp);
            flgs =1;//已经删除数据
        }
        else
            p=p->next;
    }
    if(flgs==0)
        printf("未删除%s商品\n",delpath);
    return 0;
    
} */
int list_delete(struct single_list *p)
{
    struct single_list *temp = p;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p = p->next;
    temp->next=NULL;
    temp->prev=NULL;
    free(temp);
    return 0;
    
} 

//删除商品的函数
int del_goods(struct single_list *list1,struct single_list *list)
{
    struct single_list *next_node = list1->next;
    list_delete(list1);//删除节点的数据
    list1=next_node;
}
//修改数据
int up_data(void *newdata,int key,struct single_list *list)
{
    int flgs = 0;
    struct single_list *p=list;
    //寻找要修改的内容
    switch (key)
    {
        case 1: //修改商品价格
            p->goods_list.price=*(float *)newdata;
            printf("修改商品价格成功！\n");
            break;
        case 2: //修改商品数量
            p->goods_list.num=*(int *)newdata;
            printf("修改商品数量成功！\n");
            break;
        default:
            break;
    }
}
//选择修改商品内容函数
int up_goods(int key,void *newdata,struct single_list *list,struct single_list *list1)
{
    char name[20];
    switch (key)
    {
        case 1:
            up_data((float *)newdata,key,list);
            save_goods_to_file(list1);
            break;
        case 2:
            up_data((int *)newdata,key,list);
            save_goods_to_file(list1);
            break;
        default:
            break;
    }
}
//打印数据
int slist_show(struct single_list *list)
{
    //定义一个结构体指向指向链表结构体
    struct single_list *p=list->next;
    if(p==list)
    {
        printf("这个链表为空！\n");
        return -1;
    }
    while(p!=list)
    {
        //printf("目前遍历的数据是：%s\t%s\t%d\t%.2f\n",p->goods_list.bmp_path,p->goods_list.name,p->goods_list.num,p->goods_list.price);
        printf("当前遍历的是：%s %s %d %f\n",p->goods_list.bmp_path,p->goods_list.name,p->goods_list.num,p->goods_list.price);
        p=p->next;//循环结束时p指向最后一个节点打的位置 
    }
}
//读取文件内容写入链表
void read_goods_to_list(struct single_list *list) 
{
    FILE *file = fopen("goods.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    // 跳过第一行
    char skip_line[100];
    fgets(skip_line, sizeof(skip_line), file);//分行读取 光标到第二行
    char line[100];
    struct single_list *p=list;
    while (fgets(line, sizeof(line), file)) //按行读取
    {
        // 解析行内容为商品信息
        char  name[20];     //商品名字
        int  num;          //数量
        float price;       //价格
        sscanf(line, "%s %d %f",name, &num, &price);
        p=p->next;
        // 将信息保存到链表中
        if(p==NULL)
            break;
        add_data(name,num,price,p);
        bzero(line,100);
    }

    fclose(file);
}
//将信息写入txt文件中保存
void save_goods_to_file(struct single_list *list) 
{
    FILE *file = fopen("goods.txt", "w+");
    char  name[20]="商品名字";     //商品名字
    char  num[20]="商品数量";          //数量
    char  price[20]="商品价格";       //价格
    if (file == NULL) 
    {
        printf("无法打开文件\n");
        return;
    }
    fprintf(file, "%s\t%s\t%s\n",name,num,price);
    struct single_list  *p = list->next;
    while (p != list) 
    {
        fprintf(file, "%s\t\t%d\t\t%.2f\n",p->goods_list.name,p->goods_list.num,p->goods_list.price);
        p = p->next;
    }
    fclose(file);
}
/* int main()
{
    struct single_list *mylist=slist_init();
    read_goods_to_list(mylist);
    //尾插数据
    //slist_add_tail("./BMP/1.bmp","可口可乐",10,3.5,mylist);
    //插入数据
    //slist_add("./BMP/2.bmp","./BMP/3.bmp",mylist);
    
    //slist_add("./BMP/2.bmp","./BMP/3.bmp",mylist);
    //删除数据
    list_delete("./BMP/1.bmp",mylist);
    save_goods_to_file(mylist);
    //打印数据
    slist_show(mylist);
    return 0;
} */