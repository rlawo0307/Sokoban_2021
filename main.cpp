#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>
#include <conio.h>

#include "control.h"
#include "game.h"
#include "command.h"
#include "var.h"

//구조체 사용하는 형태로 바꾸기
int main()
{
	char key;
	PLAYER player;
	DATA1 init_data;
	DATA2 cur_data;
	bool game = true;

	//player.play_time = 0;
	Start_Screen(player.ID);

	FILE* fp = fopen("./res/map.txt", "r");
	if (fp == NULL)
	{
		printf("FILE OPEN FAIL\n");
		return 0;
	}

	while (game)
	{
		Init(&player, &init_data, &cur_data);
		Load_Map(fp, &init_data);
		Check_Box_Keep(&init_data, &cur_data);

		while (cur_data.keep != 0)
		{
			key = getch();
			switch (key)
			{
			case 'u': break;
			case 'r': Restart_Cur_Map(&init_data, &cur_data); break;
			case 'n': break;
			case 'e': return 0;
			case 'p': break;
			case 'f': break;
			case 'h': Display_Help(&cur_data); break;
			case 't': break;
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

	return 0;
}