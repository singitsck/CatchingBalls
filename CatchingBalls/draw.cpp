#include <windows.h>
#include <stdio.h>
#include "draw.h"


void DrawString(HDC hDC, LONG posX, LONG posY, char *outText) {
	char outStr[100];
	SetBkColor(hDC, BACKGROUND_COLOR);      // background color
	SetTextColor(hDC, TEXT_COLOR);          // text color
	sprintf_s(outStr, "%s                   ", outText);
	TextOut(hDC, posX, posY, outStr, strlen(outStr));