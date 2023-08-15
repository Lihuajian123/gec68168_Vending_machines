//显示800*480bmp图片
#include "myhead.h"
#define BMP_Pixel_range    800*480*3
#define Board_Pixel_range  800*480*4
int show_bmp(char *pathname)
{
    int bmp=open(pathname,O_RDWR);
    if(bmp==-1)
    {
        perror("图片打开失败！\n");
        return -1;
    }
    
    //读取图片的头信息
    char head[54]={0};
    read(bmp,head,54);
    //读取图片像素点
    char rgb[BMP_Pixel_range];
    read(bmp,rgb,BMP_Pixel_range);

    //关闭图片
    close(bmp);
    
    //打开液晶屏的驱动
    int fd;
    fd=open("/dev/fb0",O_RDWR);
    if(fd==-1)
    {
        perror("液晶屏驱动打开失败！\n");
        return -1;
    }
    //图片适配液晶屏
    char argb[Board_Pixel_range];
    for(int i=0;i<(Board_Pixel_range)/4;i++)
    {
        argb[0+i*4]=rgb[0+i*3];       // b
        argb[1+i*4]=rgb[1+i*3];       // g
        argb[2+i*4]=rgb[2+i*3];       // r
        argb[3+i*4]=0;                // a
    }
    //对LCD液晶屏进行映射
    int(*lcd)[800]= mmap(NULL,Board_Pixel_range, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int(*color)[800] = (void *)argb;
   /*  //把像素数据放入映射空间
    for (int i = 0; i < Board_Pixel_range; i++)
    {
        lcd[i] = argb[i];
    } */
    // 把像素数据放入映射空间(实现图片倒转)
    for (int y = 0; y < 480; y++)
        for (int x = 0; x < 800; x++)
        {
            lcd[y][x] = color[479 - y][x];
        }

    close(fd);
    //解除映射
    munmap(lcd,Board_Pixel_range);
    return 0;
}
/* //显示160*220图片
int show_bmp1(char *pathname)
{
     int bmp=open(pathname,O_RDWR);
    if(bmp==-1)
    {
        perror("图片打开失败！\n");
        return -1;
    }
    
    //读取图片的头信息
    char head[54]={0};
    read(bmp,head,54);
    //读取图片像素点
    char rgb[160*220*3];
    read(bmp,rgb,160*220*3);
    //关闭图片
    close(bmp);
    
    //打开液晶屏的驱动
    int fd;
    fd=open("/dev/fb0",O_RDWR);
    if(fd==-1)
    {
        perror("液晶屏驱动打开失败！\n");
        return -1;
    }
    //图片适配液晶屏
    char argb[160*220*4];
    for(int i=0;i<160*220;i++)
    {
        argb[0+i*4]=rgb[0+i*3];       // b
        argb[1+i*4]=rgb[1+i*3];       // g
        argb[2+i*4]=rgb[2+i*3];       // r
        argb[3+i*4]=0;                // a
    }
    //如何实现将图片映射在中间区域
    int(*color)[160] = (void *)argb;
    // 计算液晶屏中间区域的起始位置
    int lcd_width = 800; // 假设液晶屏宽度为800像素
    int lcd_height = 480; // 假设液晶屏高度为480像素
    int bmp_width = 160; // 图片宽度
    int bmp_height = 220; // 图片高度
    int x_offset = (lcd_width - bmp_width) / 2; // 水平偏移量n
    it y_offset = (lcd_height - bmp_height) / 2; // 垂直偏移量
     // 映射液晶屏的映射空间到用户空间
    int *lcd_map = (int *)mmap(NULL, lcd_width * lcd_height * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (lcd_map == MAP_FAILED)
    {
        perror("映射失败！");
        close(fd);
        return -1;
    }
     // 将图片像素数据放入液晶屏中间区域映射空间
    for (int y = 0; y < bmp_height; y++)
    {
        for (int x = 0; x < bmp_width; x++)
        {
            int lcd_x = x + x_offset;
            int lcd_y = y + y_offset;
            int image_pixel = color[bmp_height-y][x]; // 假设color是像素数据的数组
            lcd_map[lcd_y * lcd_width + lcd_x] = image_pixel;
        }
    }
    // 解除映射
    munmap(lcd_map, lcd_width * lcd_height * 4);
    // 关闭文件和液晶屏驱动
    close(fd);
} */
int show_anybmp(int w,int h,int x,int y,char *bmpname)
{
	int bmpfd;
	int lcdfd;
	int i,j;
	//定义int类型的指针指向lcd在显存中的首地址
	int *lcdmem;

	//定义数组存放像素点的RGB
	char bmpbuf[w*h*3];
	//定义数组存放转换得到的ARGB
	int lcdbuf[w*h]; // int占4字节
	int tempbuf[w*h];
	//打开你要显示的bmp图片   w*h
	bmpfd=open(bmpname,O_RDWR);
	if(bmpfd==-1)
	{
		perror("打开图片");
		return -1;
	}
	
	//打开lcd的驱动
	lcdfd=open("/dev/fb0",O_RDWR);
	if(lcdfd==-1)
	{
		perror("打开lcd");
		return -1;
	}
	
	//映射得到lcd在显存中对应的首地址
	lcdmem=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	if(lcdmem==NULL)
	{
		perror("映射lcd");
		return -1;
	}
	
	//跳过前面没有用的54字节
	lseek(bmpfd,54,SEEK_SET);
	
	//判断bmp图片的宽所占的字节数能否被4整除
	if((w*3)%4!=0)
	{
		for(i=0; i<h; i++)
		{
			read(bmpfd,&bmpbuf[i*w*3],w*3);
			lseek(bmpfd,4-(w*3)%4,SEEK_CUR);  //跳过填充的垃圾数据
		}
	}
	else
		//从55字节读取bmp的像素点颜色值
		read(bmpfd,bmpbuf,w*h*3);  //bmpbuf[0] B  bmpbuf[1] G bmpbuf[2] R  一个像素点的RGB
	                               //bmpbuf[3]  bmpbuf[4]  bmpbuf[5] 
	//3字节的RGB-->4字节的ARGB   位运算+左移操作
	for(i=0; i<w*h; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;
	                   //00[2][1][0]
					   
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			//*(lcdmem+(y+j)*800+x+i)=lcdbuf[j*w+i];  图片颠倒
			*(lcdmem+(y+j)*800+x+i)=lcdbuf[(h-1-j)*w+i];
	
	//关闭
	close(bmpfd);
	close(lcdfd);
	//解除映射
	munmap(lcdmem,800*480*4);
	return 0;
}