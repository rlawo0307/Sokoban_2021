#include "command.h"
#include "func.h"

void Play(PLAYER* player, MAP* init_map, int op)
{
	MAP* map_p = init_map;
	MAP cur_map;
	MAP* tmp = (MAP*)calloc(1, sizeof(MAP));
	char key;
	int i = 0, stage = 1;
	clock_t start_time, end_time;

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
	
	while (map_p != NULL)
	{
		if (op == NEW_GAME)
		{
			Init_Data(map_p, tmp);
			Init_Data(tmp, &cur_map);
		}
		else
			Init_Data(&cur_map, tmp);

		start_time = clock();
		Print_Map(&cur_map);
		while (1)
		{
			key = getch();
			switch (key)
			{
			case 'u': Undo(tmp, &cur_map); break;
			case 'r': Restart_Cur_Map(map_p, &cur_map, tmp); break;
			case 'n': Restart_Game(player, init_map, &cur_map, &map_p, &stage); break;
			case 'e': Save(player, &cur_map, start_time); return;
			case 'p': Save(player, &cur_map, start_time); break;
			case 'a':
			case 'd':
			case 'w':
			case 's': Player_Move(map_p, &cur_map, tmp, key); break;
			}
			if (cur_map.keep == 0)
			{
				if (stage != 0)
				{
					//end_time = clock();
					//Cal_Play_Time(player->play_time, stage, start_time, end_time);
					Save(player, &cur_map, start_time);
					Cursor_Move(POS_X, POS_Y + cur_map.map_line + 4);
					printf("Stage Clear!\n");
					Sleep(1000);
				}
				break;
			}
		}
		stage++;
		map_p = map_p->next;
		op = NEW_GAME;
	}
	printf("\nSokoban Clear~!\n");
}

bool Load(PLAYER* player, MAP* map)
{
	char path[50] = "./res/save/";

	strcat(path, player->ID);
	strcat(path, ".txt");

	FILE* fp = fopen(path, "r");
	if (fp == NULL)
		return false;

	fscanf(fp, "%.3fd", &(player->play_time));
	fscanf(fp, "%d %d %d %d %d %d %d\n", &(map->map_line), &(map->box), &(map->keep), &(map->player_x), &(map->player_y), &(map->stage), &(map->undo));
	for (int i = 0; i < map->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fscanf(fp, "%c", &(map->map[i][j]));
	map->next = NULL;
	return true;
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

void Undo(MAP* tmp, MAP* cur_map)
{
	if (cur_map->undo < 5 && !(tmp->player_x == cur_map->player_x && tmp->player_y == cur_map->player_y))
	{
		Init_Data(tmp, cur_map);
		(cur_map->undo)++;
		Print_Map(cur_map);
	}
}

void Restart_Cur_Map(MAP* map_p, MAP* cur_map, MAP* tmp)
{
	Init_Data(map_p, tmp);
	Init_Data(tmp, cur_map);
	cur_map->undo = 0;
	system("cls");
	Print_Map(cur_map);
}

void Restart_Game(PLAYER* player, MAP* init_map, MAP* cur_map, MAP** map_p, int* stage)
{
	Init_Play_Time(player, *stage, RESTART_GAME);
	*stage = 0;
	*map_p = init_map;
	cur_map->keep = 0;
}

void Save(PLAYER* player, MAP* cur_map, int start_time)
{
	int i = 0;
	PLAY_TIME* tmp = player->play_time;
	char path[30] = "./res/save/";
	strcat(path, player->ID);
	strcat(path, ".txt");
	FILE* fp = fopen(path, "w");

	Cal_Play_Time(player->play_time, cur_map->stage, start_time, clock());

	fprintf(fp, "ID : %s\n", player->ID);
	fprintf(fp, "Last Stage : %d\n", cur_map->stage);
	fprintf(fp, "Total Play Time : %.3f\n", player->play_time->play_time);
	while (i++ < cur_map->stage)
	{
		tmp = tmp->next;
		fprintf(fp, "\tStage %d : %.3f\n", tmp->stage, tmp->play_time);
	}
	fprintf(fp, "map line : %d\nbox : %d\nkeep : %d\nplayer_x : %d\nplayer_y : %d\nundo : %d\n",
		cur_map->map_line, cur_map->box, cur_map->keep, cur_map->player_x, cur_map->player_y, cur_map->stage, cur_map->undo);
	for (int i = 0; i < cur_map->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fprintf(fp, "%c", cur_map->map[i][j]);

	Cursor_Move(POS_X, POS_Y+cur_map->map_line+3);
	printf("Save\n");
	fclose(fp);
}

void Player_Move(MAP* init_map, MAP* cur_map, MAP* tmp, char key)
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

	Init_Data(cur_map, tmp);

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

void Rank()
{
	;
}