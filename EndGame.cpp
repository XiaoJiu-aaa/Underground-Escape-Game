



#include"EndGame.h"
#include"Data_Storage.h"
#include<easyx.h>
#include<stdio.h>
#include<string.h>

#define Window_W 1024
#define Window_H 1024

#define BUTTON_W 220
#define BUTTON_H 50



////////////////////////////////////按钮绘制/////////////////////////////////////

//重新开始一局按钮
void AgainNew_Button(int msg_x, int msg_y)
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(140, 140, 140));
	if (Is_AgainNew_Button(msg_x,msg_y)) setfillcolor(YELLOW);

	char str[] = "Again New";
	settextstyle(40, 0, "Ravie");
	settextcolor(BROWN);

	fillroundrect(Window_W / 2 - BUTTON_W / 2, 400, Window_W / 2 + BUTTON_W / 2, 400 + BUTTON_H, 25, 25);

	outtextxy(Window_W / 2 - textwidth(str) / 2, 400 + BUTTON_H / 2 - textheight(str) / 2, str);
}

//返回游戏主菜单按钮
void BackMenu_Button(int msg_x, int msg_y)
{
	setlinecolor(BLACK);
	setfillcolor(RGB(140, 140, 140));
	if (Is_BackMenu_Button(msg_x, msg_y)) setfillcolor(YELLOW);

	char str[] = "Back Menu";
	settextstyle(40, 0, "Ravie");
	settextcolor(BROWN);

	fillroundrect(Window_W / 2 - BUTTON_W / 2, 500, Window_W / 2 + BUTTON_W / 2, 500 + BUTTON_H, 25, 25);

	outtextxy(Window_W / 2 - textwidth(str) / 2, 500 + BUTTON_H / 2 - textheight(str) / 2, str);
}

//退出游戏按钮
void BreakGame_Button(int msg_x, int msg_y)
{
	setlinecolor(BLACK);
	setfillcolor(RGB(140, 140, 140));
	if (Is_BreakGame_Button(msg_x, msg_y)) setfillcolor(YELLOW);

	char str[] = "Break";
	settextstyle(40, 0, "Ravie");
	settextcolor(BROWN);

	fillroundrect(Window_W / 2 - BUTTON_W / 2, 600, Window_W / 2 + BUTTON_W / 2, 600 + BUTTON_H, 25, 25);

	outtextxy(Window_W / 2 - textwidth(str) / 2, 600 + BUTTON_H / 2 - textheight(str) / 2, str);
}


////////////////////////////////////判断鼠标位置//////////////////////////////////


bool Is_AgainNew_Button(int msg_x, int msg_y)
{
	if (msg_x<Window_W / 2 + BUTTON_W / 2 && msg_x>Window_W / 2 - BUTTON_W / 2 && msg_y < 400 + BUTTON_H && msg_y>400) return true;
	return false;
}

bool Is_BackMenu_Button(int msg_x, int msg_y)
{
	if (msg_x<Window_W / 2 + BUTTON_W / 2 && msg_x>Window_W / 2 - BUTTON_W / 2 && msg_y < 500 + BUTTON_H && msg_y>500) return true;
	return false;
}

bool Is_BreakGame_Button(int msg_x, int msg_y)
{
	if (msg_x<Window_W / 2 + BUTTON_W / 2 && msg_x>Window_W / 2 - BUTTON_W / 2 && msg_y < 600 + BUTTON_H && msg_y>600) return true;
	return false;
}


////////////////////////////////绘制结果////////////////////////////////////////
void Draw_Result(int result)
{
	char str_win[] = "YOU SURVIVE!";
	char str_fault[] = "YOU DIE...";

	settextstyle(100, 0,"Algerian");
	settextcolor(BLACK);

	if (result == WIN)outtextxy(Window_W / 2 - textwidth(str_win) / 2, 200, str_win);
	if (result == FAULT) outtextxy(Window_W / 2 - textwidth(str_fault) / 2, 200, str_fault);
}


void Display_core(int core)
{
	char Core[50];
	sprintf_s(Core, "core:%d", core);

	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	settextstyle(35, 0, "微软雅黑");
	settextcolor(BLACK);

	outtextxy(Window_W / 2 - textwidth(Core) / 2, 300 + BUTTON_H / 2 - textheight(Core) / 2, Core);
}

//绘制游戏结束画面
int Draw_EndGame(int result,int difficult_set,bool oxygen_set,bool tracks_set,int flashlight_set,int blood)
{
	ExMessage msg;
	setbkcolor(RGB(66, 108, 255));
	cleardevice();

	//计算分数
	int oxygen_core, tracks_core, core;

	if (oxygen_set) oxygen_core = 0;
	else oxygen_core = 1;

	if (tracks_set) tracks_core = 1;
	else tracks_core = 0;

	core = blood* oxygen_core + 50 * (difficult_set + 1) * (3 - flashlight_set) + 100 * oxygen_core + 50 * tracks_core;

	if (result == WIN)
	{
		Storage_win(wincount_read() + 1); //更新胜利次数
	}
	Storage_level(core + level_read());	  //更新等级

	while (true)
	{
		getmessage(&msg,EX_MOUSE);

		BeginBatchDraw();

		Draw_Result(result);

		AgainNew_Button(msg.x,msg.y);
		BackMenu_Button(msg.x, msg.y);
		BreakGame_Button(msg.x, msg.y);

		Display_core(core);

		EndBatchDraw();

		if (msg.message == WM_LBUTTONDOWN)
		{
			if (Is_AgainNew_Button(msg.x, msg.y)) return Choose_AgainNew;
			if (Is_BackMenu_Button(msg.x, msg.y)) return Choose_BackMenu;
			if (Is_BreakGame_Button(msg.x, msg.y)) return Choose_BreakGame;
		}
		msg.message = 0;
	}
}
