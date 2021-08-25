#include "command.h"
#include "func.h"

void Play(PLAYER* player)
{
	DATA1 init_data;
	DATA2 cur_data;
	bool game = true;
	char key;

	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return;
	}

	while (game)
	{
		Ready(fp, player, &init_data, &cur_data);
		while (cur_data.keep != 0)
		{
			key = getch();
			switch (key)
			{
			case 'u': break;
			case 'r': Restart_Cur_Map(&init_data, &cur_data); break;
			case 'n': Restart_Game(fp, &player, &init_data, &cur_data); break;
			case 'e': return 0;
			case 'p': Save(&player, &init_data, &cur_data); break;
			case 'a':
			case 'd':
			case 'w':
			case 's': Player_Move(&init_data, &cur_data, key); break;
			}
		}
		if (fgetc(fp) == EOF)
			break;
	}
	fclose(fp);
	printf("\nSokoban Clear~!\n");

}

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

	fprintf(fp, "%s %d ", player->ID, player->play_time);
	for (int i = 0; i < init_data->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fprintf(fp, "%d ", init_data->map[i][j]);
	fprintf(fp, "%d %d %d %d %d", init_data->map_line, init_data->box, init_data->keep, init_data->player_x, init_data->player_y);
	for (int i = 0; i < cur_data->map_line; i++)
		for (int j = 0; j < MAP_MAX_COL; j++)
			fprintf(fp, "%d ", cur_data->map[i][j]);
	fprintf(fp, "%d %d %d %d %d %d", cur_data->map_line, cur_data->box, cur_data->keep, cur_data->player_x, cur_data->player_y, cur_data->stage);
	fclose(fp);
}

void Load()
{
	;
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


