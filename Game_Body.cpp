#include"Game_Body.h"


#include"GameReact.h"
#include"Data_Storage.h"
#include"EndGame.h"

#include"Draw_Menu.h"
#include"SetingsInterface.h"
#include<time.h>

#define WINDOW_W 1024
#define WINDOW_H 1024

#define BUTTON_W 10

//游戏显示与消息处理
void MainGame()
{
	srand(time(NULL));

	while (true)
	{
		//游戏设置读取
		int defficult_set = Storage_Difficult_read();
		bool oxygen_set = Storage_Oxygen_read();
		bool tracks_set = Storage_Tracks_read();
		int message_set = Storage_Message_read();
		int flashlight_set = Storage_Flashlight_read();

		int MainChoose = Draw_MainInerface();//主界面的选择

		int Choose = 0;						 //游戏结束后的选择

		//开始游戏
		if (MainChoose == START)
		{
			Game_Background(message_set);	//游戏背景展示
			Display_tips(message_set);		//显示提示

			AGIN:
			Choose = Game_Body(defficult_set,oxygen_set, tracks_set, flashlight_set);
			if (Choose == Choose_BreakGame) return ;
			if (Choose == Choose_AgainNew) goto AGIN;
			if (Choose == Choose_BackMenu) continue;
		}
		//进入设置界面
		else if (MainChoose == SETTINGS)
		{
			int Set_Choose = Draw_SetingsInterface();
			if (Set_Choose == BACKMENU) continue;
		}
		//退出游戏
		else if (MainChoose == BREAKGAME)
		{
			return ;
		}
	}
}

//游戏背景信息展示
void Game_Background(int message_set) 
{
	if (message_set==1) return;

	RECT r = {100,WINDOW_H/2-100,WINDOW_W ,WINDOW_H / 2 + 100 };
	setbkcolor(BLACK);
	settextstyle(30, 0, "微软雅黑");
	settextcolor(WHITE);

	char str1[] = "You are a miner.";
	char str2[] = "But today,while you are working,this mine shaft was collapsed...";
	char str3[] = "Lukily,you have flashlight.";
	char str4[] = "Now you must use this flashlight and a few oxygen and some tools to survive... ";
	char* str[] = { str1,str2,str3,str4 };

	for (int i = 0; i < 4; i++)
	{
		cleardevice();
		drawtext(str[i], &r, DT_WORDBREAK);
		Sleep(3000);
	}
}

//显示提示
void Display_tips(int message_set)
{
	if (message_set == 1) return;

	ExMessage msg;
	while (peekmessage(&msg, EX_MOUSE, true)) 
	{
		// 不断取出消息，直到鼠标消息队列为空
	}

	cleardevice();
	settextcolor(WHITE);
	setlinecolor(WHITE);

	RECT r_title = { WINDOW_W / 2 - 50,150,WINDOW_W / 2 + 50,150 + 50 };
	RECT r_content = { WINDOW_W / 2 - 200,300,WINDOW_W / 2 + 200,300 + 350 };
	
	settextstyle(40, 0, "宋体");
	roundrect(r_title.left - BUTTON_W, r_title.top - BUTTON_W, r_title.right + BUTTON_W, r_title.bottom + BUTTON_W,25,25);
	drawtext("提示",&r_title,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	settextstyle(24, 0, "宋体");
	roundrect(r_content.left - BUTTON_W, r_content.top - BUTTON_W, r_content.right + BUTTON_W, r_content.bottom + BUTTON_W, 25, 25);
	drawtext("1.使用'W','A','S','D'来进行移动\n\n2.滑动鼠标来获得视野\n\n3.按ESC暂停游戏并退出\n\n4.每局分数会随着您的游戏设置而改变\n\n5.如果您要跳过以上内容，请前往设置界面\n\n\n点击任意位置开始游戏", &r_content, DT_WORDBREAK|DT_CENTER);

	while (true)
	{
		peekmessage(&msg, EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) return;
	}
}

