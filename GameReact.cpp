

#include"GameReact.h"
#include"Data_Storage.h"
#include"Game_Pause.h"
#include"EndGame.h"

#include<easyx.h>
#include<graphics.h>
#include<math.h>
#include<stdio.h>



#define PI			3.141592653589		// 圆周率
#define UNIT_GROUND	0					// 表示地面
#define UNIT_WALL	1					// 表示墙

#define LIGHT_A		PI / 3				// 灯光的角度范围

#define SCREENWIDTH  1024               //窗口宽度
#define SCREENHEIGHT 1024               //窗口高度

#define	WIDTH		900				    // 矿井的宽度
#define	HEIGHT		900					// 矿井的高度

#define	UNIT		20					// 每个墙壁单位的大小
#define PLAYER_R	5					// 游戏者的半径

POINT	g_ptPlayer;						// 游戏者的位置
POINT	g_ptMouse;						// 鼠标位置

const SIZE different_map[3] = { {23,23},{31,31},{43,43}, };		// 矿井地图的尺寸(基于 UNIT 单位)
const POINT g_utPlayer = { 1,1 };								// 游戏者的位置(基于 UNIT 单位)
const POINT different_exit[3] = { {21,22},{29,30},{41,42} };	// 出口位置(基于 UNIT 单位)
const POINT g_ptOffset = { 10,10 };								// 矿井显示在屏幕上的偏移量

IMAGE   g_imgMap(WIDTH, HEIGHT);		// 矿井平面图
DWORD* g_bufMap;						// 矿井平面图的显存指针
IMAGE   g_imgRender(WIDTH, HEIGHT);		// 渲染
DWORD* g_bufRender;					    // 渲染的显存指针
DWORD* g_bufScreen;					    // 屏幕的显存指针


IMAGE tracks(WIDTH, HEIGHT);            //足迹图
DWORD* g_tracks;						//足迹图的显存指针


enum CMD 
{
	CMD_UP = 1,
	CMD_DOWN = 2, 
	CMD_LEFT = 4, 
	CMD_RIGHT = 8, 
	CMD_PAUSE = 16 
};//用户控制枚举


//绘制
// 在指定位置和角度“照明”
void Lighting(int _x, int _y, double _a, DWORD* g_bufMap, DWORD* g_bufRender,int flashlight_set)
{
	int light_r[3] = {60,100,150};

	int i;		// 定义循环变量
	int x, y;	// 定义临时坐标
	double a;	// 定义临时角度
	
	// 计算灯光照亮的角度区域
	double a1 = _a - LIGHT_A / 2;
	double a2 = _a + LIGHT_A / 2;
	for (a = a1; a < a2; a += PI / 360)					// 扇形循环
	{
		for (int r = 0; r < light_r[flashlight_set]; r++)				// 半径循环
		{
			// 计算照射到的位置
			x = (int)(_x + cos(a) * r);
			y = (int)(_y + sin(a) * r);

			// 光线超出屏幕范围，终止
			// (为了简化全凭模糊运算，不处理最上和最下一行)
			if (x < 0 || x >= WIDTH || y <= 0 || y >= HEIGHT - 1)
				break;

			// 光线碰到建筑物，终止
			if (g_bufMap[y * WIDTH + x])
				break;

			// 光线叠加
			g_bufRender[y * WIDTH + x] += 0x202000;		// 0x202000 是很淡的黄色
		}
	}

	// 计算光照扇形区域的最小包围矩形
	// 方法：获得 7 个点的最值：圆心、圆弧两端、圆与 xy 轴的 4 个交点
	// 第一步：初始化 7 个点
	POINT pt[7];
	pt[0].x = _x;									pt[0].y = _y;
	pt[1].x = int(_x + light_r[flashlight_set] * cos(a1) + 0.5);	pt[1].y = int(_y + light_r[flashlight_set] * sin(a1) + 0.5);
	pt[2].x = int(_x + light_r[flashlight_set] * cos(a2) + 0.5);	pt[2].y = int(_y + light_r[flashlight_set] * sin(a2) + 0.5);

	for (a = ceil(a1 * 4 / (2 * PI)) * (PI / 2), i = 3; a < a2; a += PI / 2, i++)
	{
		pt[i].x = int(_x + light_r[flashlight_set] * cos(a) + 0.5);
		pt[i].y = int(_y + light_r[flashlight_set] * sin(a) + 0.5);
	}

	// 第二步：获取 7 个点的最大最小值，得到最小包围矩形
	i--;
	RECT r = { pt[i].x, pt[i].y, pt[i].x, pt[i].y };

	for (--i; i >= 0; i--)
	{
		if (pt[i].x < r.left)	r.left = pt[i].x;
		if (pt[i].x > r.right)	r.right = pt[i].x;
		if (pt[i].y < r.top)	r.top = pt[i].y;
		if (pt[i].y > r.bottom)	r.bottom = pt[i].y;
	}

	// 调整矩形范围
	if (r.left < 0)				r.left = 0;
	if (r.top < 1)				r.top = 1;
	if (r.right >= WIDTH)		r.right = WIDTH - 1;
	if (r.bottom >= HEIGHT - 1)	r.bottom = HEIGHT - 2;

	// 修正曝光过度的点
	for (y = r.top; y <= r.bottom; y++)
		for (x = r.left; x <= r.right; x++)
		{
			i = y * WIDTH + x;
			if (g_bufRender[i] > 0xffff00)
				g_bufRender[i] = 0xffff00;
		}

	// 将光线模糊处理(避开建筑物)
	for (y = r.top; y <= r.bottom; y++)
		for (x = r.left; x <= r.right; x++)
		{
			i = y * WIDTH + x;
			if (!g_bufMap[i])
				g_bufRender[i] = RGB(
					(GetRValue(g_bufRender[i - WIDTH]) + GetRValue(g_bufRender[i - 1]) + GetRValue(g_bufRender[i])
						+ GetRValue(g_bufRender[i + 1]) + GetRValue(g_bufRender[i + WIDTH])) / 5,
					(GetGValue(g_bufRender[i - WIDTH]) + GetGValue(g_bufRender[i - 1]) + GetGValue(g_bufRender[i])
						+ GetGValue(g_bufRender[i + 1]) + GetGValue(g_bufRender[i + WIDTH])) / 5,
					(GetBValue(g_bufRender[i - WIDTH]) + GetBValue(g_bufRender[i - 1]) + GetBValue(g_bufRender[i])
						+ GetBValue(g_bufRender[i + 1]) + GetBValue(g_bufRender[i + WIDTH])) / 5);
		}
}

// 绘制游戏者
void DrawPlayer()
{
	// 画安全帽
	setlinecolor(DARKGRAY);
	circle(g_ptPlayer.x, g_ptPlayer.y, 5);
}


// 获取用户输入的命令
int	GetCmd()
{
	int c = 0;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
		(GetAsyncKeyState('A') & 0x8000))		c |= CMD_LEFT;

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
		(GetAsyncKeyState('D') & 0x8000))		c |= CMD_RIGHT;

	if ((GetAsyncKeyState(VK_UP) & 0x8000) ||
		(GetAsyncKeyState('W') & 0x8000))		c |= CMD_UP;

	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
		(GetAsyncKeyState('S') & 0x8000))		c |= CMD_DOWN;

	
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_PAUSE;

	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		g_ptMouse.x = m.x;
		g_ptMouse.y = m.y;
	}

	return c;
}

// 向上移动
void OnUp()
{
	int i = (g_ptPlayer.y - 6) * WIDTH + (g_ptPlayer.x - 5) + 1;
	int j;
	for (j = 0; j < 5; j++, i += 2)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.y--;
}

// 向左移动
void OnLeft()
{
	int i = (g_ptPlayer.y - 5) * WIDTH + (g_ptPlayer.x - 5);
	int j;
	for (j = 0; j < 5; j++, i += WIDTH)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.x--;
}

// 向右移动
void OnRight()
{
	int i = (g_ptPlayer.y - 5) * WIDTH + (g_ptPlayer.x + 5) + 1;
	int j;
	for (j = 0; j < 5; j++, i += WIDTH)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.x++;
}

// 向下移动
void OnDown()
{
	int i = (g_ptPlayer.y + 5) * WIDTH + (g_ptPlayer.x - 5) + 1;
	int j;
	for (j = 0; j < 5; j++, i += 2)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.y++;
}

// 检查是否到出口
bool CheckWin(int difficult_set)
{
	return (g_ptPlayer.y >= different_exit[difficult_set].y * UNIT + UNIT / 2 + g_ptOffset.y);
}


//显示氧气剩余
void Display_Oxygen_rest(int*len, bool oxygen_set,int tmp,int difficult_set)
{
	if (oxygen_set)
	{
		settextstyle(50, 0, "Ravie");
		setfillcolor(RGB(56, 170, 255));
		settextcolor(WHITE);
		setlinecolor(BLACK);

		fillroundrect(SCREENWIDTH / 2 - 500, 0, SCREENWIDTH / 2 + 500, 50, 25, 25);
		char str[] = "Oxygen is enough!";
		outtextxy(SCREENWIDTH / 2 - textwidth(str) / 2, 0, str);
		return;
	}


	if (*len > 750) setfillcolor(RGB(8, 255, 192));
	if (*len < 750 && *len>500) setfillcolor(RGB(199, 153, 16));
	if (*len<500 && *len>250) setfillcolor(RGB(255, 93, 29));
	if (*len < 250) setfillcolor(RED);

	setlinecolor(BLACK);
	fillroundrect(SCREENWIDTH / 2 - *len / 2, 0, SCREENWIDTH / 2 + *len / 2, 50, 25, 25);
	if((tmp%48==0 && difficult_set==2)||
	   (tmp%24==0 && difficult_set==1)||
	   (tmp%16==0 && difficult_set==0))(*len)--;
}

//显示行动轨迹
void Display_Tracks(int p_x,int p_y,bool tracks_set)
{
	if (tracks_set == true) return;
	// 设置绘图目标为轨迹图像
	SetWorkingImage(&tracks);

	// 绘制轨迹点
	setfillcolor(RGB(117, 117, 117));
	solidcircle(p_x, p_y, 2);

	// 恢复绘图目标
	SetWorkingImage(NULL);
}

// 准备开始游戏
void ReadyGo(bool tracks_set,int difficult_set,int flashlight_set)
{
	// 初始化
	InitGame(difficult_set);

	// 停电前兆
	int time[7] = { 1000, 50, 500, 50, 50, 50, 50 };
	int i, x, y;
	for (i = 0;i < 7; i++)
	{
		if (i % 2 == 0)
		{
			putimage(SCREENWIDTH/2- different_map[difficult_set].cx *10, SCREENHEIGHT / 2 - different_map[difficult_set].cy * 10, &g_imgMap);
		}
		else
		{
			clearrectangle(0, 50, SCREENHEIGHT - 1, SCREENHEIGHT - 1);
		}
		Sleep(time[i]);
	}
	// 电力缓慢中断
	for (i = 255; i >= 0; i -= 5)
	{
		for (y = (SCREENHEIGHT - 1) * SCREENWIDTH; y >= 0; y -= SCREENWIDTH)
		{
			for (x = 0; x < SCREENWIDTH; x++)
			{
				if (g_bufScreen[y + x] != 0)
				{
					g_bufScreen[y + x] = g_bufScreen[y + x] - 0x050505;
				}
			}
		}
		FlushBatchDraw();
		Sleep(50);
	}

	// 绘制游戏区
	Paint(tracks_set, difficult_set,flashlight_set);
}
// 初始化游戏数据
void InitGame(int difficult_set)
{
	// 获得窗口显存指针
	g_bufRender = GetImageBuffer(&g_imgRender);//渲染
	g_bufMap = GetImageBuffer(&g_imgMap);//矿井
	g_bufScreen = GetImageBuffer(NULL);
	g_tracks = GetImageBuffer(&tracks);//足迹

	// 设置 Render 环境
	SetWorkingImage(&g_imgRender);
	setbkmode(TRANSPARENT);
	SetWorkingImage(NULL);

	// 初始化轨迹图像为全透明
	SetWorkingImage(&tracks);
	cleardevice();

	// 创建矿井
	MakeMaze(different_map[difficult_set].cx, different_map[difficult_set].cy, difficult_set);

	// 设置游戏者位置
	g_ptPlayer.x = g_utPlayer.x * UNIT + UNIT / 2 + g_ptOffset.x;
	g_ptPlayer.y = g_utPlayer.y * UNIT + UNIT / 2 + g_ptOffset.y;
}


// 初始化(注：宽高必须是奇数)
void MakeMaze(int width, int height,int difficult_set)
{
	if (width % 2 != 1 || height % 2 != 1)
	{
		printf("宽高不是奇数，生成失败!");
		return;//不是奇数直接返回
	}

	// 定义矿井二维数组，并初始化全部为墙壁
	// 宽高比实际多 2，是因为两端各有一个“哨兵”，用于方便处理数据
	BYTE** aryMap = (BYTE**)malloc((width + 2) * sizeof(BYTE*));
	for (int x = 0; x < width + 2; x++)
	{
		aryMap[x] = (BYTE*)malloc((height + 2) * sizeof(BYTE));
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
	aryMap[different_exit[difficult_set].x + 1][different_exit[difficult_set].y + 1] = UNIT_GROUND;

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

	// 释放内存
	for (int i = 0; i < width + 2; i++) {
		free(aryMap[i]);
		aryMap[i] = NULL;
	}
	free(aryMap);
	aryMap = NULL;
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
void Paint(bool tracks_set,int difficult_set,int flashlight_set)
{
	Display_Tracks(g_ptPlayer.x, g_ptPlayer.y,tracks_set);
	// 设置绘图目标为 Render 对象
	SetWorkingImage(&g_imgRender);

	// 清空 Render 对象
	cleardevice();

	// 计算视野角度
	double dx, dy, a;

	// 计算矿井图像在屏幕上的偏移量
	int offsetX = SCREENWIDTH / 2 - different_map[difficult_set].cx * 10;
	int offsetY = SCREENHEIGHT / 2 - different_map[difficult_set].cy * 10;

	// 将鼠标屏幕坐标转换为矿井图像内的坐标
	int mouseInMapX = g_ptMouse.x - offsetX;
	int mouseInMapY = g_ptMouse.y - offsetY;

	// 计算差值
	dx = mouseInMapX - g_ptPlayer.x;
	dy = mouseInMapY - g_ptPlayer.y;

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

	

	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++) 
		{
			DWORD trackColor = g_tracks[y * WIDTH + x];
			if (trackColor != 0)
			{  // 如果不是黑色（透明）
				g_bufRender[y * WIDTH + x] = trackColor;
			}
		}
	}

	// 绘制灯光
	Lighting(g_ptPlayer.x, g_ptPlayer.y, a, g_bufMap, g_bufRender,flashlight_set);

	// 画游戏者
	DrawPlayer();

	// 画出口
	DrawExit(difficult_set);

	// 设置绘图目标为窗口
	SetWorkingImage(NULL);

	// 显示到窗口上
	putimage(SCREENWIDTH / 2 - different_map[difficult_set].cx * 10,SCREENHEIGHT/2- different_map[difficult_set].cy * 10, &g_imgRender);
}

//绘制出口
void DrawExit(int difficult_set)
{
	settextstyle(12, 0, "宋体");
	outtextxy(different_exit[difficult_set].x * UNIT + g_ptOffset.x, different_exit[difficult_set].y * UNIT + g_ptOffset.y + 8, _T("Export"));
}

//处理玩家操作，游玩
int Game_Body(const int difficult_set, const bool oxygen_set, const bool tracks_set,const int flashlight_set)
{
	setbkcolor(BLACK);
	cleardevice();

	ReadyGo(tracks_set, difficult_set,flashlight_set);

	int blood = 1000;
	int tmp = 0;
	int c;

	while (true)
	{
		// 获得用户输入
		c = GetCmd();
		 
		// 处理用户输入
		if (c & CMD_UP)			OnUp();
		if (c & CMD_DOWN)		OnDown();
		if (c & CMD_LEFT)		OnLeft();
		if (c & CMD_RIGHT)		OnRight();
		//游戏暂停
		if (c & CMD_PAUSE)
		{
			if (Draw_Pause() == GAMEEND) return Choose_BackMenu;
			continue;
		}

		BeginBatchDraw();
		//显示氧气剩余
		Display_Oxygen_rest(&blood, oxygen_set,tmp, difficult_set);

		// 绘制场景
		Paint(tracks_set, difficult_set, flashlight_set);

		EndBatchDraw();
		
		if(blood==0)return Draw_EndGame(FAULT,difficult_set,oxygen_set,tracks_set,flashlight_set,blood);
		if(CheckWin(difficult_set))return Draw_EndGame(WIN, difficult_set, oxygen_set, tracks_set, flashlight_set,blood);
		
		tmp++;

		// 延时
		Sleep(10);
	}
}