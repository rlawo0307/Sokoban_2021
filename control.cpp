#include "control.h"

int Get_Cursor(int op)
{
	CONSOLE_SCREEN_BUFFER_INFO cur_cursor;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_cursor);

	if (op == 1)
		return cur_cursor.dwCursorPosition.X;
	else
		return cur_cursor.dwCursorPosition.Y;
}

void Cursor_Move(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}