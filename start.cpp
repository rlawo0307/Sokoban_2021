#include "start.h"

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

void Enter_ID(char* ID)
{
	Cursor_Move(POS_X + 16, POS_Y + 2);
	scanf("%s", ID);
}

void Start_Menu(char* ID)
{
	char key = ' ';

	Cursor_Move(POS_X + 50, POS_Y + 6);
	while (key != '\n' && key != 'f' && key != 'h' && key != 't')
		key = getch();

	switch (key)
	{
	case '\n': Play(); break;
	case 'f': Load(); break;
	case 'h': Display_Help(); Start_Screen(ID); break;
	case 't': break;
	}
}

void Start_Screen(char* ID)
{
	Show_Start_Screen();
	Enter_ID(ID);
	Start_Menu(ID);
}