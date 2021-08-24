#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include "var.h"
#include "control.h"

void Start_Screen(char*);
void Print_Map(char(*)[MAP_MAX_COL], int);
void Load_Map(char(*)[MAP_MAX_COL], FILE*, int*);
void Check_Box_Keep(char(*)[MAP_MAX_COL], char(*)[MAP_MAX_COL], int(*)[MAP_MAX_COL], int, int*, int*, int*, int*, int);
void Player_Move(char(*)[MAP_MAX_COL], int(*)[MAP_MAX_COL], char, int*, int*, int, int, int*);