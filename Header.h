#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <thread>
#include <fstream>
#include <string>
#include <map>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;
const int MAX_LEVEL = 10;
const float HEIGHT = 29;
const float WIDTH = 80;
const int STARTLANE = 3;
const int ENDLANE = WIDTH - 6;
const int intWIDTH = 118 - WIDTH;
const int STOPTIME = 41;

/*class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(int, int) = 0;
	//...
};

class CTRUCK : public CVEHICLE {
public:
	void Move(int, int) {};
	//...
};

class CCAR : public CVEHICLE {
public:
	void Move(int, int) {};
	//...
};

class CANIMAL {
protected: int mX, mY, Way;
public:
	CANIMAL(int, int);
	void Move(int, int);
	virtual void Draw(int x, int y) {};
	bool IsDone();


	//virtual void Tell();
};

class CDINAUSOR : public CANIMAL {
	
public:
	CDINAUSOR(int x, int y) : CANIMAL(x, y) {};
	void Draw(int x, int y);
	//...
};

class CBIRD : public CANIMAL {
public:
	CBIRD(int x, int y) : CANIMAL(x, y) {};
	void Draw(int x, int y);
	//void Move(int, int);
	//bool IsDone();
	//...
};*/

class CVEHICLE {
protected:	int mX, mY, Way;
public:
	CVEHICLE(int x, int y);
	void virtual Draw(int x, int y) = 0;
	void Move(int, int);
	bool IsDone();
	int getX() { return mX; }
	int getY() { return mY; }
	//...
};

class CTRUCK : public CVEHICLE {
public:
	CTRUCK(int x, int y);
	void Draw(int x, int y);
	//void Move(int, int);
	//...
};

class CCAR : public CVEHICLE {
public:
	CCAR(int x, int y);
	void Draw(int x, int y);

	//void Move(int, int) {};
	//...
};

class CANIMAL {
protected:
	int mX, mY, Way;
public:
	CANIMAL(int x, int y);
	void virtual Draw(int x, int y) = 0;
	void Move(int, int);
	bool IsDone();
	int getX() { return mX; }
	int getY() { return mY; }
	//virtual void Tell();
};

class CDINAUSOR : public CANIMAL {
public:
	CDINAUSOR(int x, int y);
	void Draw(int x, int y);
	//...
};

class CBIRD : public CANIMAL {
public:
	CBIRD(int x, int y);
	void Draw(int x, int y);
	//void Move(int, int);
	//bool IsDone();
	//...
};


class CPEOPLE {
	int mX, mY;
	char map[3][3];
	bool mState; //Trạng thái sống chết
	int type;
public:
	CPEOPLE(int x, int y);
	void ReDraw(int x, int y);
	void Up(int x);
	void Left(int x);
	void Right(int x);
	void Down(int x);
	bool isImpact(CVEHICLE* a[] , int n);
	bool isImpact(CANIMAL* b[] , int n);

	bool isFinish(int Finish);
	bool isDead();
	int getX();
	int getY();
};

class Level {
private:
	int lane; // number of lanes
	int distance;
	int speed; // speed of obstacle
	 int car, truck, dina, bird;
public:
	Level(int,int,int,int,int,int,int);
	int getLane();
	int getDistance();
	int getSpeed();
	int AmountOfCar();
	int AmountOfTruck();
	int AmountOfDinasour();
	int AmounrOfBird();
};


class FileSave {
private:
	string name;
	int level;
public:
	FileSave(int,string);
	int getLevel();
	string getName();
};


class CGAME {
	CVEHICLE* axt[10];
	CVEHICLE* axh[10];
	CANIMAL* akl[10];
	CANIMAL* ac[10];
	CPEOPLE *cn;
	Level *lv[10]; int presentLevel;
	int Finish;
	FileSave *File[10];
	int numberOfSave;
public:
	CGAME(); //Chuẩn bị dữ liệu cho tất cả các đối tượng
	void drawGame(); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	~CGAME(); // Hủy tài nguyên đã cấp phát
	CPEOPLE* getPeople();//Lấy thông tin người
	CVEHICLE* getVehicle();//Lấy danh sách các xe
	CANIMAL* getAnimal(); //Lấy danh sách các thú
	bool IsImpact();
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(HANDLE); // Thực hiện thoát Thread
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	void loadGame(); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(HANDLE); // Tạm dừng Thread
	void resumeGame(HANDLE); //Quay lai Thread
	void updatePosPeople(char,int&); //Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); //Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal();//Thực hiện cho CDINAUSOR & CBIRD di chuyển
	void UpdateLevel();
	void LoadLevel(int);
	void ScoreBoard(bool); //or gameOverScence
	void Clean();
	bool IsFinish();
	void Update();
	void DrawLight(bool);
	int getSpeed() { return lv[presentLevel - 1]->getSpeed(); }
};

void clrscr();

void FixConsoleWindow();
void GotoXY(int x, int y);
int Menu();
void hidecursor();
void LoadingBar();
//void SetColor(int ForgC);
class Light {
public:
	void DrawRed(int x, int y);
	void DrawGreen(int x, int y);
};