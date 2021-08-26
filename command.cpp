#include "command.h"
#include "func.h"

/*================================================
start command
================================================*/
void Play(PLAYER* player, MAP* init_map, int op)
{
	MAP* map_p = init_map;
	MAP cur_map;
	MAP* tmp = (MAP*)calloc(1, sizeof(MAP));
	bool game = true;
	char key;
	int i = 0, stage = 1;

	system("cls");
	Input_ID(player);

	if (op == 0) // File_Load
	{
		while (!Load(player, &cur_map))
		{
			Cursor_Move(POS_X, POS_Y + 6);
			printf("* No Such Data (ID : %s)\n", player->ID);
			Input_ID(player);
		}
		stage = cur_map.stage;
	}

	while (i < stage)
	{
		map_p = map_p->next;
		i++;
	}
	
	while (1)
	{
		if (map_p == NULL)
		{
			printf("\nSokoban Clear~!\n");
			break;
		}
		else
		{
			if (op == NEW_GAME)
			{
				Init_Data(map_p, tmp);
				Init_Data(tmp, &cur_map);
			}
			else
				Init_Data(&cur_map, tmp);
			Print_Map(&cur_map);
			Cursor_Move(POS_X+27, POS_Y + 6);
			while (1)
			{
				key = getch();
				switch (key)
				{
				case 'u': break;
				case 'r': Restart_Cur_Map(tmp, &cur_map); break;
				case 'n': Restart_Game(player, init_map, &cur_map, &map_p, &stage); break;
				case 'e': Save(player, &cur_map); return;
				case 'p': Save(player, &cur_map); break;
				case 'a':
				case 'd':
				case 'w':
				case 's': Player_Move(map_p, &cur_map, key); break;
				}
				if (cur_map.keep == 0)
				{
					Cursor_Move(POS_X, POS_Y + cur_map.map_line + 3);
					printf("Stage Clear!\n");
					Sleep(1000);
					break;
				}
			}
		}
		stage++;
		map_p = map_p->next;
		op = NEW_GAME;
	}
}

bool Load(PLAYER* player, MAP* map)
{
	char path[50] = "./res/save/";

	strcat(path, player->ID);
	strcat(path, ".txt");
	//strcat(path, strcat(player->ID, ".txt"));

	FILE* fp = fopen(path, "r");
	if (fp == NULL)
		return false;

	fscanf(fp, "%d", &(player->play_time));
	fscanf(fp, "%d %d %d %d %d %d", &(map->map_line), &(map->box), &(map->keep), &(map->player_x), &(map->player_y), &(map->stage));
	for (int i = 0; i < map->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fscanf(fp, "%c", &(map->map[i][j]));
	map->next = NULL;
	return true;
}

void Input_ID(PLAYER* player)
{
	char str[50];
	int line = 0, i = 0;

	FILE* fp = fopen("./res/ID_inputbox.txt", "r");
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

	Cursor_Move(POS_X + 16, POS_Y + 2);
	scanf("%s", player->ID);
}

void Display_Help()
{
	char str[100];
	char key = ' ';

	FILE* fp = fopen("./res/help.txt", "r");

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
}

/*================================================
game command
================================================*/
void Restart_Cur_Map(MAP* init_map, MAP* cur_map)
{
	Deep_Copy(init_map, cur_map);
	//undo var reset
	system("cls");
	Print_Map(cur_map);
}

void Restart_Game(PLAYER* player, MAP* init_map, MAP* cur_map, MAP** map_p, int* stage)
{
	//player->play_time = 0;
	*stage = 0;
	*map_p = init_map;
	cur_map->keep = 0;
}

void Save(PLAYER* player, MAP* cur_map)
{
	char path[30] = "./res/save/";
	strcat(path, player->ID);
	strcat(path, ".txt");

	FILE* fp = fopen(path, "w");

	fprintf(fp, "%d\n", player->play_time);
	fprintf(fp, "%d %d %d %d %d %d", cur_map->map_line, cur_map->box, cur_map->keep, cur_map->player_x, cur_map->player_y, cur_map->stage);
	for (int i = 0; i < cur_map->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fprintf(fp, "%c", cur_map->map[i][j]);
	fclose(fp);

	Cursor_Move(POS_X, POS_Y+cur_map->map_line+3);
	printf("Save\n");
}

void Player_Move(MAP* init_map, MAP* cur_map, char key)
{
	int cur_x, cur_y, next_x, next_y, check_x, check_y;

	next_x = check_x = cur_x = cur_map->player_x;
	next_y = check_y = cur_y = cur_map->player_y;

	switch (key)
	{
	case 'a': next_x--; check_x -= 2; break;
	case 'd': next_x++; check_x += 2; break;
	case 'w': next_y--; check_y -= 2; break;
	case 's': next_y++; check_y += 2; break;
	}

	char next_c = cur_map->map[next_y][next_x];
	char isbox = init_map->map[cur_y][cur_x];
	char check_c = cur_map->map[check_y][check_x];

	if (next_c == ' ')
	{
		cur_map->map[next_y][next_x] = '@';
		if (isbox == 'O')
			cur_map->map[cur_y][cur_x] = 'O';
		else
			cur_map->map[cur_y][cur_x] = ' ';
	}
	else if (next_c == '$')
	{
		if (check_c == ' ')
		{
			cur_map->map[cur_y][cur_x] = ' ';
			cur_map->map[next_y][next_x] = '@';
			cur_map->map[check_y][check_x] = '$';
		}
		else if (check_c == 'O')
		{
			cur_map->map[next_y][next_x] = '@';
			cur_map->map[check_y][check_x] = '$';
			(cur_map->keep)--;
			if (isbox == 'O')
			{
				cur_map->map[cur_y][cur_x] = 'O';
				(cur_map->keep)++;
			}
			else
				cur_map->map[cur_y][cur_x] = ' ';
		}
		else
			return;
	}
	else if (next_c == 'O')
	{
		cur_map->map[next_y][next_x] = '@';
		if (isbox == 'O')
			cur_map->map[cur_y][cur_x] = 'O';
		else
			cur_map->map[cur_y][cur_x] = ' ';
	}
	else
		return;

	cur_map->player_x = next_x;
	cur_map->player_y = next_y;

	system("cls");
	Print_Map(cur_map);
}
