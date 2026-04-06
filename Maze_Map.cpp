



#include"Maze_Map.h"


#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

// 准备开始游戏
void ReadyGo()
{
	// 初始化
	InitGame();

	// 停电前兆
	int time[7] = { 1000, 50, 500, 50, 50, 50, 50 };
	int i, x, y;
	for (i = 0; i < 7; i++)
	{
		if (i % 2 == 0)
		{
			putimage(12,87, &g_imgMap);
			DrawPlayer();
			DrawExit();
		}
		else
			clearrectangle(0, 0, WIDTH - 1, HEIGHT - 1);
		Sleep(time[i]);
	}
	// 电力缓慢中断
	for (i = 255; i >= 0; i -= 5)
	{
		for (y = (HEIGHT - 1) * SCREENWIDTH; y >= 0; y -= SCREENWIDTH)
		{
			for (x = 0; x < WIDTH; x++)
			{
				if (g_bufScreen[y + x] != 0)
				{
					g_bufScreen[y + x] = g_bufScreen[y + x] - 0x050505;
				}
			}
		}

		FlushBatchDraw();
		DrawPlayer();
		DrawExit();
		Sleep(50);
	}

	// 绘制游戏区
	Paint();
}
// 初始化游戏数据
void InitGame()
{
	// 获得窗口显存指针
	g_bufRender = GetImageBuffer(&g_imgRender);
	g_bufMap = GetImageBuffer(&g_imgMap);
	g_bufScreen = GetImageBuffer(NULL);

	// 设置 Render 环境
	SetWorkingImage(&g_imgRender);
	setbkmode(TRANSPARENT);
	SetWorkingImage(NULL);

	// 创建矿井
	MakeMaze(g_utMap.cx, g_utMap.cy);

	// 设置游戏者位置
	g_ptPlayer.x = g_utPlayer.x * UNIT + UNIT / 2 + g_ptOffset.x;
	g_ptPlayer.y = g_utPlayer.y * UNIT + UNIT / 2 + g_ptOffset.y;
}




// 初始化(注：宽高必须是奇数)
void MakeMaze(int width, int height)
{
	if (width % 2 != 1 || height % 2 != 1)
	{
		printf("宽高不是奇数，生成失败!");
		return;//不是奇数直接返回
	}

	// 定义矿井二维数组，并初始化全部为墙壁
	// 宽高比实际多 2，是因为两端各有一个“哨兵”，用于方便处理数据
	BYTE** aryMap = (BYTE**)malloc((width+2)*sizeof(BYTE*));
	for (int x = 0; x < width + 2; x++)
	{
		aryMap[x] = new BYTE[height + 2];
		memset(aryMap[x], UNIT_WALL, height + 2);
	}

	// 定义边界(哨兵功能)
	for (int x = 0; x <= width + 1; x++)
	{
		aryMap[x][0] = aryMap[x][height + 1] = UNIT_GROUND;
	}
		
	for (int y = 1; y <= height; y++)
	{
		aryMap[0][y] = aryMap[width + 1][y] = UNIT_GROUND;
	}

	// 从任意点开始遍历生成矿井
	TravelMaze(((rand() % (width - 1)) & 0xfffe) + 2, ((rand() % (height - 1)) & 0xfffe) + 2, aryMap);

	// 设置出口
	aryMap[g_utExit.x + 1][g_utExit.y + 1] = UNIT_GROUND;

	// 将矿井绘制在 IMAGE 对象上
	SetWorkingImage(&g_imgMap);
	cleardevice();
	for (int y = 1; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
			if (aryMap[x][y] == UNIT_WALL)
			{
				DrawWall(x, y, 
					aryMap[x - 1][y] == UNIT_WALL,
					aryMap[x][y - 1] == UNIT_WALL,
					aryMap[x + 1][y] == UNIT_WALL,
					aryMap[x][y + 1] == UNIT_WALL);
			}
		}
	}
	SetWorkingImage(NULL);
}

// 遍历 (x, y) 四周
void TravelMaze(int x, int y, BYTE** aryMap)
{
	// 定义遍历方向
	int d[4][2] = { 0, 1, 1, 0, 0, -1, -1, 0 };

	// 将遍历方向乱序

	int t;
	for (int i = 0; i < 4; i++)
	{
		int n = rand() % 4;
		t = d[i][0], d[i][0] = d[n][0], d[n][0] = t;
		t = d[i][1], d[i][1] = d[n][1], d[n][1] = t;
	}

	// 尝试周围四个方向
	aryMap[x][y] = UNIT_GROUND;
	for (int i = 0; i < 4; i++)
	{
		if (aryMap[x + 2 * d[i][0]][y + 2 * d[i][1]] == UNIT_WALL)
		{
			aryMap[x + d[i][0]][y + d[i][1]] = UNIT_GROUND;
			TravelMaze(x + d[i][0] * 2, y + d[i][1] * 2, aryMap);		// 递归
		}
	}
}

//绘制一面墙
void DrawWall(int x, int y, bool left, bool top, bool right, bool bottom)
{
	// 墙壁厚 4 pixel
	int cx, cy;
	cx = x * UNIT - UNIT / 2 - 2 + 10;
	cy = y * UNIT - UNIT / 2 - 2 + 10;
	if (left)	solidrectangle(x * UNIT - UNIT + 10, cy, cx + 4, cy + 4);
	if (top)	solidrectangle(cx, y * UNIT - UNIT + 10, cx + 4, cy + 4);
	if (right)	solidrectangle(cx, cy, x * UNIT + 9, cy + 4);
	if (bottom)	solidrectangle(cx, cy, cx + 4, y * UNIT + 9);
}

// 绘制视野范围内的矿井
void Paint()
{
	// 设置绘图目标为 Render 对象
	SetWorkingImage(&g_imgRender);

	// 清空 Render 对象
	cleardevice();

	// 计算视野角度
	double dx, dy, a;
	dx = g_ptMouse.x - g_ptPlayer.x;
	dy = g_ptMouse.y - g_ptPlayer.y;
	if (dx == 0 && dy == 0)
	{
		a = 0;
	}
	else if (dx != 0 && dy != 0)
	{
		a = atan(dy / dx);
	}
	else if (dx == 0)
	{
		a = (dy > 0) ? PI / 2 : PI * 3 / 2;
	}
	else
	{
		a = 0;
	}

	if (dx < 0)	a += PI;
	if (a < 0) a += PI * 2;

	// 绘制灯光
	Lighting(g_ptPlayer.x, g_ptPlayer.y, a,g_bufMap, g_bufRender);

	// 画游戏者
	DrawPlayer();

	// 画出口
	DrawExit();

	// 设置绘图目标为窗口
	SetWorkingImage(NULL);

	// 显示到窗口上
	putimage(12, 87, &g_imgRender);
}
