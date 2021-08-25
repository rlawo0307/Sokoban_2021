#include "command.h"
#include "game.h"

void Restart_Cur_Map(DATA1* init_data, DATA2* cur_data)
{
	Deep_Copy(init_data, cur_data);
	//undo var reset
	system("cls");
	Print_Map(cur_data);
}

void Display_Help(DATA2* cur_data)
{
	char str[100];
	char key = ' ';

	FILE* fp = fopen("./res/help.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return;
	}

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
	Print_Map(cur_data);
}


