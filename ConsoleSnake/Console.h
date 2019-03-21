//************************************************************
//				本文件为控制台相关全局函数的定义
//************************************************************
#pragma once
#include<Windows.h>
#include"Common.h"

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

//计算一个宽字节字符串的长度占用的半角字符数
size_t WcharStrHalfWidthLen(const wchar_t* str)
{
	size_t size{ 0 };
	const size_t length{ wcslen(str) };
	for (int i{ 0 }; i < length; i++)
	{
		if (str[i] >= 0 && str[i] < 128)
			size++;		//如果一个Unicode字符编码在0~127范围内，它占一个半角字符宽度
		else
			size += 2;		//否则它占两个半角字符宽度
	}
	return size;
}

//在x,y坐标处输一个格子
void PrintCell(short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	WriteConsoleOutputCharacterW(handle, L"■", 1, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
}

//在界面的x,y坐标处输出一个数字
void PrintInt(int num, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	wchar_t str[20];
	_itow_s(num, str, 10);
	size_t len{ wcslen(str) };
	WriteConsoleOutputCharacterW(handle, str, len, pos, &unuse);		//输出字符
	FillConsoleOutputAttribute(handle, color, len, pos, &unuse);		//设置颜色
}

//在界面的x,y坐标处输出一个字符串
void PrintString(const wchar_t *str, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	size_t len{ wcslen(str) };
	size_t len_halfwidth{ WcharStrHalfWidthLen(str) };	//字符串占用半角字符数
	WriteConsoleOutputCharacterW(handle, str, len, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, len_halfwidth, pos, &unuse);		//设置颜色
}

//清除控制台的x,y处开始的length个字符
void ClearString(short x, short y, size_t length)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	FillConsoleOutputAttribute(handle, BLACK, length, pos, &unuse);
}

//光标移动到x,y坐标
void GotoXY(short x, short y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//显示或隐藏光标
void CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = visible;
	cci.dwSize = 25;		//光标厚度，取值为1~100
	SetConsoleCursorInfo(handle, &cci);
}
