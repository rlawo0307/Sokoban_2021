#include "start.h"

void New_Game(PLAYER* player)
{
	char str[50];
	int line = 0;
	char key = ' ';

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

	Cursor_Move(POS_X + 50, POS_Y + 6);
	while (key != 'z' && key != 'h' && key != 't')
	{
		key = getch();
		switch (key)
		{
		case 'z': Play(player, 0, NULL); break;
		case 'h': break;
		case 't': break;
		}
	}
}


