#include "myhead.h"
#include </usr/include/linux/input.h>

int getcrood(int *gx, int *gy)
{
    // 1.打开触摸屏设备文件
    int fd = open("/dev/input/event0", O_RDWR);
    if (fd < 0)
    {
        printf("打开触摸屏失败\n");
    }

    int x = 0, y = 0;
    int t_x, t_y; // 按下的坐标

    while (1)
    {
        // 2.读取触摸屏信息
        struct input_event xy;
        read(fd, &xy, sizeof(xy));

        // 判断是否为触摸屏的X 轴事件
        if (xy.type == EV_ABS && xy.code == ABS_X)
        {
            // 转换坐标
            x = xy.value * 800 / 1024;
            *gx = x;
            // 输出X轴的坐标值
            //  printf("x=%d\n", x);
        }

        // 判断是否为触摸屏的X 轴事件
        if (xy.type == EV_ABS && xy.code == ABS_Y)
        {
            // 转换坐标
            y = xy.value * 480 / 600;
            *gy = y;
            // 输出X轴的坐标值
            // printf("y=%d\n", y);
        }

        // 获取按钮是否按下的状态
        if (xy.type == EV_KEY && xy.code == BTN_TOUCH)
        {
            //  printf("touch=%d\n", xy.value);

            if (xy.value == 1) // 按下
            {
                // 保存按下的坐标
                t_x = x;
                t_y = y;
            }

            if (xy.value == 0) // 松开
            {
                break; // 跳出循环
            }
        }
    }

    // 关闭屏幕
    close(fd);
    return 0;
 /*    // 根据按下与松开的差值判断滑动的方向
    if (t_x - x > 100)
    {
        printf("左滑动\n");
        return 3;
    }

    if (t_x - x < -100)
    {
        printf("右滑动\n");
        return 4;
    }

    if (t_y - y > 100)
    {
        printf("上滑动\n");
        return 1;
    }

    if (t_y - y < -100)
    {
        printf("下滑动\n");
        return 2;
    }*/
} 
