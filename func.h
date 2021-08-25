#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include "var.h"
#include "control.h"

bool Load_Map(FILE*, MAP*);
void Init_Data(MAP*, MAP*);

void Show_Start_Screen();
void Enter_ID(char*);
void Start_Menu(PLAYER*);
void Start_Screen(PLAYER*);
void Deep_Copy(DATA1*, DATA2*);
void Print_Map(DATA2*);

bool Check_Box_Keep(DATA1*, DATA2*);
//bool Ready(FILE*, PLAYER*, DATA1*, DATA2*);
void Player_Move(DATA1*, DATA2*, char);