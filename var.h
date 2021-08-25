#pragma once

#define MAP_MAX_ROW 31
#define MAP_MAX_COL 31
#define POS_X 5
#define POS_Y 5

typedef struct player
{
	char ID[30];
	int play_time;
}PLAYER;

typedef struct initial_data
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int map_line;
	int box, keep;
	int player_x, player_y;
}DATA1;

typedef struct cur_data
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int map_line;
	int box, keep;
	int player_x, player_y;
	int stage;
}DATA2;