#include "Header.h"

CGAME::CGAME() {

	//set level
	lv[0] = new Level(4,7,2,0,0,0,4);
	lv[1] = new Level(4,7,2,2,2,2,1);
	lv[2] = new Level(5, 6, 2, 2, 3, 3, 3);
	lv[3] = new Level(5, 6, 2, 3, 3, 2, 3);
	lv[4] = new Level(5, 6, 3, 3, 3, 3, 2);
	lv[5] = new Level(7, 4, 2, 3, 3, 3, 3);
	lv[6] = new Level(7, 4, 3, 3, 3, 3, 3);
	lv[7] = new Level(7,4,4,4,4,4,4);
	lv[8] = new Level(9,3,3,6,5,4,4);
	lv[9] = new Level(9,3,4,7,7,7,7);


	presentLevel = 1;
	//int c = level[presentLevel]->AmountOfCar;
	srand(time(NULL));

	ifstream fin; 
	fin.open("SaveFile.txt");
	numberOfSave = 0;

	if (!(fin.peek() == ifstream::traits_type::eof())) {
		int n; string name;
		while (!(fin.peek() == ifstream::traits_type::eof())) {
			getline(fin, name);
			fin >> n;
			fin.ignore(100, '\n');
			File[numberOfSave++] = new FileSave(n,name);
		}
	}
	
	fin.close();
} //Chuẩn bị dữ liệu cho tất cả các đối tượng
void CGAME::drawGame() {
	
	clrscr();

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfCar(); i++) axh[i] = NULL;
	for (int i = 0; i < lv[presentLevel - 1]->AmountOfTruck(); i++) axt[i] = NULL;
	for (int i = 0; i < lv[presentLevel - 1]->AmounrOfBird(); i++) ac[i] = NULL;
	for (int i = 0; i < lv[presentLevel - 1]->AmountOfDinasour(); i++) akl[i] = NULL;

	// backgceil (lane and destination = 0; 
	GotoXY(0, 0); for (int i = 0; i < WIDTH; i++) cout << "#";
	GotoXY(0, 1); for (int i = 1; i <= HEIGHT; i++) { cout << "#"; GotoXY(0, i); }
	GotoXY(WIDTH, 1); for (int i = 1; i <= HEIGHT; i++) { cout << "#"; GotoXY(WIDTH,i); }
	GotoXY(0, HEIGHT); for (int i = 0; i < WIDTH + 1; i++) cout << "#";

	// instruction
	//SetColor(4);

	GotoXY(WIDTH, 0); for (int i = 0; i < intWIDTH; i++) cout << "#";
	GotoXY(WIDTH + intWIDTH, 0); for (int i = 1; i <= HEIGHT; i++) { cout << "#"; GotoXY(WIDTH + intWIDTH, i);}
	GotoXY(WIDTH, HEIGHT); for (int i = 0; i < intWIDTH + 1; i++) cout << "#";
	GotoXY(WIDTH + 8, 2); cout << "CROSSING ROAD THE GAME!!!";
	GotoXY(WIDTH + 16, 4); cout << "LEVEL " << presentLevel;
	GotoXY(WIDTH + 6, 6); cout << "Please Pause before";
	GotoXY(WIDTH + 8, 8); cout << "	load/save game";
	GotoXY(WIDTH + 8, 10); cout << "P: Pause/Resume";
	GotoXY(WIDTH + 8, 12); cout << "K: Save";
	GotoXY(WIDTH + 8, 14); cout << "L: Load";
	GotoXY(WIDTH + 8, 16); cout << "ESC: Return";

	//SetColor(9);

	//
	int d = lv[presentLevel - 1]->getDistance();
	int n = lv[presentLevel - 1]->getLane();
	int m = HEIGHT;
	
	for (int i = 0; i < n; i++) {
		GotoXY(STARTLANE, m - 2); Finish = m - 2; m -= d;
		for (int j = 0; j < ENDLANE; ++j) cout << "_";
	}

	DrawLight(false);
	cn = new CPEOPLE(WIDTH/2, HEIGHT - 3);
	
} //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
CGAME::~CGAME() {

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfCar(); ++i) delete axh[i];
	for (int i = 0; i < lv[presentLevel - 1]->AmountOfTruck(); ++i) delete axt[i];
	
	for (int i = 0; i < lv[presentLevel - 1]->AmountOfDinasour(); ++i) delete akl[i];
	for (int i = 0; i < lv[presentLevel - 1]->AmounrOfBird(); ++i) delete ac[i];
	delete cn;
	for (int i = 0; i < 10; i++) {
		delete lv[i];
	}

}// Hủy tài nguyên đã cấp phát

CPEOPLE* CGAME::getPeople() {
	//cn.Up(2);
	//cn.isImpact(axt);
	return cn;

}//Lấy thông tin người
CVEHICLE* CGAME::getVehicle() {

	//return &axh;



	return axh[0];


}//Lấy danh sách các xe
CANIMAL* CGAME::getAnimal() {





	return ac[0];


}
//Lấy danh sách các thú
void CGAME::resetGame() {








} // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
void CGAME::exitGame(HANDLE) {

	//exit(0); // MAYBE NOT SAFE






} // Thực hiện thoát Thread
void CGAME::startGame() {

	drawGame();
	

} // Thực hiện bắt đầu vào trò chơi
void CGAME::loadGame() {

	Clean();
	ifstream fin; numberOfSave = 0;
	fin.open("SaveFile.txt");
	
	int level; string name;
	GotoXY(WIDTH + 8,20);
	if (fin.peek() == ifstream::traits_type::eof()) cout << "There is no save file!!";
	else {
		cout << "There are those save file: ";
		int line = 22;
		while (!(fin.peek() == ifstream::traits_type::eof())) {
			getline(fin,name);
			fin >> level;
			fin.ignore(100, '\n');
			File[numberOfSave] = new FileSave(level,name);
			GotoXY(WIDTH + 8, line); cout << numberOfSave + 1 << ". " << File[numberOfSave]->getName() << " "
				<< File[numberOfSave]->getLevel();
			numberOfSave += 1; line += 1;
		}

		char type; type = _getch();
		if (type != 27) {
			int a = type - '0';
			if (a <= numberOfSave && a > 0) {
				presentLevel = File[a - 1]->getLevel() - 1;
				UpdateLevel();
			}
		}

		Clean();
	}
	fin.close();
	

} // Thực hiện tải lại trò chơi đã lưu
void CGAME::saveGame() {

	Clean();
	ofstream fout; char a = 'a'; string name = "";
	GotoXY(WIDTH + 6, 20); cout << "Pls enter your save file name: ";
	
	while (a != 27) {
		GotoXY(WIDTH + 8, 22); cout << name << "                    ";
		a = _getch();
		if (a == 127 && name.size() > 0) name.pop_back();
		else if (a == 13) {

			fout.open("SaveFile.txt", std::ios_base::app);
			fout << name << endl << presentLevel << endl;
			fout.close();

			GotoXY(WIDTH + 8, 24); cout << "Save completely!!";
			Sleep(2000);
			break;
		}
		else if (a != 27) name.push_back(a);
	}

	Clean();
}// Thực hiện lưu lại dữ liệu trò chơi
void CGAME::pauseGame(HANDLE) {

	//GotoXY(WIDTH + 8, 10); cout << "p: Resume";


} // Tạm dừng Thread
void CGAME::resumeGame(HANDLE) {

	//GotoXY(WIDTH + 8, 10); cout << "p: Pause  ";
	
} //Quay lai Thread
void CGAME::updatePosPeople(char temp, int &ti) {

	int d = lv[presentLevel - 1]->getDistance();
	switch (temp) {
		case 87:
			if (cn->getY() != Finish) 
			cn ->Up(d);
			break;
		case 83:
			if (cn->getY() != HEIGHT - 3) 
			cn -> Down(d);
			break;
		case 65:
			if (cn->getX() - 4 >= STARTLANE) 
			cn -> Left(4);
			break;
		case 68:
			if (cn->getX() + 4 <= ENDLANE) 
			cn -> Right(4);
			break;
		default:
			break;
	}

	if (cn->isFinish(Finish)) {
		UpdateLevel(); ti = STOPTIME;
	}

} //Thực hiện điều khiển di chuyển của CPEOPLE
void CGAME::updatePosVehicle() {

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfCar(); i++) {

		if (axh[i] == NULL || axh[i]->IsDone()) {
			if (axh[i] != NULL) delete axh[i];
			int a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2);
			int b = rand() % 7 * 12;
			if (a % 2 == 0)
				axh[i] = new CCAR(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance());
			else
				axh[i] = new CCAR(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance());
		}
		else axh[i]->Move(10, 10);
	}

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfTruck(); i++) {

		if (axt[i] == NULL || axt[i]->IsDone()) {
			if (axt[i] != NULL) delete axt[i];
			int a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2);
			int b = rand() % 7 * 12;
			if (a % 2 == 0)
				axt[i] = new CTRUCK(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance());
			else
				axt[i] = new CTRUCK(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance());
		}
		else axt[i]->Move(10, 10);
	}


} //Thực hiện cho CTRUCK & CCAR di chuyển

void CGAME::Update() {

	//bool check[10][100] = {false};

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfCar(); i++) {

		if (axh[i] == NULL || axh[i]->IsDone()) {
			if (axh[i] != NULL) delete axh[i];
			int a, b;
			//do { 
				a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2); b = rand() % 7 * 12; 
			//} 
			//while (check[a][b]); check[a][b] = true;
			if (a % 2 == 0)
				axh[i] = new CCAR(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
			else
				axh[i] = new CCAR(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
		}
		else axh[i]->Move(10, 10);
	}

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfTruck(); i++) {

		if (axt[i] == NULL || axt[i]->IsDone()) {
			if (axt[i] != NULL) delete axt[i];
			int a, b;
			//do { 
			a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2); b = rand() % 7 * 12;
			//} 
			//while (check[a][b]); check[a][b] = true;
			if (a % 2 == 0)
				axt[i] = new CTRUCK(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
			else
				axt[i] = new CTRUCK(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
		}
		else axt[i]->Move(10, 10);
	}

	for (int i = 0; i < lv[presentLevel - 1]->AmounrOfBird(); i++) {

		if (ac[i] == NULL || ac[i]->IsDone()) {
			if (ac[i] != NULL) delete ac[i];
			int a, b;
			//do { 
			a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2); b = rand() % 7 * 12;
			//} 
			//while (check[a][b]); check[a][b] = true;
			if (a % 2 == 0)
				ac[i] = new CBIRD(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
			else
				ac[i] = new CBIRD(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
		}
		else ac[i]->Move(10, 10);
	}

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfDinasour(); i++) {

		if (akl[i] == NULL || akl[i]->IsDone()) {
			if (akl[i] != NULL) delete akl[i];
			int a, b;
			//do { 
			a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2); b = rand() % 7 * 12;
			//} 
			//while (check[a][b]); check[a][b] = true;
			if (a % 2 == 0)
				akl[i] = new CDINAUSOR(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
			else
				akl[i] = new CDINAUSOR(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
		}
		else akl[i]->Move(10, 10);
	}
}

void CGAME::updatePosAnimal() {

	for (int i = 0; i < lv[presentLevel - 1]->AmounrOfBird(); i++) {

		if (ac[i] == NULL || ac[i] -> IsDone())  {
			if (ac[i] != NULL) delete ac[i];
			int a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2);
			int b = rand() % 7 * 12;
			if (a % 2 == 0)
				ac[i] = new CBIRD(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
			else
				ac[i] = new CBIRD(STARTLANE - b, Finish + a *  lv[presentLevel - 1]->getDistance() - 1);
		}
		else ac[i]->Move(10, 10);
	}

	for (int i = 0; i < lv[presentLevel - 1]->AmountOfDinasour(); i++) {

		if (akl[i] == NULL || akl[i]->IsDone()) {
			if (akl[i] != NULL) delete akl[i];
			int a = 1 + rand() % (lv[presentLevel - 1]->getLane() - 2);
			int b = rand() % 7 * 12; 
			if (a % 2 == 0)
				akl[i] = new CDINAUSOR(ENDLANE + b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
			else
				akl[i] = new CDINAUSOR(STARTLANE - b, Finish + a * lv[presentLevel - 1]->getDistance() - 1);
		}
		else akl[i]->Move(10, 10);
	}

	

}//Thực hiện cho CDINAUSOR & CBIRD di chuyển

void CGAME::UpdateLevel() {

	presentLevel += 1;

	for (int i = 0; i < lv[presentLevel - 2]->AmountOfCar(); i++) delete axh[i];
	for (int i = 0; i < lv[presentLevel - 2]->AmountOfTruck(); i++) delete axt[i];
	for (int i = 0; i < lv[presentLevel - 2]->AmountOfDinasour(); i++) delete akl[i];
	for (int i = 0; i < lv[presentLevel - 2]->AmounrOfBird(); i++) delete ac[i];
	delete cn;

	if (presentLevel <= MAX_LEVEL) drawGame();
}

void CGAME::LoadLevel(int level) {

	presentLevel = level;
}

void CGAME::ScoreBoard(bool IsWin) {

	clrscr();
	if (IsWin) {
		GotoXY(WIDTH / 2-10, HEIGHT / 2);	   cout << "XXXXXX  XXXXXXX X    X  XXXXX XXXX      XX    XXXXX  XXXX";
		GotoXY(WIDTH / 2-10, HEIGHT / 2 + 1); cout << "X       X     X  X X  X  X     X   X    X  X     X    XX";
		GotoXY(WIDTH / 2-10, HEIGHT / 2 + 2); cout << "X       X     X  X  X X  X   X XXXXX   XXXXXX    X        X";
		GotoXY(WIDTH / 2-10, HEIGHT / 2 + 3); cout << "XXXXXX  XXXXXXX  X   XX  XXXXX X    X  X     X   X    XXXXX ";
	}
	else {
		GotoXY(WIDTH/2, HEIGHT/2);
			cout << "Opp!! You lose at level " << presentLevel << endl;
	}
}

void CGAME::Clean() {

	int i = 20;
	while (i < HEIGHT) {
		GotoXY(WIDTH + 1, i); for (int j = 0; j < intWIDTH - 1; j++) cout << " ";
		i += 1;
	}
}

bool CGAME::IsFinish() {

	if (presentLevel > MAX_LEVEL) return true;
	return false;

}

bool CGAME::IsImpact() {
	if (cn->isImpact(ac, lv[presentLevel - 1]->AmounrOfBird())) return true;
	if (cn->isImpact(akl, lv[presentLevel - 1]->AmountOfDinasour())) return true;
	if (cn->isImpact(axh, lv[presentLevel - 1]->AmountOfCar())) return true;
	if (cn->isImpact(axt, lv[presentLevel - 1]->AmountOfTruck())) return true;
	return false;
}

void CGAME::DrawLight(bool isRed) {

	Light a;
	
	int d = lv[presentLevel - 1]->getDistance();
	int n = lv[presentLevel - 1]->getLane();
	int m = HEIGHT - 2 - d;
	for (int i = 0; i < n - 2; i++) {
		int pos;
		if (i % 2 == 0) pos = STARTLANE - 1;
		else pos = ENDLANE + 3;

		if (isRed) a.DrawRed(pos,m);
		else a.DrawGreen(pos,m);
		m -= d;
	}
}





Level::Level(int lane, int distance, int speed, int car, int struck, int bird, int dinasour) {
	this->lane = lane; this->speed = speed; this->car = car; this->truck = struck;
	this->bird = bird; this->dina = dinasour; this->distance = distance;
}

int Level::getLane() { return lane;}
int Level::getDistance() { return distance; }
int Level::getSpeed() { return speed; }
int Level::AmounrOfBird() { return bird; }
int Level::AmountOfCar() { return car; }
int Level::AmountOfDinasour() { return dina; }
int Level::AmountOfTruck() { return truck; }

FileSave::FileSave(int presentLevel, string name) {
	level = presentLevel; this->name = name;
}

int FileSave::getLevel() {
	return level;
}

string FileSave::getName() {
	return name;
}