#include "font.h"
#include "myhead.h"
//初始化Lcd
struct LcdDevice *init_lcd(const char *device)
{
	//申请空间
	struct LcdDevice* lcd = malloc(sizeof(struct LcdDevice));
	if(lcd == NULL)
	{
		return NULL;
	} 

	//1打开设备
	lcd->fd = open(device, O_RDWR);
	if(lcd->fd < 0)
	{
		perror("open lcd fail");
		free(lcd);
		return NULL;
	}
	
	//映射
	lcd->mp = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd->fd,0);

	return lcd;
}
//显示字体
int show_font(char *name,int a, int b)
{
	
    //初始化Lcd
	struct LcdDevice* lcd = init_lcd("/dev/fb0");
			
	//打开字体	
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");
	//字体大小的设置
	fontSetSize(f,35);  //字体大小72，你可以自由设置其它大小
	//创建一个画板（点阵图）
	//参数1和2表示画板区域的宽高
	//参数3表示每个像素占4个字节
	//参数4表示画板的背景颜色getColor(0,255,255,255)
	//                                A  B   G   R
	bitmap *bm = createBitmapWithInit(100,40,4,getColor(0,197,181,255)); //也可使用createBitmapWithInit函数，改变画板颜色
	
	char buf[100]={0};
	strcpy(buf,name);
	//将字体写到点阵图上
	/*
		参数1:你要使用的字体
		参数2:你要使用的画板
		参数3和4:表示汉字在画板上的相对坐标
		参数5:你要显示的汉字
		参数6:汉字的颜色getColor(0,255,0,0)
		                         A  B  G R
	*/
	fontPrint(f,bm,0,0,buf,getColor(0,0,0,0),0);
	
	
	
	//把字体框输出到LCD屏幕上
	/*
		参数2和3表示画板相对于lcd的坐标位置
	*/
	//show_font_to_lcd(lcd->mp,0,0,bm);

	//把字体框输出到LCD屏幕上310 350
	show_font_to_lcd(lcd->mp,a,b,bm);
	
	//关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
	
}
