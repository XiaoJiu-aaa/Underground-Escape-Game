
#define _CRT_SECURE_NO_WARNINGS
#include"Data_Storage.h"

#include<stdio.h>


//判断文件是否存在 存在--真；不存在--否
bool File_exists(const char*filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	return true;
}

//初始化
void Initialize()
{
	if (File_exists("./level.txt")     && 
		File_exists("./win_count.txt") && 
		File_exists("./difficult.txt") &&
		File_exists("./oxygen.txt")    &&
		File_exists("./tracks.txt")    &&
		File_exists("./message.txt")   &&
		File_exists("./flashlight.txt"))
	{
		return;//跳过初始化
	}

	FILE* f1 = fopen("./level.txt", "w");
	FILE* f2 = fopen("./win_count.txt", "w");
	FILE* f3 = fopen("./difficult.txt", "w");
	FILE* f4 = fopen("./oxygen.txt", "w");
	FILE* f5 = fopen("./tracks.txt", "w");
	FILE* f6 = fopen("./message.txt", "w");
	FILE* f7 = fopen("./flashlight.txt", "w");

	if (f1) { fprintf(f1, "%d", 0);	fclose(f1); }
	else    { printf("初始化失败(level.txt)"); return; }
	
	if (f2) { fprintf(f2, "%d", 0); fclose(f2); }
	else    { printf("初始化失败(win_count.txt)"); return; }
	
	if (f3) { fprintf(f3, "%d", 0); fclose(f3); }
	else    { printf("初始化失败(difficult.txt)"); return; }

	if (f4) {fprintf(f4, "%d", 0);fclose(f4);}
	else    {printf("初始化失败(oxygen.txt)"); return;}
	
	if (f5) {fprintf(f5, "%d", 0);fclose(f5);}
	else    {printf("初始化失败(tracks.txt)");  return;}
		
	if (f6) {fprintf(f6, "%d", 0);fclose(f6);}
	else    {printf("初始化失败(message.txt)"); return;}
	
	if (f7) {fprintf(f7, "%d", 0);fclose(f7);}
	else    {printf("初始化失败（flashlight.txt）");return;}

	printf("初始化成功！");
}


///////////////////////////////存储函数///////////////////////////////////////////


//存储等级
void Storage_level(const int level)
{
	FILE* f = fopen("./level.txt", "w");
	if (f == NULL)
	{
		printf("打开level.txt失败！");
		return;
	}

	fprintf(f, "%d", level);
	fclose(f);
}

//存储通关次数
void Storage_win(const int win_count)
{
	FILE* f = fopen("./win_count.txt", "w");
	if (f == NULL)
	{
		printf("打开win_count.txt失败！");
		return;
	}

	fprintf(f, "%d", win_count);
	fclose(f);
}

//存储难度设置
void Storage_Difficult(const int difficult)
{
	FILE* f = fopen("./difficult.txt", "w");
	if (f == NULL)
	{
		printf("打开difficult.txt失败！");
		return;
	}

	fprintf(f, "%d", difficult);
	fclose(f);
}

//存储氧气设置
void Storage_Oxygen(const bool tmp)
{
	FILE* f = fopen("./oxygen.txt", "w");
	if (f == NULL)
	{
		printf("打开oxygen.txt失败！");
		return;
	}

	if (tmp) fprintf(f, "%d",1);
	if (!tmp) fprintf(f, "%d", 0);
	fclose(f);
}

//存储足迹设置
void Storage_Tracks(const bool tmp)
{
	FILE* f = fopen("./tracks.txt", "w");
	if (f == NULL)
	{
		printf("打开tracks.txt失败！");
		return;
	}

	if (tmp) fprintf(f, "%d", 1);
	if (!tmp) fprintf(f, "%d", 0);
	fclose(f);
}

//存储信息设置
void Storage_Message(const int tmp)
{
	FILE* f = fopen("./message.txt", "w");
	if (f == NULL)
	{
		printf("打开message.txt失败！");
		return;
	}

	fprintf(f, "%d", tmp);
	
	fclose(f);
}

//存储手电筒设置
void Storage_Flashlight(const int tmp)
{
	FILE* f = fopen("./flashlight.txt", "w");
	if (f == NULL)
	{
		printf("打开flashlight.txt失败！");
		return;
	}

	fprintf(f, "%d", tmp);
	fclose(f);
}



//////////////////////////////读取函数//////////////////////////////////////

//读取等级
int level_read()
{
	FILE* f = fopen("./level.txt", "r");
	if (f == NULL)
	{
		printf("打开level.txt失败！");
		return -1;
	}

	int level=0;
	fscanf(f, "%d", &level);
	fclose(f);

	return level;
}

//读取通关次数
int wincount_read()
{
	FILE* f = fopen("./win_count.txt", "r");
	if (f == NULL)
	{
		printf("打开win_count.txt失败！");
		return 0;
	}

	int win_count = 0;
	fscanf(f, "%d", &win_count);
	fclose(f);

	return win_count;
}

//读取难度设置
int Storage_Difficult_read()
{
	FILE* f = fopen("./difficult.txt", "r");
	if (f == NULL)
	{
		printf("打开difficult.txt失败！");
		return 0;
	}

	int difficult = 0;
	fscanf(f, "%d", &difficult);
	fclose(f);

	return difficult;
}

//读取氧气设置
bool Storage_Oxygen_read()
{
	FILE* f = fopen("./oxygen.txt", "r");
	if (f == NULL)
	{
		printf("打开oxygen.txt失败！");
		return 0;
	}

	int oxygen;
	fscanf(f, "%d", &oxygen);
	fclose(f);
	
	if (oxygen == 0) return false;
	return true;
}

//读取足迹设置
bool Storage_Tracks_read()
{
	FILE* f = fopen("./tracks.txt", "r");
	if (f == NULL)
	{
		printf("打开tracks.txt失败！");
		return 0;
	}

	int tracks;
	fscanf(f, "%d", &tracks);
	fclose(f);

	if (tracks == 0) return false;
	return true;
}

//读取信息设置
int Storage_Message_read()
{
	FILE* f = fopen("./message.txt", "r");
	if (f == NULL)
	{
		printf("打开message.txt失败！");
		return 0;
	}

	int message;
	fscanf(f, "%d", &message);
	fclose(f);

	return message;
}

//读取手电筒设置
int Storage_Flashlight_read()
{
	FILE* f = fopen("./flashlight.txt", "r");
	if (f == NULL)
	{
		printf("打开flashlight.txt失败！");
		return 0;
	}

	int flash;
	fscanf(f, "%d", &flash);
	fclose(f);

	return flash;
}

