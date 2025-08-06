#include"lib.h"

bool Centering(int& SizeX_SpawnMainWindow, int& SizeY_SpawnMainWindow) {
	int CenterScreenX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int CenterScreenY = GetSystemMetrics(SM_CYSCREEN) / 2;
	SizeX_SpawnMainWindow = (CenterScreenX - SizeX_MainWindow / 2);
	SizeY_SpawnMainWindow = (CenterScreenY - SizeY_MainWindow / 2);
	return true;
}
void SetAllWndFont(HFONT NameFont, ...) {
	va_list up;
	va_start(up, NameFont);
	HWND Window;
	while ((Window = va_arg(up, HWND))) {
		SetWindowFont(Window, NameFont, true);
	}
	va_end(up);
}
HWND CreateCustomButton(HWND hParent, int x, int y, int width, int height, LPCWSTR text, int id) {
	HWND Button = CreateWindowExW(0,L"BUTTON",text,WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
	x, y, width, height,hParent,(HMENU)id,NULL,NULL);
	ShowWindow(Button, SW_SHOWNORMAL);
	return Button;
}
