#include "myhead.h"
#include "LCD.h"
#include "opendir.h"
#include "link_list.h"
#include "font.h"
#define FILE_TYPE ".bmp"
#define USER "user.bmp"
#define ROOT "root.bmp"
//键盘输入的函数
char *key_board()
{
    int x,y;
    float price[20];
    char *str = (char *)malloc(20 * sizeof(char)); // 使用动态分配来保存输入的字符串
    str[0] = '\0'; // 初始化字符串为空
    while (1)
    {
        //获取坐标地址
        getcrood(&x,&y);
        char temp='0';
        if(x>=550&&x<634 && y>=50 &&y<120)
        {
            printf("1");
            fflush(stdout);
            strcat(str,"1");
        }
        if(x>=634&&x<715 && y>=50 &&y<120)
        {
            printf("2");
            fflush(stdout);
            strcat(str,"2");
        }
        if(x>=715&&x<800 && y>=50 &&y<120)
        {
            printf("3");
            fflush(stdout);
            strcat(str,"3");
        }
        if(x>=550&&x<=634 && y>=120 &&y<200)
        {
            printf("4");
            fflush(stdout);
            strcat(str,"4");
        }
        if(x>=634&&x<715 && y>=120 &&y<200)
        {
            printf("5");
            fflush(stdout);
            strcat(str,"5");
        }
        if(x>=715&&x<800 && y>=120 &&y<200)
        {
            printf("6");
            fflush(stdout);
            strcat(str,"6");
        }
        if(x>=550&&x<634 && y>=200 &&y<280)
        {
            printf("7");
            fflush(stdout);
            strcat(str,"7");

        }
        if(x>=634&&x<715 && y>=200 &&y<280)
        {
            printf("8");
            fflush(stdout);
            strcat(str,"8");
        }
        if(x>715&&x<800 && y>=200 &&y<280)
        {
            printf("9");
            fflush(stdout);
            strcat(str,"9");
        }
        if(x>=634&&x<680 && y>=280 &&y<340)
        {
            printf("0");
            fflush(stdout);
            strcat(str,"0");
        }
        if(x>=680&&x<=715 && y>=280 &&y<340)
        {
            printf(".");
            fflush(stdout);
            strcat(str,".");
        }
        // 将点击的字符添加到字符串中
        /* if (temp != '0' && strlen(str) < 19) // 防止字符串溢出
        {
            str[strlen(str)] = temp;
            str[strlen(str) + 1] = '\0'; // 确保字符串终止
        } */
        if(x>=550&&x<=634 &&  y>=280 &&y<340)
        {
            printf("取消\n");
           if (strlen(str) > 0) 
                str[strlen(str) - 1] = '\0'; // 删除最后一个字符
            printf("%s",str);
            fflush(stdout);
        }
        if(x>=715&&x<=800 &&  y>=280 &&y<340)
        {
            printf("确定\n");
            break;
        }
    }
    return str;
}
int main(int arge, char **argv)
{
    //定义一个双向循环链表保存商品
    struct single_list *goods_list=slist_init();
    int ret;
    //打开目录读取文件,保存在链表中
    ret=openDIR(argv[1],".bmp",goods_list);
    if (ret == -1)
    {
        printf("打开目录失败\n");
        return 1;
    }
    read_goods_to_list(goods_list);
    //获取坐标
    int flgs;
    int x=0,y=0;
    int get_x=0,get_y=0;
    int i=1;
    //显示user界面图片
    struct single_list *p=goods_list->next;
lb1:
    show_bmp("./user.bmp");//显示(用户界面)
    //p=p->next;
    while (1)
    {
        //显示字体
        char name[]=" 价格:￥";
        char name1[]=" 数量:";
        show_font(name,310,350);
        show_font(name1,310,385);
        //显示商品小图片
        show_anybmp(160,220,316,130,p->goods_list.bmp_path);
        //显示价格、数量
        char temp[20];
        snprintf(temp, sizeof(temp), "%.2f", p->goods_list.price);
        show_font(temp,400,350);
        char temp1[20];
        snprintf(temp1, sizeof(temp1), "%d", p->goods_list.num);
        show_font(temp1,400,385);
        //获取坐标
        flgs=getcrood(&x,&y);
        //点击右切换
        if(x>=660&&x<800 && y>0 && y <= 70)
        {
            p=p->next;
            if(p==goods_list)
                p=p->next;
        }
        //点击左切换
        if(x>=0&&x<125 && y>0 && y <= 70)
        {
            p=p->prev;
            if(p==goods_list)
                p=p->prev;
        }
        //购买商品
        if(x>=635&&x<=770 && y>=345 && y<=409)
        {
            int buy_num;
            show_anybmp(250,300,550,50,"./keyboard.bmp");
            printf("商品购买的数量是：");
            char *input = key_board();
            buy_num = (int)atof(input);
            // 释放动态分配的内存
            free(input);
            printf("需要支付的金额是：%.2f\n",(p->goods_list.price)*(buy_num));
            printf("是否取消购买？ (y/n): ");
            char cancel_option;
            scanf(" %c", &cancel_option); //注意前面的空格，以避免残留字符问题
            if (cancel_option == 'y' || cancel_option == 'Y') 
                printf("取消购买。\n");// 用户取消购买
            else
            {
                // 用户确认购买
                p->goods_list.num -= buy_num;
                show_anybmp(240,265,316,130,"./payment.bmp");
                sleep(7);
                //判断金钱是否支付 收到-1 没有收到-0
                printf("购买成功！\n");
            }
            if(p->goods_list.num<=0)
            {
                printf("商品已经卖完了！\n");
                p->goods_list.num=0;
            }
            goto lb1;
        }
        //点击管理员界面
        if(x>=0&&x<190 && y>380 && y <= 470)
        {
             //密码登录
            //rkey_login();
            while (1)
            {
                show_bmp("./root.bmp");//显示管理员界面
                //显示字体
                char name2[]=" 价格:￥";
                char name3[]=" 数量:";
                show_font(name2,310,350);
                show_font(name3,310,385);
                //显示小图片和数量价格
                show_anybmp(160,220,316,130,p->goods_list.bmp_path);
                char temp[20];
                snprintf(temp, sizeof(temp), "%.2f", p->goods_list.price);
                show_font(temp,405,350);
                char temp1[20];
                snprintf(temp1, sizeof(temp1), "%d", p->goods_list.num);
                show_font(temp1,405,385);
                int flgs1=getcrood(&get_x,&get_y);
                //点击右切换
                if(get_x>=660&&get_x<800 && get_y>0 && get_y <= 70)
                {
                    p=p->next;
                    if(p==goods_list)
                        p=p->next;
                }
                //点击左切换
                if(get_x>=0&&get_x<125 && get_y>0 && get_y <= 70)
                {
                    p=p->prev;
                    if(p==goods_list)
                        p=p->prev;
                }
                //商品上架
                if(get_x>=611&&get_x<800 && get_y>360 && get_y <= 430)
                {
                    int tem=0;
                    printf("1、增加商品 0 退出\n");
                    scanf("%d",&tem);
                    if(tem==1)
                    {
                        while (1)
                        {
                            //增加商品
                            add_goods(goods_list);
                            //写入文件
                            save_goods_to_file(goods_list);
                            int ext;
                            printf("请输入0/1 退出/继续\n");
                            scanf("%d",&ext);
                            if(ext==0)
                            {
                                printf("退出商品上架功能成功\n");
                                break;
                            }
                        }
                    }
                }
                //点击商品，进入商品管理界面
                if(get_x>=316&&get_x<=476 && get_y>=130&&get_y<=350)
                {
                    while (1)
                    {
                        int flgs=1;
                        int x1,y1;
//lb2:
                        getcrood(&x1,&y1);
                        //显示商品界面
                        show_bmp("./goods.bmp");
                        show_anybmp(160,220,316,130,p->goods_list.bmp_path);
                        //显示数量和价格
                        char temp[20];
                        snprintf(temp, sizeof(temp), "%.2f", p->goods_list.price);
                        show_font(temp,405,350);
                        char temp1[20];
                        snprintf(temp1, sizeof(temp1), "%d", p->goods_list.num);
                        show_font(temp1,405,385);
                        //退出界面
                        if(x1>=0&&x1<=125 && y1>=0 && y1<=70)
                        {
                            show_bmp("./root.bmp");
                            break;
                        }
                        //商品修改价格
                        if(x1>=20&&x1<=180 && y1>=300 && y1<=350)
                        {
                            while (1)
                            {
                                int a,b;
                                getcrood(&a,&b);
                                if(a>=0&&a<=125 && b>=0 && b<=70)//退出a == 'n'
                                {
                                    flgs=0;
                                    //goto lb2;
                                    break;
                                }
                                float price=0;
                                //屏幕触摸键盘输入价格
                                show_anybmp(250,300,550,50,"./keyboard.bmp");
                                printf("商品修改的价格是：");
                                char *input = key_board();
                                // 将输入的字符串转换为浮点数并赋值给 price
                                price = (float)atof(input);
                                // 释放动态分配的内存
                                free(input);
                                //修改数据
                                up_goods(1,&price,p,goods_list);
                                /*  int a;
                                printf("1-继续修改价格，0-退出修改功能\n");
                                scanf("%d", &a);
                               if(a == 0 )//退出s
                                {
                                    flgs=0;
                                    printf("1\n");
                                    break;
                                }*/
                            } 
                        }
                        //商品修改数量
                        if(x1>=20&&x1<=180 && y1>=390 && y1<=450)
                        {
                            while (1)
                            {
                                int num;
                                int x2,y2;
                                getcrood(&x2,&y2);
                                if(x2>=0&&x2<=125 && y2>=0 && y2<=70)//退出a == 'n'
                                {
                                    flgs=0;
                                    //goto lb2;
                                    break;
                                }
                                //屏幕触摸键盘输入数量
                                show_anybmp(250,300,550,50,"./keyboard.bmp");
                                printf("商品修改的数量是：");
                                char *input = key_board();
                                num = (int)atof(input);
                                // 释放动态分配的内存
                                free(input);
                                //修改数据
                                up_goods(2,&num,p,goods_list);
                                /* char a;
                                printf("y-继续修改数量，n-退出修改功能\n");
                                getchar();
                                scanf("%c",&a);
                                getchar(); */
                            }
                        }
                        //商品下架
                        if(x1>=620&&x1<=800 && y1>=390 && y1<=450)
                        {
                            //删除数据
                            printf("%p\n",p);
                            struct single_list *temp=p->next;
                            del_goods(p,goods_list);
                            p=temp;
                            if(p==goods_list)
                                p=p->next;
                            printf("商品下架成功\n");
                            printf("%p\n",p);
                            slist_show(goods_list);
                            save_goods_to_file(goods_list);
                            show_bmp("./root.bmp");
                            flgs=0;
                        }
                        //修改成功后退出s
                        if(flgs == 0)
                            break;
                    }
                }
                //退出
                if(get_x>=0&&get_x<180 && get_y>380 && get_y <= 430)
                {
                    printf("退出管理员系统\n");
                    show_bmp("./user.bmp");
                    break;
                }
            }  
        }
    }
    //销毁链表
    while (p->next!=goods_list)
        p=p->next;
    while (p!=goods_list)
    {
        p=p->prev;
        free(p->next);
    }
    return 0;
}	