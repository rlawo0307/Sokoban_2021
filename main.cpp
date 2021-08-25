#pragma warning(disable:4996)

#include<stdio.h>

#include "command.h"
#include "var.h"

int main()
{
	PLAYER player;
	MAP* map = (MAP*)calloc(sizeof(MAP), 1);
	char str[50];
	int line = 0;
	char key = ' ';
	bool check;

	//Map Load 
	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return;
	}
	check = Load_Map(fp, map);
	if (!check)
	{
		printf("Check Your Map!\n");
		return;
	}
	fclose(fp);

	//Show Start Screen
	FILE* fp = fopen("./res/start_screen.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return;
	}
	Cursor_Move(POS_X, POS_Y);
	while (1)
	{
		fgets(str, sizeof(str), fp);
		if (!strcmp(str, "end"))
			break;
		Cursor_Move(POS_X, POS_Y + line);
		printf("%s", str);
		line++;
	}
	fclose(fp);

	//Select menu
	Cursor_Move(POS_X + 50, POS_Y + 6);
	while (key != 'f' && key != 'n' && key != 'h' && key != 't')
	{
		key = getch();
		switch (key)
		{
		case 'n': New_Game(&player, map, 1); break;
		case 'f': Load(&player, map, 0); break;
		case 'h': Display_Help(); Show_Start_Screen(); break;
		case 't': break;
		}
	}
	return 0;
}