// ConsoleSnake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"Snake.h"

int main()
{
	CursorVisible(false);
	CSnake snake;
	snake.DrawFram();
	snake.ShowInfo();
	snake.DrawSnake();
	snake.DrawFood();
	SYSTEMTIME temp_time, current_time;
	GetLocalTime(&temp_time);
	while (true)
	{
		GetLocalTime(&current_time);
		if (current_time - temp_time >= snake.GetIntervalTime())		//如果获得的当前时间和之前的时间之差超过了设定的值则移动一次
		{
			temp_time = current_time;
			snake.ClearSnake();
			snake.SnakeForward();
			snake.DrawSnake();
		}
		if (snake.GaneOver())
		{
			PrintString(L"游戏结束，按任意键退出。", 6, 10, RED);
			_getch();
			return 0;
		}
		if (_kbhit())
		{
			snake.ClearSnake();
			switch (GetKey())
			{
				//case ' ':
				//	snake.SnakeForward();
				//	break;
			case UP_KEY:
				snake.MoveSnake(UP);
				break;
			case DOWN_KEY:
				snake.MoveSnake(DOWN);
				break;
			case LEFT_KEY:
				snake.MoveSnake(LEFT);
				break;
			case RIGHT_KEY:
				snake.MoveSnake(RIGHT);
				break;
			case ESC_KEY:
				return 0;
			default:
				break;
			}
			snake.DrawSnake();
		}
		if (snake.SnakeHitFood())
		{
			snake.SnakeEatFood();
			snake.CreateFood();
			snake.DrawFood();
			snake.DrawSnake();
			snake.ShowInfo();
		}
	}
	return 0;
}