#pragma once

#define Choose_AgainNew 1
#define Choose_BackMenu 2
#define Choose_BreakGame 3

#define WIN 1
#define FAULT 0



void AgainNew_Button(int msg_x, int msg_y);		//重新开始一局 
void BackMenu_Button(int msg_x, int msg_y);		//返回游戏主菜单
void BreakGame_Button(int msg_x, int msg_y);	//退出游戏



/////////////////////////判断鼠标是否在按钮上////////////////////////////////

bool Is_AgainNew_Button(int msg_x,int msg_y);

bool Is_BackMenu_Button(int msg_x, int msg_y);

bool Is_BreakGame_Button(int msg_x, int msg_y);

void Display_core(int core);//显示分数

void Draw_Result(int result);	//绘制结束标题
int Draw_EndGame(int result, int difficult_set, bool oxygen_set, bool tracks_set, int flashlight_set,int blood);	//绘制游戏结束画面

