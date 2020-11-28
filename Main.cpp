//Các hằng số và biến toàn cục cần thiết
#include "Header.h"
#include <thread>

char MOVING;
CGAME *cg;
bool IS_EXIT = true;
bool IS_RUNNING = true;
bool SOUND = true;
int ti = STOPTIME;

void SubThread() {
	while (IS_EXIT) {
		++ti;
		if (!IS_RUNNING) continue;
		if (!cg->getPeople()->isDead()) // if player si still alive -> update positions
			cg->updatePosPeople(MOVING,ti);

		if (cg->IsFinish()) {
			cg->ScoreBoard(true);
			IS_EXIT = false;
			break;
		}


		MOVING = ' '; // Temp pause, waiting for keys from main
		if (ti % 300 > STOPTIME - 1) {
			cg->DrawLight(true);
			cg->Update();
		}
		else {
			cg->DrawLight(false);
		}
		//Sleep(1);
		//cg->drawGame();
		if (cg ->IsImpact()) { // crash car or animals
			cout << "\a";// sound
			cg->ScoreBoard(false);
			IS_EXIT = false;
			break;

		}

		Sleep(100/cg->getSpeed());
		//Sleep(1000);
	}
}

int main() {

	hidecursor();
	LoadingBar();
	cg = NULL;
	char t = '1';

	mciSendString(L"play gang.mp3 repeat", NULL, 0, NULL);

	while (t != '4')
	{
		clrscr();
		GotoXY(10, 1); cout << "       XX    XX   XXX  XXX           XXX  XXXXXXXX   XXX";
		GotoXY(10, 2); cout << "       XX    XX   XXX  XXX           XXX  XX   XXX   XXX";
		GotoXY(10, 3); cout << "       XX    XX   XXX  XXX           XXX  XX   XXX   XXX";
		GotoXY(10, 4); cout << "       XX    XX    XX  XXXXX       XXXXX  XXX  XXX   XXX";
		GotoXY(10, 5); cout << "       XX    XX    XX  XX XXX     XXX XX  XXXXXX        ";
		GotoXY(10, 6); cout << "XXXXXXXX     XX    XX  XX   XXX  XXX  XX  XXX        XXX";
		GotoXY(10, 7); cout << "XXXXXXXX     XXXXXXX   XX    XXXXX    XX  XXX        XXX";

		GotoXY(17, 10);  cout << "   1. New  game.";
		GotoXY(17, 11);  cout << "   2. Load game.";
		GotoXY(17, 12);  cout << "   3. Settings.";
		GotoXY(17, 13);  cout << "   4. Quit.";

		t = _getch();
		cg = new CGAME();
		IS_EXIT = true; IS_RUNNING = true; MOVING = ' '; ti = STOPTIME;


		if (t == '1' || t == '2') {
			if (t == '2') {

				ifstream fin; int numberOfSave = 0; FileSave *File[100];
				fin.open("SaveFile.txt");

				int level; string name;
				GotoXY(17, 15);
				if (fin.peek() == ifstream::traits_type::eof()) cout << "There is no save file!!";
				else {
					cout << "Here are saved files: ";
					int line = 17;
					while (!(fin.peek() == ifstream::traits_type::eof())) {
						getline(fin, name);
						fin >> level;
						fin.ignore(100, '\n');
						File[numberOfSave] = new FileSave(level, name);
						GotoXY(17, line); cout << numberOfSave + 1 << ". " << File[numberOfSave]->getName() << " "
							<< File[numberOfSave]->getLevel();
						numberOfSave += 1; line += 1;
					}

					fin.close();

					char type; type = _getch();
					if (type != 27) {
						int a = type - '0';
						if (a <= numberOfSave && a > 0) {
							int presentLevel = File[a - 1]->getLevel();
							cg->LoadLevel(presentLevel);
						}
					}
					else continue;
				}
			}

				int temp;
				FixConsoleWindow();
				//Menu();
				cg->startGame();
                thread t1(SubThread);
				//thread t2(SubThread2);

				while (IS_EXIT) {
					temp = toupper(_getch());
					if (!cg->getPeople()->isDead()) {
						if (temp == 27) {
							cg->exitGame(t1.native_handle());
							IS_EXIT = false;
							//t1.join();
						}
						else if (temp == 'P') {
							if (IS_RUNNING) {
								IS_RUNNING = false;
								cg->pauseGame(t1.native_handle());
							}
							else {
								IS_RUNNING = true;
								cg->resumeGame(t1.native_handle());
							}

						}
						else if (temp == 'K') {
							if (IS_RUNNING) {}//cout << "Pls pause before doing anything else";
							else cg->saveGame();
						}
						else if (temp == 'L') {
							if (IS_RUNNING) {}//cout << "Pls pause before doing anything else";
							else cg->loadGame();
						}
						else {
							if (IS_RUNNING) MOVING = temp; //Cập nhật bước di chuyển
							//cg->updatePosPeople(MOVING);
						}
					}
					else {
						if (temp == 'Y') cg->startGame();
						else {
							cg->exitGame(t1.native_handle());
							return 0;
						}
					}
				}
				t1.join();
		}
			else if (t == '3') {

			GotoXY(17, 15); cout << "1. Sound";
			GotoXY(17, 16); cout << "2. Tutorial";
			GotoXY(17, 17);  cout << "3. Choose character.";
			char  key = _getch();
			if (key == '1')
			{
				GotoXY(17, 16); cout << "It is turned "; if (SOUND) cout << "on"; else cout << "off"; cout << ". Do you  want to switch it ? Press s";
				char getS = _getch();
				if (getS == 's' || getS == 'S') {
					GotoXY(17, 17);
					cout << "Switching option..." << endl;
					Sleep(1000);
					SOUND = !SOUND;
					if (!SOUND) {
						mciSendString(L"pause gang.mp3", NULL, 0, NULL);
					}
					else {
						mciSendString(L"play gang.mp3 repeat", NULL, 0, NULL);
					}
				}
			}
			else if (key == '2'){
				GotoXY(17, 17); cout << "Using w,a,s,d keys to move up, left, down, right.";
				GotoXY(17, 18); cout << "There are 10 rounds for the game. Pass all of them to win a trophy.";
				_getch();
			}
			else if (key == '3'){
				ifstream fin;
				fin.open("character.txt");
				int num; fin >> num;
				while (num--){
					int index; fin >> index;
					string tmp[3];
					for (int i = 0; i < 3; i++){
						cin >> tmp[i];
					}
				}
				fin.close();
				t = _getch();
			}
			}
			else if (t == '4') {

					delete cg;
		}
	}
}

