#pragma warning(disable:4996)

#include<stdio.h>

#include "command.h"
#include "var.h"

int main()
{
	PLAYER player;
	MAP* map = (MAP*)calloc(1, sizeof(MAP));

	if (Load_Map(map) == false)
	{
		printf("Check Your Map!\n");
		return 0;
	}

	player.play_time = (PLAY_TIME*)calloc(1, sizeof(PLAY_TIME));
	Init_Play_Time(&player, map->stage, START_GAME);

	Menu(&player, map);
	return 0;
}
