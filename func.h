#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include "var.h"
#include "control.h"

void Show_Start_Screen();
void Menu(PLAYER*, MAP*);
bool Load_Map(MAP*);
void Init_Data(MAP*, MAP*);
void Print_Map(MAP*);
void Input_ID(PLAYER*);
