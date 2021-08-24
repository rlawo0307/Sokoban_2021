#pragma once

#include <stdio.h>
#include <windows.h>
#include "game.h"

void Display_Help(char(*map)[MAP_MAX_COL], int stage)
{
	char str[100];
	char key = ' ';

	FILE* fp = fopen("./res/help.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return;
	}

	system("cls");

	while (1)
	{
		fgets(str, sizeof(str), fp);
		if (!strcmp(str, "end"))
			break;
		printf("%s", str);
	}
	fclose(fp);

	while (key != 'q')
		key = getch();

	system("cls");
	Print_Map(map, stage);
}