#include"lib.h"
bool PlayStatus = false;

extern bool StartGame;

std::stack<HWND> CurrentStack;

bool ClearCurrentWindowStack() {
	while (!CurrentStack.empty()) {
		DestroyWindow(CurrentStack.top());
		CurrentStack.pop();
	}
	return true;
}

bool Draw�lient�rea(uint32_t UserStatus, HWND MainWindowCreate) {
	ClearCurrentWindowStack();
	switch (UserStatus) {
	case UserStatus_MainWindow: {
		wchar_t TEXTINBUTTON[4][MAX_PATH] = {
			L"PLAY",
			L"SCOREBOARD",
			L"SETTINGS",
			L"EXIT"
		};
		uint32_t yBtn = 300;
		for (int i = UserStatus_Play; i <= UserStatus_Settings+1; i++) {
			HWND Button = CreateCustomButton(MainWindowCreate, SizeX_MainWindow / 2 - 100, yBtn, SizeX_ButtonMainWindow, SizeY_ButtonMainWindow, TEXTINBUTTON[i-1], i);
			if (!Button)wcerr << L"ERROR CreateCustomButton";
			CurrentStack.push(Button);
			yBtn += 100;
		}
		break;
	}
	case UserStatus_Play: {
		cout << "����� �� UserStatus_Play"<<endl;
		uint32_t SnakeField[9][9]{};
		uint32_t SnakeSize = 1;
		CreateCustomButton(MainWindowCreate, SizeX_MainWindow / 2 - 100, 300, SizeX_ButtonMainWindow, SizeY_ButtonMainWindow, L"Z", 5);
		struct Coord {
			uint32_t X;
			uint32_t Y;
		};
		enum Turn{TOP,BOTTOM,LEFT,RIGHT};
		if (PlayStatus == false and StartGame == true) { //PlayStatus == false � ������ �� 

			PlayStatus == true;
			cout << "����� �� if"<<endl;
			Coord Apple{ (rand() % 9),(rand() % 9) };
			Coord Snake{ (rand() % 9),(rand() % 9) };
			if ((Apple.X and Apple.Y) == (Snake.X and Snake.Y)) {
				Apple.X = Apple.Y = (rand() % 9);
			}
			
		}
		// ����� � y ������ 
		// ����� ��������� ��������� ������� �� � � � �� ��� �� ��� ����
		// ����� ��������� ��������� ���� �� � �
		// ����� ��������� ������������ �� ���� ����� ����� �
		// �� ���� ����� � �����
		// ����� ���� ������� ������
		//
		break;
	}
	case UserStatus_ScoreBoard: {

		break;
	}
	case UserStatus_Settings: {
		
		break;
	}
	}
	return true;
}