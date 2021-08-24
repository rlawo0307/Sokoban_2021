#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include "var.h"
#include "control.h"

void Start_Screen(char* user);
void Print_Map(char(*map)[MAP_MAX_COL], int stage);
void Load_Map(char(*map)[MAP_MAX_COL], FILE* fp, int* line);
void Check_Box_Keep(char(*map)[MAP_MAX_COL], int(*keep_check)[MAP_MAX_COL], int line, int* box, int* keep, int* cur_x, int* cur_y, int stage);
void Player_Move(char(*map)[MAP_MAX_COL], int(*keep_check)[MAP_MAX_COL], char key, int* cur_x, int* cur_y, int line, int stage, int* keep);
