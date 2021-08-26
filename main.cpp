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
	Menu(&player, map);
	return 0;
}
