#pragma once

#define SCREENWIDTH 1024
#define SCREENHEIGHT 1024


#define GAMEEND 1
#define GAMECONTINUE 2

#include<easyx.h>

int Draw_Pause();								//绘制暂停界面

void Draw_End(ExMessage msg, RECT r1);			//暂停按钮
void Draw_Continue(ExMessage msg, RECT r2);		//继续按钮
