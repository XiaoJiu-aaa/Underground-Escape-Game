

#include"Draw_Menu.h"


#include"Draw_Buttons.h"
#include"Data_Storage.h"
#include<string.h>
#include<stdio.h>

#define Button_Data_Width	100
#define Button_Data_Height	50

#define START		1
#define SETTINGS	2
#define BREAKGAME	3

#define Window_w	1024
#define Window_h	1024

//创建窗口,设置背景
void Creat_Windows()
{
	initgraph(Window_w, Window_h);
	setbkcolor(RGB(66,108,255));
	cleardevice();
}


//绘制主界面与消息处理
int Draw_MainInerface()
{
	ExMessage msg; 
	setbkcolor(RGB(66, 108, 255));
	
	while (true)
	{
		getmessage(&msg,EX_MOUSE);

		BeginBatchDraw();//双缓冲区
		cleardevice();

		Draw_Title();//绘制标题

		Display_level();//显示等级
		Display_win_count();//显示通关次数


		//绘制按钮
		Button_StartGame(msg.x, msg.y);
		Button_SetMiner(msg.x, msg.y);
		Button_BreakGame(msg.x, msg.y);
		

		EndBatchDraw();//双缓冲区

		if (msg.message == WM_LBUTTONDOWN)
		{
			if (Is_B_StartGame(msg.x,msg.y)) return START;
			if (Is_B_SetMiner(msg.x,msg.y)) return SETTINGS;
			if (Is_B_BreakGame(msg.x,msg.y)) return BREAKGAME;
		}
		msg.message = 0;
	}
}


//绘制标题
void Draw_Title()
{
	char str_title[] = "Underground Escape";
	setbkmode(TRANSPARENT); 
	settextcolor(BLACK);
	settextstyle(100,0,"Bauhaus 93");
	settextcolor(WHITE);

	outtextxy(Window_w/2-textwidth(str_title)/2,200,str_title);
}


//显示游戏数据
void Display_level()
{
	char str_level[50];
	sprintf_s(str_level, "Level:%d", level_read()/1000);

	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(25,0, "微软雅黑");
	setfillcolor(RGB(255,247,50));

	fillroundrect(100,450,100+Button_Data_Width,450+Button_Data_Height, 25, 25);
	
	outtextxy(100+ Button_Data_Width/2-textwidth(str_level)/2, 450 + Button_Data_Height / 2-textheight(str_level) / 2, str_level);
}

void Display_win_count()
{
	char str_win[50];
	sprintf_s(str_win, "Win:%d", wincount_read());

	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(25, 0, "微软雅黑");
	setfillcolor(RGB(255, 247, 50));

	fillroundrect(100, 550, 100 + Button_Data_Width, 550 + Button_Data_Height, 25, 25);

	outtextxy(100 + Button_Data_Width / 2 - textwidth(str_win) / 2, 550 + Button_Data_Height / 2 - textheight(str_win) / 2, str_win);

}
