#include "TkDrawString.h"
#include "DxLib.h"

void DrawStringFuchi(int X, int Y,char *String,unsigned int Color)
{
	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++)
			DrawString(X + x * 4, Y + y * 4, String, Color);
}
