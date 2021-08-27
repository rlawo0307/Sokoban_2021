#include "func.h"
#include "command.h"

bool Load_Map(MAP* head)
{
	MAP* last = head;
	MAP* tmp = head;
	char str[MAP_MAX_COL];
	int line = 0;

	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return false;
	}

	while (1)
	{
		fgets(str, sizeof(str), fp);
		if (!strncmp(str, "map", 3))
		{
			line = -1;
			tmp = (MAP*)calloc(1, sizeof(MAP));
		}
		else if (!strncmp(str, "\n", 2) || !strncmp(str, "end", 3))
		{
			if (tmp->box != tmp->keep)
				return false;
			tmp->stage = last->stage + 1;
			last->next = tmp;
			last = last->next;
			if (!strncmp(str, "end", 3))
			{
				head->stage = tmp->stage;
				break;
			}
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
			(tmp->map_line)++;
		}
		line++;
	}
	return true;
}

void Init_Play_Time(PLAYER* player, int stage, int op)
{
	PLAY_TIME* cur = player->play_time;
	PLAY_TIME* tmp = NULL;
	
	int i = 0;

	if (op == START_GAME) // Start Game
	{
		while (i++ < stage)
		{
			tmp = (PLAY_TIME*)calloc(1, sizeof(PLAY_TIME));
			tmp->stage = i;
			tmp->play_time = 0;
			tmp->next = NULL;

			cur->next = tmp;
			cur = cur->next;
		}
		player->play_time->stage = cur->stage;
	}
	else // Restart Game
	{
		while (i++ <= stage)
		{
			cur->play_time = 0;
			cur = cur->next;
		}
	}
}

void Show_Start_Screen()
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
	fclose(fp);
}

void Menu(PLAYER* player, MAP* map)
{
	char key = ' ';

	Show_Start_Screen();
	Cursor_Move(POS_X + 50, POS_Y + 6);
	while (key != 'f' && key != 'n' && key != 'h' && key != 't')
	{
		key = getch();
		switch (key)
		{
		case 'n': Play(player, map, NEW_GAME); break;
		case 'f': Play(player, map, LOAD_FILE); break;
		case 'h': Display_Help(); Show_Start_Screen(); key = ' '; break;
		case 't': Rank(); break;
		}
	}
}

void Init_Data(MAP* ori, MAP* des)
{
	for (int i = 0; i < MAP_MAX_ROW; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			des->map[i][j] = ori->map[i][j];
	des->map_line = ori->map_line;
	des->box = ori->box;
	des->keep = ori->keep;
	des->player_x = ori->player_x;
	des->player_y = ori->player_y;
	des->stage = ori->stage;
	des->undo = ori->undo;
}

void Print_Map(MAP* cur_map)
{
	system("cls");
	Cursor_Move(POS_X, POS_Y);
	printf("< STAGE %d >\n\n", cur_map->stage);
	for (int i = 0; i < cur_map->map_line; i++)
	{
		Cursor_Move(Get_Cursor(1) + POS_X, Get_Cursor(0));
		printf("%s", cur_map->map[i]);
	}
	Cursor_Move(POS_X, POS_Y+cur_map->map_line+4);
	printf("Undo : %d", cur_map->undo);
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

void Cal_Play_Time(PLAY_TIME* head, int stage, int start_time, int end_time)
{
	PLAY_TIME* tmp = head->next;
	int i = 0;
	
	head->play_time = 0;
	while (tmp != NULL && tmp->stage <= stage)
	{
		if(tmp->stage == stage)
			tmp->play_time += (float)(end_time - start_time) / CLOCKS_PER_SEC;
		head->play_time += tmp->play_time;
		tmp = tmp->next;
	}
}