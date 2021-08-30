#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <float.h> 
#include "var.h"
#include "control.h"

void Show_Start_Screen();
void Menu(PLAYER*, MAP*);
void Init_Play_Time(PLAYER*, int, int);
bool Load_Map(MAP*);
void Init_Data(MAP*, MAP*);
void Print_Map(MAP*);
void Input_ID(PLAYER*);
void Cal_Play_Time(PLAY_TIME*, int, int, int);
void Show_Stage_Rank(int);
void Save_Rank(PLAYER*, int);
