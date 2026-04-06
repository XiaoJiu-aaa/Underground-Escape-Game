#pragma once

#include"Player_Actions.h"


IMAGE   g_imgMap(WIDTH, HEIGHT);		// 矿井平面图
DWORD*  g_bufMap;						// 矿井平面图的显存指针
IMAGE   g_imgRender(WIDTH, HEIGHT);		// 渲染
DWORD*  g_bufRender;					    // 渲染的显存指针
DWORD*  g_bufScreen;					    // 屏幕的显存指针


//初始化
void	ReadyGo();									// 准备开始游戏
void	InitGame();									// 初始化游戏数据



// 矿井生成
void	MakeMaze(int width, int height);			                         // 初始化(注：宽高必须是奇数)
void	TravelMaze(int x, int y, BYTE** aryMap);	                         // 遍历 (x, y) 四周
void	DrawWall(int x, int y, bool left, bool top, bool right, bool bottom);//绘制一面墙
void	DrawExit();									                         // 绘制出口


void Paint();	                                                             // 绘制视野范围内的矿井