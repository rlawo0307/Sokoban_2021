#include "command.h"
#include "func.h"

/*================================================
start command
================================================*/
void Play(PLAYER* player, MAP* init_map, int stage)
{
	MAP cur_map;
	MAP* tmp;
	bool game = true;
	char key;
	int i = 0;

	while (i < stage)
	{
		tmp = tmp->next;
		i++;
	}

	while (game)
	{
		if (init_map == NULL)
		{
			printf("\nSokoban Clear~!\n");
			break;
		}
		else
		{
			Init_Data(init_map, &cur_map);
			
			while (cur_map.keep != 0)
			{
				key = getch();
				switch (key)
				{
				case 'u': break;
				case 'r': Restart_Cur_Map(&init_data, &cur_data); break;
				case 'n': Restart_Game(map_fp, player, &init_data, &cur_data); break;
				case 'e': Save(player, &init_data, &cur_data); game = false; break;
				case 'p': Save(player, &init_data, &cur_data); break;
				case 'a':
				case 'd':
				case 'w':
				case 's': Player_Move(&init_data, &cur_data, key); break;
				}
			}

		}
		tmp = tmp->next;
	}
}

void Load(PLAYER* player, MAP* map, int stage)
{
	char path[50] = "./save/";
	char ID[20];
	printf("\n ID : ");
	scanf("%s", ID);
	strcat(path, strcat(ID, ".txt"));

	FILE* fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return;
	}

	Play(player, map, stage);
}

void New_Game(PLAYER* player, MAP* map, int stage)
{
	char str[50];
	int line = 0, i = 0;
	char key = ' ';
	MAP* tmp = map;

	//Show ID Inputbox
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

	//Scan Player ID
	Cursor_Move(POS_X + 16, POS_Y + 2);
	scanf("%s", player->ID);

	Play(player, map, stage);
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
void Restart_Cur_Map(DATA1* init_data, DATA2* cur_data)
{
	Deep_Copy(init_data, cur_data);
	//undo var reset
	system("cls");
	Print_Map(cur_data);
}

void Restart_Game(FILE* fp, PLAYER* player, DATA1* init_data, DATA2* cur_data)
{
	//player->play_time = 0;
	cur_data->stage = 0;
	fseek(fp, 0, SEEK_SET);
	Ready(fp, player, init_data, cur_data);
}

void Save(PLAYER* player, DATA1* init_data, DATA2* cur_data)
{
	char path[30] = "./res/save/";
	strcat(path, player->ID);
	strcat(path, ".txt");

	FILE* fp = fopen(path, "w");

	fprintf(fp, "%d\n", player->play_time);
	for (int i = 0; i < cur_data->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fprintf(fp, "%d ", cur_data->map[i][j]);
	fprintf(fp, "%d %d %d %d %d %d", cur_data->map_line, cur_data->box, cur_data->keep, cur_data->player_x, cur_data->player_y, cur_data->stage);
	fclose(fp);
}





