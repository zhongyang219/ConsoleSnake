//************************************************************
//本文件包含宏定义、全局常量、枚举类型和全局函数的定义
//************************************************************
#pragma once
#include<Windows.h>
#include<conio.h>

//定义功能键
#define UP_KEY (-1)			//定义上方向键
#define DOWN_KEY (-2)		//定义下方向键
#define LEFT_KEY (-3)		//定义左方向键
#define RIGHT_KEY (-4)		//定义右方向键
//定义字符键
#define PAUSE_KEY 13			//定义暂停键
#define ESC_KEY 27		//定义退出键（按esc键退出）
#define ENTER_KEY 13		//定义回车键

#define BOARD_X 1
#define BOARD_Y 3
#define WIDTH 30
#define HIGHT 23

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum Color
{
	BLACK = 0,
	GRAY = 8,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};


//获取一个键盘输入按键并将其返回
int GetKey()
{
	int key{ _getch() };
	if (key == 0xE0 || key == 0)		//如果获得的按键值为0x0E或0则表示按下了功能键
	{
		switch (_getch())		//按下了功能键需要再次调用_getch函数
		{
			case 72: key = UP_KEY; break;
			case 80: key = DOWN_KEY; break;
			case 75: key = LEFT_KEY; break;
			case 77: key = RIGHT_KEY; break;
			default: break;
		}
	}
	if (key>='a' && key<='z')		//如果按的是小写字母，则自动转换成大写字母
		key -= 32;
	return key;
}

//为SYSTEMTIME结构重载减号运算符，在确保a>b的情况下返回两个时间差的毫秒数，但是返回的值不会超过3000毫秒
int operator-(SYSTEMTIME a, SYSTEMTIME b)
{
	if (a.wSecond == b.wSecond)
		return a.wMilliseconds - b.wMilliseconds;
	else if (a.wSecond - b.wSecond == 1 || a.wSecond - b.wSecond == -59)
		return a.wMilliseconds - b.wMilliseconds + 1000;
	else
		return a.wMilliseconds - b.wMilliseconds + 2000;
}

template<class T>
T Min3(T v1, T v2, T v3)
{
    T min = v1;
    if (v2 < min)
        min = v2;
    if (v3 < min)
        min = v3;
    return min;
}

template<class T>
T Max3(T v1, T v2, T v3)
{
    T max = v1;
    if (v2 > max)
        max = v2;
    if (v3 > max)
        max = v3;
    return max;
}
