#pragma once


//////////////////////////文件-初始化-读取-写入////////////////////////////////////



bool File_exists(const char* filename);		//判断文件是否存在

void Initialize();							//初始化文件

void Storage_level(const int level);		//储存等级
void Storage_win(const int win_count);		//储存通关次数
void Storage_Difficult(const int difficult);//储存难度设置
void Storage_Oxygen(const bool tmp);		//储存氧气设置
void Storage_Tracks(const bool tmp);		//储存足迹设置
void Storage_Message(const int tmp);		//储存信息设置
void Storage_Flashlight(const int tmp);		//储存手电筒设置


int level_read();							//读取等级
int wincount_read();						//读取通关次数
int Storage_Difficult_read();				//读取玩家难度设置
bool Storage_Oxygen_read();					//读取氧气设置
bool Storage_Tracks_read();					//读取足迹设置
int Storage_Message_read();					//读取信息设置
int Storage_Flashlight_read();				//读取手电筒设置



