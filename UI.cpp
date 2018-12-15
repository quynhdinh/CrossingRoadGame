#include "Header.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*void Menu() {
	GotoXY(20, 20);
	cout << "Crossing Road the Game" << endl;
	GotoXY(20, 21); cout << "1. Play" << endl;
	GotoXY(20, 22); cout << "2. Load" << endl;
	GotoXY(20, 23); cout << "3. Exit" << endl;
}*/

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void Light::DrawRed(int x, int y) {
	GotoXY(x, y - 1);
	SetColor(12); //red
	cout << char(220); //bottom
	GotoXY(x, y);
	SetColor(8); //grey
	cout << char(223); //upper
	SetColor(15);
}
void Light::DrawGreen(int x, int y) {
	GotoXY(x, y - 1);
	SetColor(8); //grey
	cout << char(220); //bottom
	GotoXY(x, y);
	SetColor(10);
	cout << char(223); //upper
	SetColor(15);
}

void LoadingBar() {
	float progress = 0.0;
	while (progress < 1.0) {
		Sleep(100);
		int barWidth = 70;
		GotoXY(15, 17);
		cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) cout << "=";
			else if (i == pos) cout << ">";
			else cout << " ";
		}
		cout << "] " << 100 << " %\r";
		cout.flush();
		progress += 0.16;
	}
}