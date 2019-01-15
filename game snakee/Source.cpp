#include <iostream>
#include <Windows.h>
#include <curses.h>
#include <string>
#include <ctime>

using namespace std;

const int height = 20, width = 40;
int x = width / 2, y = height / 2, ans = 0;
bool dar_hal_ejra = true;
int jahat = 3, fx, fy, score = 0, num;
void gotoxy(int a, int b){
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != hConsole)
	{
		pos.X = a;
		pos.Y = b;
		SetConsoleCursorPosition(hConsole, pos);
	}
}

void makhfi()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void zamin(){
	for (int j = 0; j<height; ++j)
		cout << string(width, '-') << endl;
}
void ghaza() {
	fx = clock() % (width - 2) + 1;
	fy = clock() % (height - 2) + 1;
	gotoxy(fx, fy);
	cout << "$";
}
void payam() {
	cout << string(33, '-') << endl;
	cout << "-\tYou Lost!!!\t\t-" << endl;
	cout << "-\tYour Score = " << score << "\t\t-" << endl;
	cout << string(33, '-') << endl;
}
void payam1() {
	cout << "\t1 to exit\n\t0 to new game" << endl;
	cin >> ans;
	while (!(ans == 0 || ans == 1))
		cin >> ans;
	if (ans == 0) {
		dar_hal_ejra = true;
		x = (width / 2);	
		y = (height / 2);	
		system("cls");
		score = 0;
	}
}
void jabejaei(int dx, int dy) {
	x = x + dx;
	y = y + dy;
	if (x == fx && y == fy) {
		score += 10;
		ghaza();
	}
	if (x == 0 || x == (width - 1) || y == 0 || y == (height - 1)) {
		dar_hal_ejra = false;
	}
	system("cls");
	zamin();
	gotoxy(fx, fy);
	cout << "$";
	gotoxy(x, y);
	cout << char(254);
}
void taghir_jahat() {
	switch (jahat){
	case 0: jabejaei(0, -1);
		break;
	case 1: jabejaei(1, 0);
		break;
	case 2: jabejaei(0, 1);
		break;
	case 3: jabejaei(-1, 0);
		break;
	}
}
void start() {
	while (dar_hal_ejra) {
		if (_kbhit()) {
			switch (_getch()) {
			case 80:
				if (jahat != 0) jahat = 2;
				break;
			case 75:
				if (jahat != 1) jahat = 3;
				break;
			case 72:
				if (jahat != 2) jahat = 0;
				break;
			case 77:
				if (jahat != 3) jahat = 1;
				break;
			}
		}
		taghir_jahat();
		Sleep(120);
	}
}
int main(){

	makhfi();
	do{
		zamin();
		ghaza();
		gotoxy(x, y);
		cout << char(254);
		start();
		system("cls");
		payam();
		payam1();
	} while (ans == 0);
	return 0;
}