#pragma warning(disable:4996)

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "func.h"

void Play(PLAYER*, MAP*, int);
bool Load(PLAYER*, MAP*);
void Input_ID(PLAYER*);
void Display_Help();

void Restart_Cur_Map(MAP*, MAP*);
void Restart_Game(PLAYER*, MAP*, MAP*, MAP**, int*);
void Save(PLAYER*, MAP*);
void Player_Move(MAP*, MAP*, char);
