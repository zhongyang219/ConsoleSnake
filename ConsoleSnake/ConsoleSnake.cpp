// ConsoleSnake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"Snake.h"

//#define SNAK_TEST

int main()
{
#ifndef SNAK_TEST
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
            snake.DrawFood();
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
            case ENTER_KEY:
                _getch();
                break;
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
        Sleep(10);
	}

#else
    //测试代码
    ////CSnake::Point p1{ 0,0 }, p2{ 1,0 }, p3{};
    //std::vector<CSnake::Point> snake_test;
    //snake_test.push_back(CSnake::Point());
    //snake_test.push_back(CSnake::Point());
    //snake_test.push_back(CSnake::Point());

    //PrintCell(point.x, point.y, Color::WHITE, CSnake::CheckPointsShape(s))
    PrintCell(0, 0, Color::WHITE, CELL_H);
    PrintCell(1, 0, Color::WHITE, CELL_H);
    PrintCell(2, 0, Color::WHITE, CELL_H);
    PrintCell(3, 0, Color::WHITE, CELL_SQUARE);

#endif
	return 0;
}