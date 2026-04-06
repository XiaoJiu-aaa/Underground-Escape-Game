#include"SetingsInterface.h"

#include"Draw_Buttons.h"

#include"Seting_Buttons.h"

//设置--难度调整--轨迹开关--氧气//
int Draw_SetingsInterface()
{
	ExMessage msg;
	
	cleardevice();

	while (true)
	{
		getmessage(&msg, EX_MOUSE);

		BeginBatchDraw();//双缓冲区

		Button_Back(msg.x, msg.y);//返回按钮

		Difficulty_Switch(msg);//难度设置处理
		Oxygen_Switch(msg);//氧气开关
		Tracks_Switch(msg);//足迹开关
		Message_Switch(msg);//信息选择
		Flashlight_Switch(msg);//手电筒设置

		EndBatchDraw();//双缓冲区

		if (msg.message == WM_LBUTTONDOWN && Is_B_Back(msg.x, msg.y))
		{
			return BACKMENU;
		}
		msg.message = 0;
	}
}

