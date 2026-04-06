

#include"Game_Pause.h"



//暂停界面绘制
int Draw_Pause()
{
	ExMessage msg;

	RECT r = { SCREENWIDTH / 2 - 200,SCREENHEIGHT / 2 - 150,SCREENWIDTH / 2 + 200,SCREENHEIGHT / 2 + 150 };
	RECT r1 = { SCREENWIDTH / 2 - 200 + 20,SCREENHEIGHT / 2 + 70,SCREENWIDTH / 2 - 200 + 150 + 20,SCREENHEIGHT / 2 + 70 + 40 };
	RECT r2 = { SCREENWIDTH - r1.right ,r1.top ,SCREENWIDTH - r1.left,r1.bottom };
	RECT r3 = { r.left ,r.top + 110,r.right ,r.bottom + 110 + 50 };

	char str1[] = "If you end the game now,you will not receive anything...";
	char str2[] = "Continue your escape!";

	setfillcolor(RGB(210, 184, 255));
	setlinecolor(RGB(221, 204, 255));

	settextcolor(BLACK);

	//绘制图案
	while (true)
	{
		getmessage(&msg,EX_MOUSE);

		settextstyle(70, 0, "Haettenschweiler");
		setfillcolor(RGB(210, 184, 255));

		BeginBatchDraw();

		fillroundrect(r.left, r.top, r.right, r.bottom, 60, 60);
		drawtext("Game   Pause", &r, DT_CENTER);//标题

		//两个按钮
		Draw_End(msg, r1);
		Draw_Continue(msg, r2);

		//绘制中间文字
		if (msg.x > r1.left && msg.x < r1.right && msg.y<r1.bottom && msg.y>r1.top)
			drawtext(str1, &r3, DT_CENTER | DT_WORDBREAK);
		if (msg.x > r2.left && msg.x < r2.right && msg.y<r2.bottom && msg.y>r2.top)
			drawtext(str2, &r3, DT_WORDBREAK | DT_CENTER);
		EndBatchDraw();

		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x > r1.left && msg.x < r1.right && msg.y<r1.bottom && msg.y>r1.top)return GAMEEND;
			if (msg.x > r2.left && msg.x < r2.right && msg.y<r2.bottom && msg.y>r2.top )return GAMECONTINUE;

		}
	}
}

//终止游戏按钮
void Draw_End(ExMessage msg, RECT r1)
{
	setfillcolor(RGB(230, 213, 255));
	settextstyle(24, 0, "宋体");

	if (msg.x > r1.left && msg.x < r1.right && msg.y<r1.bottom && msg.y>r1.top) setfillcolor(RGB(94, 255, 93));
	fillroundrect(r1.left, r1.top, r1.right, r1.bottom, 25, 25);//左侧终止按钮
	drawtext("End", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//继续游戏按钮
void Draw_Continue(ExMessage msg, RECT r2)
{
	setfillcolor(RGB(230, 213, 255));

	if (msg.x > r2.left && msg.x < r2.right && msg.y<r2.bottom && msg.y>r2.top) setfillcolor(RGB(94, 255, 93));
	fillroundrect(r2.left, r2.top, r2.right, r2.bottom, 25, 25);//右侧继续按钮
	drawtext("Continue", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
