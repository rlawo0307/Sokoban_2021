#pragma once

#define MAP_MAX_ROW 31
#define MAP_MAX_COL 31
#define POS_X 3
#define POS_Y 3

typedef struct player
{
	char ID[30];
	int play_time;
}PLAYER;

typedef struct map
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int map_line;
	int box, keep;
	int player_x, player_y;
	int stage;
	MAP* next;
}MAP;