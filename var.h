#pragma once

#define MAP_MAX_ROW 31
#define MAP_MAX_COL 31
#define POS_X 3
#define POS_Y 3
#define NEW_GAME 1
#define LOAD_FILE 0
#define START_GAME 0
#define RESTART_GAME 1

typedef struct play_time
{
	int stage;
	float play_time;
	struct play_time* next;
}PLAY_TIME;

typedef struct player
{
	char ID[30] = "";
	PLAY_TIME* play_time;
}PLAYER;

typedef struct map
{
	char map[MAP_MAX_ROW][MAP_MAX_COL];
	int map_line;
	int box, keep;
	int player_x, player_y;
	int stage;
	int undo;
	struct map* next;
}MAP;