#pragma once
void SetAllWndFont(HFONT NameFont, ...);
bool Centering(int& SizeX_SpawnMainWindow, int& SizeY_SpawnMainWindow);
HWND CreateCustomButton(HWND hParent, int x, int y, int width, int height, LPCWSTR text, int id);