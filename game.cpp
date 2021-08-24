#include "game.h"

void Start_Screen(char* user)
{
	char str[50];
	int line = 0;

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
	Cursor_Move(POS_X + 16, POS_Y + 3);
	scanf("%s", user);
	fclose(fp);
	system("cls");
}

void Print_Map(char(*map)[MAP_MAX_COL], int stage)
{
	Cursor_Move(POS_X, POS_Y);
	printf("< STAGE %d >\n\n", stage);
	for (int i = stage - 1 ? 0 : 1; i < MAP_MAX_ROW; i++)
	{
		Cursor_Move(Get_Cursor(1) + POS_X, Get_Cursor(0));
		printf("%s", map[i]);
	}
}

void Load_Map(char(*map)[MAP_MAX_COL], FILE* fp, int* line)
{
	while (1)
	{
		fgets(map[*line], sizeof(map[*line]), fp);
		if ((*line != 0 && !strncmp(map[*line], "map", 3)) || !strncmp(map[*line], "end", 3))
		{
			memset(map[*line], 0, sizeof(MAP_MAX_COL));
			break;
		}
		else
			(*line)++;
	}
}

void Check_Box_Keep(char(*initial_map)[MAP_MAX_COL], char(*cur_map)[MAP_MAX_COL], int(*keep_check)[MAP_MAX_COL], int line, int* box, int* keep, int* player_x, int* player_y, int stage)
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < strlen(initial_map[i]); j++)
		{
			if (initial_map[i][j] == '$')
				(*box)++;
			else if (initial_map[i][j] == 'O')
			{
				keep_check[i][j] = 1;
				(*keep)++;
			}
			else if (initial_map[i][j] == '@')
			{
				*player_x = j;
				*player_y = i;
			}
			cur_map[i][j] = initial_map[i][j];
		}

	if (*box == *keep)
		Print_Map(cur_map, stage);
	else
		printf("Check Your Map!\n");
}

void Player_Move(char(*map)[MAP_MAX_COL], int(*keep_check)[MAP_MAX_COL], char key, int* player_x, int* player_y, int line, int stage, int* keep)
{
	char check;
	int next_x = *player_x, next_y = *player_y;
	int check_x = *player_x, check_y = *player_y;

	switch (key)
	{
	case 'a': next_x--; check_x -= 2; break;
	case 'd': next_x++; check_x += 2; break;
	case 'w': next_y--; check_y -= 2; break;
	case 's': next_y++; check_y += 2; break;
	}

	if (map[next_y][next_x] == ' ')
	{
		map[next_y][next_x] = '@';
		if (keep_check[*player_y][*player_x] == 1)
			map[*player_y][*player_x] = 'O';
		else
			map[*player_y][*player_x] = ' ';
	}
	else if (map[next_y][next_x] == '$')
	{
		check = map[check_y][check_x];
		if (check == ' ')
		{
			map[*player_y][*player_x] = ' ';
			map[next_y][next_x] = '@';
			map[check_y][check_x] = '$';
		}
		else if (check == 'O')
		{
			map[next_y][next_x] = '@';
			map[check_y][check_x] = '$';
			if (keep_check[*player_y][*player_x] == 1)
				map[*player_y][*player_x] = 'O';
			else
				map[*player_y][*player_x] = ' ';
		}
		else
			return;
	}
	else if (map[next_y][next_x] == 'O')
	{
		map[next_y][next_x] = '@';
		if (keep_check[*player_y][*player_x] == 1)
			map[*player_y][*player_x] = 'O';
		else
			map[*player_y][*player_x] = ' ';
	}
	else
		return;
	*player_x = next_x;
	*player_y = next_y;

	system("cls");
	Print_Map(map, stage);
}
