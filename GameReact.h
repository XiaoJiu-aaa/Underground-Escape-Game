#pragma once


#include<easyx.h>




void Display_Oxygen_rest(int*len, bool oxygen,int tmp, int difficult_set);//显示剩余氧气量
void Display_Tracks(int p_x, int p_y, bool tracks_set);										  //显示行动轨迹

// 处理用户控制
int		GetCmd();									// 获取用户输入的命令
void	OnUp();										// 向上移动
void	OnLeft();									// 向左移动
void	OnRight();									// 向右移动
void	OnDown();									// 向下移动
bool	CheckWin(int difficult_set);				// 检查是否到出口


//绘制
void	Lighting(int _x, int _y, double _a, DWORD* g_bufMap, DWORD* g_bufRender, int flashlight_set);		// 在指定位置和角度“照明”
void	DrawPlayer();																						// 绘制游戏者
void    Paint(bool tracks_set, int difficult_set,int flashlight_set);										// 绘制视野范围内的矿井

//初始化
void	ReadyGo(bool tracks_set,int difficult_set, int flashlight_set);			// 准备开始游戏
void	InitGame(int difficult_set);											// 初始化游戏数据



// 矿井生成
void	MakeMaze(int width, int height, int difficult_set);			         // 初始化(注：宽高必须是奇数)
void	TravelMaze(int x, int y, BYTE** aryMap);	                         // 遍历 (x, y) 四周
void	DrawWall(int x, int y, bool left, bool top, bool right, bool bottom);//绘制一面墙
void	DrawExit(int difficult_set);									     // 绘制出口


int		Game_Body(const int difficult_set, const bool oxygen_set, const bool tracks_set, const int flashlight_set);
