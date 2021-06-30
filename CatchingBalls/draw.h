#define BACKGROUND_COLOR    RGB(128,128,128)
#define TEXT_COLOR          RGB(0,0,0)
#define BACKGROUND_BRUSH    CreateSolidBrush(BACKGROUND_COLOR)

void DrawString(HDC hDC, LONG posX, LONG posY, char *outText);
void DrawMouseCoordinates(HDC hDC, LONG posX, LONG posY, LONG x, LONG y);
#pragma once
