#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include "var.h"
#include "control.h"

void Init(PLAYER*, DATA1*, DATA2*);
void Start_Screen(char*);
void Deep_Copy(DATA1*, DATA2*);
void Print_Map(DATA2*);
void Load_Map(FILE*, DATA1*);
void Check_Box_Keep(DATA1*, DATA2*);
void Player_Move(DATA1*, DATA2*, char);