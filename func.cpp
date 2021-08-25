#include "func.h"
#include "command.h"

bool Load_Map(FILE* fp, MAP* map)
{
	MAP* last = map;
	MAP* tmp = NULL;
	char str[MAP_MAX_COL];
	int line = 0, stage = 1;
	

	while (1)
	{
		fgets(str, sizeof(str), fp);
		if (!strcmp(str, "map"))
		{
			tmp = (MAP*)calloc(sizeof(MAP), 1);
			last->next = tmp;
			last->stage = stage++;
			last = last->next;
		}
		else if (!strcmp(str, "end"))
		{
			last->next = tmp;
			last->stage = stage++;
			last = last->next;
			break;
		}
		else
		{
			for (int i = 0; i < strlen(str); i++)
			{
				tmp->map[line][i] = str[i];
				if (str[i] == '$')
					(tmp->box)++;
				else if (str[i] == 'O')
					(tmp->keep)++;
				else if (str[i] == '@')
				{
					tmp->player_x = i;
					tmp->player_y = line;
				}
			}
			(tmp->map_line++);
		}
		line++;
	}

	if (last->box != last->keep)
		return false;
	return true;
}

void Init_Data(MAP* init_map, MAP* cur_map)
{
	for (int i = 0; i < MAP_MAX_ROW; i++)
		for (int j = 0; j < MAP_MAX_ROW; j++)
			cur_map->map[i][j] = init_map->map[i][j];
	cur_map->box = init_map->box;
	cur_map->keep = init_map->keep = 0;
	cur_map->player_x = init_map->player_x;
	cur_map->player_y = init_map->player_y;
	cur_map->stage = init_map->stage;
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



void Print_Map(DATA2* cur_data)
{
	system("cls");
	Cursor_Move(POS_X, POS_Y);
	printf("< STAGE %d >\n\n", cur_data->stage);
	for (int i = cur_data->stage - 1 ? 0 : 1; i < cur_data->map_line; i++)
	{
		Cursor_Move(Get_Cursor(1) + POS_X, Get_Cursor(0));
		printf("%s", cur_data->map[i]);
	}
}


bool Ready(FILE* map_fp, PLAYER* player, DATA1* init_data, DATA2* cur_data, char* path, int op)
{
	bool check;

	Load_Map(map_fp, init_data);
	Init(init_data, cur_data);
	check = Check_Box_Keep(init_data, cur_data, path, op);
	return check;
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

