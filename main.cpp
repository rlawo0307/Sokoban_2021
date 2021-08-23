#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include <windows.h>

#define MAP_MAX_ROW 31
#define MAP_MAX_COL 31

void Input_User(char*);
void Load_Map(char (*map)[MAP_MAX_COL], FILE* fp, int*);
void Check_Box_Keep(char(*map)[MAP_MAX_COL], int, int*, int*, int*, int*, int);
void Move(char(*map)[MAP_MAX_COL], int*, int*, int, int);

int main()
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	char user[10];

	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return 0;
	}

	//Input_User(user);

	int stage = 1, line, box, keep, cur_x, cur_y;

	while (stage)
	{
		line = box = keep = cur_x = cur_y = 0;

		for (int i = 0; i < MAP_MAX_ROW; i++)
				memset(map[i], 0, sizeof(char)*MAP_MAX_COL);

		//system("cls");
		Load_Map(map, fp, &line);
		Check_Box_Keep(map, line, &box, &keep, &cur_x, &cur_y, stage);

		while (keep != 0)
		{
			Move(map, &cur_x, &cur_y, line, stage);
		}
		
		stage++;

		if (fgetc(fp) == EOF)
			break;
	}
	fclose(fp);
	printf("\nSokoban Clear~!\n");
	return 0;
}

void Input_User(char* user)
{
	printf("User Name : ");
	scanf("%s", user);
}

void Print_Map(char(*map)[MAP_MAX_COL], int stage)
{
	printf("< STAGE %d >\n\n", stage);
	for (int i = stage - 1 ? 0 : 1; i < MAP_MAX_ROW; i++)
		printf("%s", map[i]);
}

void Load_Map(char (*map)[MAP_MAX_COL], FILE* fp, int* line)
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

void Check_Box_Keep(char(*map)[MAP_MAX_COL], int line, int* box, int* keep, int* cur_x, int* cur_y, int stage)
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < strlen(map[i]); j++)
			if (map[i][j] == '$')
				(*box)++;
			else if (map[i][j] == 'O')
				(*keep)++;
			else if (map[i][j] == '@')
			{
				*cur_x = j;
				*cur_y = i;
			}

	if (*box == *keep)
		Print_Map(map, stage);
	else
		printf("Check Your Map!\n");
}

void Move(char(*map)[MAP_MAX_COL],int* cur_x, int* cur_y, int line, int stage)
{
	char key;
	int next_x = *cur_x, next_y = *cur_y;

	scanf("%c", &key);

	printf("%d %d\n", *cur_x, *cur_y);

	switch (key)
	{
	case 'a': next_x--;  break; 
	case 'd': next_x++; break;
	case 'w': next_y--; break;
	case 's': next_y++; break;
	}
	
	if (map[next_y][next_x] != '#' && next_x >= 0 && next_y >= 0)
		if (map[next_y][next_x] == '$')
		{
			map[]
		}
	{
		map[*cur_y][*cur_x] = ' ';
		map[next_y][next_x] = '@';
		*cur_x = next_x;
		*cur_y = next_y;
	}

	system("cls");
	Print_Map(map, stage);
	
}