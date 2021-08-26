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
void Restart_Game(MAP*, MAP*, MAP**, int*, clock_t*);
void Save(PLAYER*, MAP*, clock_t);
void Player_Move(MAP*, MAP*, MAP*, char);
void Rank();
