#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>
//#include <windows.h>
//#include <conio.h>

#include "control.h"
#include "game.h"
#include "command.h"
#include "var.h"

int main()
{
	char user[10];
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int keep_check[MAP_MAX_ROW][MAP_MAX_COL];
	char key;
	int stage = 1, line, box, keep, cur_x, cur_y;

	Start_Screen(user);
	system("cls");

	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return 0;
	}

	while (stage)
	{
		line = box = keep = cur_x = cur_y = 0;

		for (int i = 0; i < MAP_MAX_ROW; i++)
		{
			memset(map[i], 0, sizeof(char) * MAP_MAX_COL);
			memset(keep_check[i], 0, sizeof(char) * MAP_MAX_COL);
		}

		Load_Map(map, fp, &line);
		Check_Box_Keep(map, keep_check, line, &box, &keep, &cur_x, &cur_y, stage);

		while (keep != 0)
		{
			key = getch();
			switch (key)
			{
			case 'u': break;
			case 'r': break;
			case 'n': break;
			case 'e': return 0;
			case 'p': break;
			case 'f': break;
			case 'h': Display_Help(map, stage); break;
			case 't': break;
			case 'a': 
			case 'd': 
			case 'w': 
			case 's': Player_Move(map, keep_check, key, &cur_x, &cur_y, line, stage, &keep); break;
			}
		}
		stage++;

		if (fgetc(fp) == EOF)
			break;
	}
	fclose(fp);
	printf("\nSokoban Clear~!\n");
	return 0;
}