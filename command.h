#pragma warning(disable:4996)

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "func.h"

void Play(PLAYER*, MAP*, int);
bool Load(PLAYER*, MAP*);
void Display_Help();

void Undo(MAP*, MAP*);
void Restart_Cur_Map(MAP*, MAP*, MAP*);
void Restart_Game(PLAYER*, MAP*, MAP*, MAP**, int*);
void Save_Data(PLAYER*, MAP*, int);
void Player_Move(MAP*, MAP*, MAP*, char);
void Show_Rank(MAP*);
