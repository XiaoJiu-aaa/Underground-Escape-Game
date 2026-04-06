


#include"Draw_Menu.h"
#include"Data_Storage.h"
#include"Game_Body.h"

int main()
{
	Creat_Windows();	//创建窗口

	Initialize();		//文件初始化
	
	MainGame();			//游戏主体

	return 0;
}