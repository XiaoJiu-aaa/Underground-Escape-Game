#include"Draw_Buttons.h"

#include<stdbool.h>
#define Button_w 200
#define Button_h 50
#define Window_w 1024

///////////////////////////////////////////////////////////////////////////////////
                           //绘制主界面按钮//
						  
						 
//开始游戏按钮
void Button_StartGame(int msg_x,int msg_y)
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(140, 140, 140));
	if(Is_B_StartGame(msg_x,msg_y)) setfillcolor(YELLOW);

	char str_start[] = "Start";
	settextstyle(40, 0, "Ravie");
	settextcolor(BROWN);

	fillroundrect(Window_w / 2 - Button_w / 2, 400, Window_w / 2 + Button_w / 2, 400 + Button_h, 25, 25);

	outtextxy(Window_w/2-textwidth(str_start)/2,400+Button_h/2-textheight(str_start)/2, str_start);
}

//设置角色属性按钮
void Button_SetMiner(int msg_x, int msg_y)
{
	setlinecolor(BLACK);
	setfillcolor(RGB(140, 140, 140));
	if (Is_B_SetMiner(msg_x, msg_y)) setfillcolor(YELLOW);
	
	char str_set[] = "Settings";
	settextstyle(40, 0, "Ravie");
	settextcolor(BROWN);
	 
	fillroundrect(Window_w / 2 - Button_w / 2, 500, Window_w / 2 + Button_w / 2, 500 + Button_h, 25, 25);

	outtextxy(Window_w / 2 - textwidth(str_set) / 2, 500 + Button_h / 2 - textheight(str_set) / 2, str_set);
}

//退出游戏按钮
void Button_BreakGame(int msg_x, int msg_y)
{
	setlinecolor(BLACK);
	setfillcolor(RGB(140, 140, 140));
	if (Is_B_BreakGame(msg_x, msg_y)) setfillcolor(YELLOW);

	char str_break[] = "Break";
	settextstyle(40, 0, "Ravie");
	settextcolor(BROWN);

	fillroundrect(Window_w / 2 - Button_w / 2, 600, Window_w / 2 + Button_w / 2, 600 + Button_h, 25, 25);

	outtextxy(Window_w / 2 - textwidth(str_break) / 2, 600 + Button_h / 2 - textheight(str_break) / 2, str_break);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
                                     //设置界面//
	


//返回按钮
void Button_Back(int msg_x, int msg_y)
{
	setlinecolor(BLACK);
	setfillcolor(RGB(140, 140, 140));
	if (Is_B_Back(msg_x, msg_y)) setfillcolor(YELLOW);

	char str_back[] = "Back";
	settextstyle(50,0, "Ravie");
	settextcolor(BROWN);

	fillroundrect(70,50,70+140,50+50,25,25);

	outtextxy(140-textwidth(str_back)/2,75- textheight(str_back) / 2, str_back);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                          //判断鼠标是否在按钮上//



bool Is_B_StartGame(int msg_x, int msg_y)
{
	if (msg_x<Window_w / 2 + Button_w / 2 && msg_x>Window_w / 2 - Button_w / 2 && msg_y < 400 + Button_h && msg_y>400) return true;
	return false;
}


bool Is_B_SetMiner(int msg_x, int msg_y)
{
	if (msg_x<Window_w / 2 + Button_w / 2 && msg_x>Window_w / 2 - Button_w / 2 && msg_y < 500 + Button_h && msg_y>500) return true;
	return false;
}


bool Is_B_BreakGame(int msg_x, int msg_y)
{
	if (msg_x<Window_w / 2 + Button_w / 2 && msg_x>Window_w / 2 - Button_w / 2 && msg_y < 600 + Button_h && msg_y>600) return true;
	return false;
}


bool Is_B_Back(int msg_x, int msg_y)
{
	if (msg_x<210&&msg_x>70&&msg_y<100&&msg_y>50) return true;
	return false;
}