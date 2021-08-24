#include "command.h"

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

void Restart_Cur_Map(char(*initial_map)[MAP_MAX_COL], char(*cur_map)[MAP_MAX_COL], int stage, int* keep, int* player_x, int* player_y) //undo, time reset
{
	system("cls");
	for (int i = 0; i < MAP_MAX_ROW; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			cur_map[i][j] = initial_map[i][j];

	Print_Map(initial_map, stage);
}