#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include <windows.h>
#include <conio.h>

#define MAP_MAX_ROW 31
#define MAP_MAX_COL 31

void Input_User(char*);
void Load_Map(char (*)[MAP_MAX_COL], FILE*, int*);
void Check_Box_Keep(char(*)[MAP_MAX_COL], int(*)[MAP_MAX_COL], int, int*, int*, int*, int*, int);
void Move(char(*)[MAP_MAX_COL], int(*)[MAP_MAX_COL], char, int*, int*, int, int, int*);

int main()
{
	char user[10];
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int keep_check[MAP_MAX_ROW][MAP_MAX_COL];
	char key;

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
		{
			memset(map[i], 0, sizeof(char) * MAP_MAX_COL);
			memset(keep_check[i], 0, sizeof(char) * MAP_MAX_COL);
		}

		//system("cls");
		Load_Map(map, fp, &line);
		Check_Box_Keep(map, keep_check, line, &box, &keep, &cur_x, &cur_y, stage);

		while (keep != 0)
		{
			key = getch();
			switch (key)
			{
			case 'u':
			case 'r':
			case 'n':
			case 'e': return 0;
			case 'p':
			case 'f':
			case 'd':
			case 't':
			case 'a':
			case 'h':
			case 'w':
			case 's': Move(map, keep_check, key, &cur_x, &cur_y, line, stage, &keep); break;
			}
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

void Check_Box_Keep(char(*map)[MAP_MAX_COL], int(*keep_check)[MAP_MAX_COL], int line, int* box, int* keep, int* cur_x, int* cur_y, int stage)
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < strlen(map[i]); j++)
			if (map[i][j] == '$')
				(*box)++;
			else if (map[i][j] == 'O')
			{
				keep_check[i][j] = 1;
				(*keep)++;
			}
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

void Move(char(*map)[MAP_MAX_COL], int(*keep_check)[MAP_MAX_COL], char key, int* cur_x, int* cur_y, int line, int stage, int* keep)
{
	char check;
	int next_x = *cur_x, next_y = *cur_y;
	int check_x = *cur_x, check_y = *cur_y;

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
		if (keep_check[*cur_y][*cur_x] == 1)
			map[*cur_y][*cur_x] = 'O';
		else
			map[*cur_y][*cur_x] = ' ';
	}
	else if (map[next_y][next_x] == '$')
	{
		check = map[check_y][check_x];
		if (check == ' ')
		{
			map[*cur_y][*cur_x] = ' ';
			map[next_y][next_x] = '@';
			map[check_y][check_x] = '$';
		}
		else if (check == 'O')
		{
			map[next_y][next_x] = '@';
			map[check_y][check_x] = '$';
			if (keep_check[*cur_y][*cur_x] == 1)
				map[*cur_y][*cur_x] = 'O';
			else
				map[*cur_y][*cur_x] = ' ';
		}
		else
			return;
	}
	else if (map[next_y][next_x] == 'O')
	{
		map[next_y][next_x] = '@';
		if (keep_check[*cur_y][*cur_x] == 1)
			map[*cur_y][*cur_x] = 'O';
		else
			map[*cur_y][*cur_x] = ' ';
	}
	else
		return;
	*cur_x = next_x;
	*cur_y = next_y;

	system("cls");
	Print_Map(map, stage);
}