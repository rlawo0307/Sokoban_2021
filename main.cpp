#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include <windows.h>

#define MAP_MAX_ROW 31
#define MAP_MAX_COL 31

void Input_User(char*);
void Load_Map(char (*map)[MAP_MAX_COL], FILE* fp, int*);
void Check_Box_Keep(char(*map)[MAP_MAX_COL], int, int*, int*, int*, int*, int);
void Move(char(*map)[MAP_MAX_COL], int*, int*, int, int);

int main()
{
	return 0;
}