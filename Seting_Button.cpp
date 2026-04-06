
#include<math.h>

#include"Seting_Buttons.h"
#include"Data_Storage.h"


#define option_button_width 120
#define option_button_height 50

#define button_width 300
#define button_height 50

//难度设置
void Difficulty_Switch(ExMessage msg)
{
	char str1[] = "Difficulty";

	char str2[] = "Easy and effortless";
	char str3[] = "A bit difficult";
	char str4[] = "Full of difficulties";
	
	char* str_all[] = {str2,str3,str4};
	settextcolor(RGB(231,209,255));
	settextstyle(25, 0, "Showcard Gothic");
	setfillcolor(BROWN);
	
	setlinecolor(RGB(231, 209, 255));
	fillroundrect(250,300,250+ option_button_width,300+ option_button_height,25,25);
	outtextxy(250+ option_button_width /2-textwidth(str1)/2,300+ option_button_height /2-textheight(str1)/2 ,str1);//左侧按钮绘制

	if (msg.x > 400 && msg.x < 400 + button_width && msg.y < 300 + button_height && msg.y>300) setfillcolor(YELLOW);
	fillroundrect(400, 300, 400 + button_width, 300 + button_height, 25, 25);//右侧按钮绘制

	int count=Storage_Difficult_read();
	outtextxy(400 + button_width / 2 - textwidth(str_all[count]) / 2, 300 + option_button_height / 2 - textheight(str_all[count]) / 2, str_all[count]);

	if (msg.message == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 400 + button_width && msg.y < 300 + button_height && msg.y>300)
	{
		Storage_Difficult((count + 1)%3);
	}
}

//氧气设置
void Oxygen_Switch(ExMessage msg)
{
	char str[] = "Oxygen";

	char str1[] = "ON";
	char str2[] = "OFF";

	settextcolor(RGB(231, 209, 255));
	settextstyle(25, 0, "Showcard Gothic");
	setfillcolor(BROWN);

	setlinecolor(RGB(231, 209, 255));
	fillroundrect(250, 400, 250 + option_button_width, 400 + option_button_height, 25, 25);
	outtextxy(250 + option_button_width / 2 - textwidth(str) / 2, 400 + option_button_height / 2 - textheight(str) / 2, str);//左侧按钮绘制

	if (msg.x > 400 && msg.x < 400 + button_width && msg.y < 400 + button_height && msg.y>400) setfillcolor(YELLOW);
	fillroundrect(400, 400, 400 + button_width, 400 + button_height, 25, 25);//右侧按钮绘制

	bool tmp = Storage_Oxygen_read();
	switch (tmp)
	{
		case false:
			outtextxy(400 + button_width / 2 - textwidth(str1) / 2, 400 + option_button_height / 2 - textheight(str1) / 2, str1);
			break;
		case true:
			outtextxy(400 + button_width / 2 - textwidth(str2) / 2, 400 + option_button_height / 2 - textheight(str2) / 2, str2);
			break;
	}

	if (msg.message == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 400 + button_width && msg.y < 400 + button_height && msg.y>400)
	{
		Storage_Oxygen(!tmp);
	}
}

//足迹设置
void Tracks_Switch(ExMessage msg)
{
	char str[] = "Tracks";

	char str1[] = "ON";
	char str2[] = "OFF";

	settextcolor(RGB(231, 209, 255));
	settextstyle(25, 0, "Showcard Gothic");
	setfillcolor(BROWN);

	setlinecolor(RGB(231, 209, 255));
	fillroundrect(250, 500, 250 + option_button_width, 500 + option_button_height, 25, 25);
	outtextxy(250 + option_button_width / 2 - textwidth(str) / 2, 500 + option_button_height / 2 - textheight(str) / 2, str);//左侧按钮绘制

	if (msg.x > 400 && msg.x < 400 + button_width && msg.y < 500 + button_height && msg.y>500) setfillcolor(YELLOW);
	fillroundrect(400, 500, 400 + button_width, 500 + button_height, 25, 25);//右侧按钮绘制

	bool tmp = Storage_Tracks_read();
	switch (tmp)
	{
	case false:
		outtextxy(400 + button_width / 2 - textwidth(str1) / 2, 500 + option_button_height / 2 - textheight(str1) / 2, str1);
		break;
	case true:
		outtextxy(400 + button_width / 2 - textwidth(str2) / 2, 500 + option_button_height / 2 - textheight(str2) / 2, str2);
		break;
	}

	if (msg.message == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 400 + button_width && msg.y < 500 + button_height && msg.y>500)
	{
		Storage_Tracks(!tmp);
	}
}

//信息设置
void Message_Switch(ExMessage msg)
{
	char str[] = "Message";

	char str1[] = "NO";
	char str2[] = "Skip!";//跳过信息显示
	char* str_all[] = { str1,str2 };

	settextcolor(RGB(231, 209, 255));
	settextstyle(25, 0, "Showcard Gothic");
	setfillcolor(BROWN);

	setlinecolor(RGB(231, 209, 255));
	fillroundrect(250, 600, 250 + option_button_width, 600 + option_button_height, 25, 25);
	outtextxy(250 + option_button_width / 2 - textwidth(str) / 2, 600 + option_button_height / 2 - textheight(str) / 2, str);//左侧按钮绘制

	if (msg.x > 400 && msg.x < 400 + button_width && msg.y < 600 + button_height && msg.y>600) setfillcolor(YELLOW);
	fillroundrect(400, 600, 400 + button_width, 600 + button_height, 25, 25);//右侧按钮绘制

	int message_set = Storage_Message_read();//读取设置
	outtextxy(400 + button_width / 2 - textwidth(str_all[message_set]) / 2, 600 + option_button_height / 2 - textheight(str_all[message_set]) / 2, str_all[message_set]);

	if (msg.message == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 400 + button_width && msg.y < 600 + button_height && msg.y>600)
	{
		Storage_Message(abs(message_set-1));
	}
}

//手电筒设置
void Flashlight_Switch(ExMessage msg)
{
	char str[] = "Flashlight";

	char str1[] = "Low battery...";
	char str2[] = "Normal flashlight";
	char str3[] = "This is a sun!";
	char* str_all[] = { str1,str2,str3 };

	settextcolor(RGB(231, 209, 255));
	settextstyle(25, 0, "Showcard Gothic");
	setfillcolor(BROWN);

	setlinecolor(RGB(231, 209, 255));
	fillroundrect(250, 700, 250 + option_button_width, 700 + option_button_height, 25, 25);
	outtextxy(250 + option_button_width / 2 - textwidth(str) / 2, 700 + option_button_height / 2 - textheight(str) / 2, str);//左侧按钮绘制

	if (msg.x > 400 && msg.x < 400 + button_width && msg.y < 700 + button_height && msg.y>700) setfillcolor(YELLOW);
	fillroundrect(400, 700, 400 + button_width, 700 + button_height, 25, 25);//右侧按钮绘制

	int tmp = Storage_Flashlight_read();
	outtextxy(400 + button_width / 2 - textwidth(str_all[tmp]) / 2, 700 + option_button_height / 2 - textheight(str_all[tmp]) / 2, str_all[tmp]);

	if (msg.message == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 400 + button_width && msg.y < 700 + button_height && msg.y>700)
	{
		Storage_Flashlight((tmp + 1)%3);
	}


}