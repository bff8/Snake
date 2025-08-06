#include"lib.h"
//HRESURL - коды ошибок для обработки

int UserStatus = 0;
bool StartGame = false;

int SizeX_SpawnMainWindow;
int SizeY_SpawnMainWindow;

HFONT TextInButton;
HFONT TextForInscriptions;
HBRUSH hButtonBrush;

HWND MainWindowCreate;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_GETMINMAXINFO: {
		MINMAXINFO* pt = (MINMAXINFO*)lParam;
		POINT pnt;
		pnt.x = SizeX_MainWindow;
		pnt.y = SizeY_MainWindow;
		pt->ptMaxTrackSize = pnt;
		pt->ptMinTrackSize = pnt;
		break;
	}
	case WM_CREATE: {
		hButtonBrush = CreateSolidBrush(RGB(72, 60, 220));
		TextInButton = CreateFontW(30, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"GOST type A");
		TextForInscriptions = CreateFontW(60, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial Black");
		break;
	}
	case WM_DRAWITEM:{
		LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
		if (pDIS->CtlType == ODT_BUTTON){
			WCHAR buttonText[256];
			GetWindowTextW(pDIS->hwndItem, buttonText, 256);
			SetBkMode(pDIS->hDC, TRANSPARENT);
			SetTextColor(pDIS->hDC, RGB(0, 0, 0)); // Черный текст
			SelectObject(pDIS->hDC, TextInButton);
			FillRect(pDIS->hDC, &pDIS->rcItem, hButtonBrush);// Заливаем кнопку цветом фона
			// Рисуем текст по центру
			DrawText(pDIS->hDC, buttonText, -1, &pDIS->rcItem,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			// Рамка вокруг кнопки
			FrameRect(pDIS->hDC, &pDIS->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));
			// Если кнопка нажата
			if (pDIS->itemState & ODS_SELECTED){
				// Меняем цвет текста и фона
				SetTextColor(pDIS->hDC, RGB(255, 255, 255)); // Белый текст
				SetBkColor(pDIS->hDC, RGB(50, 40, 150));      // Темно-синий фон
				// Перерисовываем текст
				DrawText(pDIS->hDC, buttonText, -1, &pDIS->rcItem,
					DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		break;
	}
	case WM_COMMAND: {
		DrawСlientАrea(LOWORD(wParam), MainWindowCreate);
		UserStatus = LOWORD(wParam); //Окно, которое пользователь сейчас видит
		if (LOWORD(wParam) == 4)
			PostQuitMessage(0); //Окно Exit = Выход из программы
		InvalidateRect(hWnd, 0, 0); //Обновление экрана для показа нового окна
		break;
	}
	case WM_KEYDOWN:{
		if (wParam == VK_SPACE and UserStatus == 1) {
			StartGame = true;
		}
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		RECT rc;
		HDC hdc = BeginPaint(hWnd, &ps);
		Image* image = new Image(L"BackgroundMainWindow.jpg");
		Graphics graphics(hdc);
		graphics.DrawImage(image, 0, 0, SizeX_MainWindow, SizeY_MainWindow);
		delete image;
		switch(UserStatus){
		case UserStatus_MainWindow: {
			SelectObject(hdc, TextForInscriptions);
			SetTextColor(hdc, RGB(0, 131, 49));
			SetBkMode(hdc, TRANSPARENT);
			SetTextAlign(hdc, TA_CENTER);
			TextOutW(hdc, 310, 200, L"SNAKE", 6);
			break;
		}
		case UserStatus_Play:{
			//Кастомный фон

			DrawСlientАrea(UserStatus, MainWindowCreate);
			break;
		}
		case UserStatus_ScoreBoard: {
			break;
		}
		case UserStatus_Settings: {
			SelectObject(hdc, TextForInscriptions);
			SetTextColor(hdc, RGB(0, 131, 49));
			SetBkMode(hdc, TRANSPARENT);
			SetTextAlign(hdc, TA_CENTER);
			TextOutW(hdc, 310, 200, L"SETTINGS", 9);
			break;
		}
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		DeleteObject(hButtonBrush);
		DeleteObject(TextInButton);
		PostQuitMessage(0);
	}
	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
}
ATOM CreateWindowClass() {
	WNDCLASSEXW wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = 0;
	wc.lpszClassName = L"MainClass";
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursorW(0,IDC_HAND);
	return RegisterClassExW(&wc);
}

BOOL Wnd() {
	MainWindowCreate = CreateWindowExW(NULL, L"MainClass", L"ёбанный пиздец", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		SizeX_SpawnMainWindow, SizeY_SpawnMainWindow, SizeX_MainWindow, SizeY_MainWindow, 0, 0, 0, 0);
	ShowWindow(MainWindowCreate, SW_SHOWNORMAL);
	//SetTimer(MainWindowCreate, 1, 500, NULL);
	DrawСlientАrea(UserStatus, MainWindowCreate);
	return true;
}

int main() {
	setlocale(LC_ALL, "RU");
	if (!Centering(SizeX_SpawnMainWindow, SizeY_SpawnMainWindow)) MessageBox(0, L"The centering function did not work", L"ERROR", MB_ICONWARNING);	CreateWindowClass();
	Wnd();

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	MSG message;
	while (GetMessageW(&message, 0, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
	
	GdiplusShutdown(gdiplusToken);
	return 0;
}
//Test commit