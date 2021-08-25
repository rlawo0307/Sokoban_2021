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

void Deep_Copy(DATA1* init_data, DATA2* cur_data)
{
	for (int i = 0; i < MAP_MAX_ROW; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			cur_data->map[i][j] = init_data->map[i][j];

	cur_data->map_line = init_data->map_line;
	cur_data->box = init_data->box;
	cur_data->keep = init_data->keep;
	cur_data->player_x = init_data->player_x;
	cur_data->player_y = init_data->player_y;
}

void Init(PLAYER* user, DATA1* init_data, DATA2* cur_data)
{
	for (int i = 0; i < MAP_MAX_ROW; i++)
		memset(init_data->map[i], 0, sizeof(char) * MAP_MAX_COL);
	init_data->map_line = 0;
	init_data->box = init_data->keep = 0;
	init_data->player_x = init_data->player_y = 0;

	Deep_Copy(init_data, cur_data);
	cur_data->stage = 0;
}

void Load_Map(FILE* fp, DATA1* init_data)
{
	int line = 0;
	while (1)
	{
		fgets(init_data->map[line], sizeof(init_data->map[line]), fp);
		if ((line != 0 && !strncmp(init_data->map[line], "map", 3)) || !strncmp(init_data->map[line], "end", 3))
		{
			memset(init_data->map[line], 0, MAP_MAX_COL);
			break;
		}
		else
			(line)++;
	}
	init_data->map_line = line;
}

void Print_Map(DATA2* cur_data)
{
	Cursor_Move(POS_X, POS_Y);
	printf("< STAGE %d >\n\n", cur_data->stage);
	for (int i = cur_data->stage - 1 ? 0 : 1; i < cur_data->map_line; i++)
	{
		Cursor_Move(Get_Cursor(1) + POS_X, Get_Cursor(0));
		printf("%s", cur_data->map[i]);
	}
}

void Check_Box_Keep(DATA1* init_data, DATA2* cur_data)
{
	for (int i = 0; i < init_data->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			if (init_data->map[i][j] == '$')
				(init_data->box)++;
			else if (init_data->map[i][j] == 'O')
				(init_data->keep)++;
			else if (init_data->map[i][j] == '@')
			{
				init_data->player_x = j;
				init_data->player_y = i;
			}

	if (init_data->box == init_data->keep)
	{
		Deep_Copy(init_data, cur_data);
		(cur_data->stage)++;
		Print_Map(cur_data);
	}
	else
		printf("Check Your Map!\n");
}

void Player_Move(DATA1* init_data, DATA2* cur_data, char key)
{
	int cur_x, cur_y, next_x, next_y, check_x, check_y;

	next_x = check_x = cur_x = cur_data->player_x;
	next_y = check_y = cur_y = cur_data->player_y;

	switch (key)
	{
	case 'a': next_x--; check_x -= 2; break;
	case 'd': next_x++; check_x += 2; break;
	case 'w': next_y--; check_y -= 2; break;
	case 's': next_y++; check_y += 2; break;
	}

	char next_c = cur_data->map[next_y][next_x];
	char isbox = init_data->map[cur_y][cur_x];
	char check_c = cur_data->map[check_y][check_x];

	if (next_c == ' ')
	{
		cur_data->map[next_y][next_x] = '@';
		if (isbox == 'O')
			cur_data->map[cur_y][cur_x] = 'O';
		else
			cur_data->map[cur_y][cur_x] = ' ';
	}
	else if (next_c == '$')
	{
		if (check_c == ' ')
		{
			cur_data->map[cur_y][cur_x] = ' ';
			cur_data->map[next_y][next_x] = '@';
			cur_data->map[check_y][check_x] = '$';
		}
		else if (check_c == 'O')
		{
			cur_data->map[next_y][next_x] = '@';
			cur_data->map[check_y][check_x] = '$';
			if (isbox == 'O')
				cur_data->map[cur_y][cur_x] = 'O';
			else
				cur_data->map[cur_y][cur_x] = ' ';
		}
		else
			return;
	}
	else if (next_c == 'O')
	{
		cur_data->map[next_y][next_x] = '@';
		if (isbox == 'O')
			cur_data->map[cur_y][cur_x] = 'O';
		else
			cur_data->map[cur_y][cur_x] = ' ';
	}
	else
		return;

	cur_data->player_x = next_x;
	cur_data->player_y = next_y;

	system("cls");
	Print_Map(cur_data);
}

