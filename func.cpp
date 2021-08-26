#include "func.h"
#include "command.h"

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
		case 't': break;
		}
	}
}

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
			(tmp->map_line)++;
		}
		line++;
	}
	return true;
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
}

void Deep_Copy(MAP* ori, MAP* des)
{
	for (int i = 0; i < MAP_MAX_ROW; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			des->map[i][j] = ori->map[i][j];

	des->map_line = ori->map_line;
	des->box = ori->box;
	des->keep = ori->keep;
	des->player_x = ori->player_x;
	des->player_y = ori->player_y;
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
}

