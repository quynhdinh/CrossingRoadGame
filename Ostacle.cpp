#include "Header.h"

CANIMAL::CANIMAL(int x, int y) {
	mX = x;
	mY = y;
	if (x >= ENDLANE) Way = -1;
	else Way = 1;
}
CDINAUSOR::CDINAUSOR(int x, int y) : CANIMAL(x, y) {
	Draw(x, y);
}
CBIRD::CBIRD(int x, int y) : CANIMAL(x, y) {
	Draw(x, y);
}
CVEHICLE::CVEHICLE(int x, int y) {
	mX = x;
	mY = y;
	if (x >= ENDLANE) Way = -1;
	else Way = 1;
}
CTRUCK::CTRUCK(int x, int y) : CVEHICLE(x, y) {
	Draw(x, y);
}
CCAR::CCAR(int x, int y) : CVEHICLE(x, y) {
	Draw(x, y);
}
void CTRUCK::Draw(int x, int y) {
	mX += Way; x = mX;
	if (x > ENDLANE + STARTLANE - 1 || x <= STARTLANE) return;
	GotoXY(x - 1, y + 1);
	cout << char(219); //block
	cout << char(219);
	cout << char(219);
	GotoXY(x - 1, y);
	cout << char(219);
	cout << char(219);
}
void CCAR::Draw(int x, int y) {
	mX += 2 * Way; x = mX;
	if (x > ENDLANE + STARTLANE - 1 || x <= STARTLANE) return;
	GotoXY(x - 1, y + 1);
	cout << char(219);
	cout << char(219);
	cout << char(219);
	GotoXY(x - 1, y);
	cout << char(220);
	cout << char(219);
	cout << char(220);

	/*GotoXY(x - 1, y);
	cout << char(220); //bottom
	cout << char(219);
	cout << char(220);*/

}
void CDINAUSOR::Draw(int x, int y) {
	//GotoXY(x,y);
	//cout << 'o';
	mX += 3 * Way; x = mX;
	if (x > ENDLANE + STARTLANE - 1 || x <= STARTLANE) return;
	GotoXY(x, y + 1);
	cout << char(223); //upper
	
	cout << char(219);
	GotoXY(x - 1, y + 1);
	cout << char(219);
	GotoXY(x, y);
	cout << char(220);
	GotoXY(x, y);
}
void CBIRD::Draw(int x, int y) {
	mX += 4 * Way; x = mX;
	if (x > ENDLANE + STARTLANE - 1 || x <= STARTLANE) return;
	GotoXY(x, y);
	cout << char(254);
	cout << char(223);
	GotoXY(x - 1, y);
	cout << char(223);

}

void CANIMAL::Move(int x, int y) {
	if (mX <= ENDLANE + STARTLANE - 1 && mX >= STARTLANE + 1) {
		GotoXY(mX - 2, mY - 1); cout << "    ";
		GotoXY(mX - 2, mY); cout << "    ";
		GotoXY(mX - 1, mY + 1); cout << "___";
	}
	Draw(mX, mY);

	//Sleep(10);
}

bool CANIMAL::IsDone() {
	if ((Way == -1 && mX <= STARTLANE + 3) || (Way == 1 && mX >= ENDLANE)) {
		GotoXY(mX - 2, mY - 1); cout << "    ";
		GotoXY(mX - 2, mY); cout << "    ";
		GotoXY(mX - 1, mY + 1); cout << "___";
		return true;
	}
	return false;
}

void CVEHICLE::Move(int x, int y) {
	if (mX <= ENDLANE + STARTLANE - 1 && mX >= STARTLANE + 1) {
		GotoXY(mX - 2, mY - 1); cout << "    ";
		GotoXY(mX - 2, mY); cout << "    ";
		GotoXY(mX - 1, mY + 1); cout << "___";
	}
	Draw(mX, mY);

	//Sleep(10);
}

bool CVEHICLE::IsDone() {
	if ((Way == -1 && mX <= STARTLANE + 3) || (Way == 1 && mX >= ENDLANE)) {
		GotoXY(mX - 2, mY - 1); cout << "    ";
		GotoXY(mX - 2, mY); cout << "    ";
		GotoXY(mX - 1, mY + 1); cout << "___";
		return true;
	}
	return false;
}




