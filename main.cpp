#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>
#include <conio.h>

#include "control.h"
#include "game.h"
#include "command.h"
#include "var.h"

typedef struct player
{
	char ID[30];
	int play_time;
}PLAYER;

typedef struct initial_data
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int map_line;
	int box, keep;
	int player_x, player_y;
	int stage;
}DATA1;

typedef struct cur_data
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int map_line;
	int box, keep;
	int player_x, player_y;
	int stage;
}DATA2;

//구조체 사용하는 형태로 바꾸기
int main()
{
	int keep_check[MAP_MAX_ROW][MAP_MAX_COL];
	char key;
	PLAYER player;
	DATA1 init_data;
	DATA2 cur_data;

	Start_Screen(user);

	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return 0;
	}

	while (stage)
	{
		line = box = keep = player_x = player_y = 0;

		for (int i = 0; i < MAP_MAX_ROW; i++)
		{
			memset(initial_map[i], 0, sizeof(char) * MAP_MAX_COL);
			memset(cur_map[i], 0, sizeof(char) * MAP_MAX_COL);
			memset(keep_check[i], 0, sizeof(char) * MAP_MAX_COL);
		}

		Load_Map(initial_map, fp, &line);
		Check_Box_Keep(initial_map, cur_map, keep_check, line, &box, &keep, &player_x, &player_y, stage);

		while (keep != 0)
		{
			key = getch();
			switch (key)
			{
			case 'u': break;
			case 'r': Restart_Cur_Map(initial_map, cur_map, stage, &keep, &player_x, &player_y); break;
			case 'n': break;
			case 'e': return 0;
			case 'p': break;
			case 'f': break;
			case 'h': Display_Help(cur_map, stage); break;
			case 't': break;
			case 'a': 
			case 'd': 
			case 'w': 
			case 's': Player_Move(cur_map, keep_check, key, &player_x, &player_y, line, stage, &keep); break;
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