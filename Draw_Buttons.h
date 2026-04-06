#pragma once


#include<easyx.h>



////////////////////////////////////////////////////////////////////////
                          //绘制按钮//


void Button_StartGame(int msg_x,int msg_y);     //开始游戏按钮
void Button_SetMiner(int msg_x,int msg_y);      //设置
void Button_BreakGame(int msg_x,int msg_y);     //退出按钮
void Button_Back(int msg_x, int msg_y);         //返回上一页



//////////////////////////////////////////////////////////////////////
                   //判定鼠标与按钮位置关系// 



bool Is_B_StartGame(int msg_x, int msg_y);
bool Is_B_SetMiner(int msg_x, int msg_y);
bool Is_B_BreakGame(int msg_x, int msg_y);
bool Is_B_Back(int msg_x,int msg_y);





