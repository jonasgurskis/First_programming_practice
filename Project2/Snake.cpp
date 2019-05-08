#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <WinUser.h>


using namespace std;

//snake variables 
bool gameover;
const int width = 40;
const int height = 20;
int nTail;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int prev3X, prev3Y, prev2X, prev2Y, prev4X, prev4Y;
int ratas = 0;
int stored_items = 2;
int difficulty;
bool first_loop = false;
bool first_loop2 = false;

//menu variables
void menu();
void mainMenu();
void optionsMenu();
void options();
void store(char);
void inventory(char );
int choice1 = 0;
int choice2 = 3;
int choice3 = 4;
char item = 'o';
char str[] = "(locked)";
char color[10];

enum eDirections { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirections dir;
void gotoxy(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setup();
void logic(char, int);
void map_draw();
void default_snake_draw();
void fruit_generation();
void moving_snake_draw(char);
void eat_fruit();
void start_game();
int main() {
	menu();
	
	return 0;
}

void setup() {
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	score = 0;
	map_draw();
	default_snake_draw();
	fruit_generation();

};
void logic(char ch, int difficulty) {	 
			switch (ch)
			{
			case 'a':
				while (1) 
				{	
					eat_fruit();
					moving_snake_draw(item);
					x--;				
					Sleep(difficulty);
					if (_kbhit()) {
						ch = _getch();
						if (ch == 's' || ch == 'd' || ch == 'w' || ch == 'q') {
							logic(ch, difficulty);
						}
						FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
					}
				}
				break;
			case 'd':
				while (1)
				{
					eat_fruit();
					moving_snake_draw(item);
					x++;					
					Sleep(difficulty);
					if (_kbhit()) {
						ch = _getch();
						if (ch == 'a' || ch == 's' || ch == 'w' || ch == 'q') {
							logic(ch, difficulty);
						}
					}
				}
				break;
			case 'w':
				while (1) 
				{
					eat_fruit();
					moving_snake_draw(item);
					y--;					
					Sleep(difficulty);
					if (_kbhit()) {
						ch = _getch();
						if (ch == 'a' || ch == 'd' || ch == 's' || ch == 'q') {
							logic(ch, difficulty);
						}
					}
				}
				break;
			case 's':
				while(1)
				 {
					eat_fruit();
					moving_snake_draw(item);
					y++;									
					Sleep(difficulty);
					if (_kbhit()) {
						ch = _getch();
						if (ch == 'a' || ch == 'd' || ch == 'w' || ch == 'q') {
							logic(ch, difficulty);
						}
					}
				}
				break;
			case 'q':
				gameover = true;
				system("CLS");
				menu();
				break;
			default:
				break;
			}



	//if (x > width || x < 0 || y > height || y < 0 ) {
	//	gameover = true;
	//}
	//for (int i = 0; i < nTail; i++) {
	//	if (tailX[i] == x && tailY[i] == y)
	//		gameover = true;
	//}

};
void map_draw() {
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 1; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "#";
			}
			else if (j == width - 1) {
				gotoxy(j + 2, i);
				cout << "#";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
}
void default_snake_draw() {
	gotoxy(x, y);
	cout << "@";
}
void fruit_generation() {
	fruitx = rand() % width;
	fruity = (rand() % height) + 1;
	gotoxy(fruitx, fruity);
	cout << "F";
}
void moving_snake_draw(char item) {
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;

	gotoxy(x, y);
	cout << "@";

	if (nTail == 0) {
		if (prevX != 0) {
		gotoxy(prevX, prevY);
		cout << " ";
	}
		prev2X = prevX;
		prev2Y = prevY;
	}
	else if (nTail == 1) {
		if (ratas > 0) {
			gotoxy(prev2X, prev2Y);
			cout << " ";
		}
		gotoxy(prevX, prevY);
		cout << item;
		Sleep(20);
		prev2X = prevX;
		prev2Y = prevY;
		ratas++;
	}
	else {
		if (ratas > 0) {
			gotoxy(prev2X, prev2Y);
			cout << " ";
		}
		ratas++;
		gotoxy(prev4X, prev4Y);
		prev4X = prev3X;
		prev4Y = prev3Y;
		cout << " ";
		for (int i = 1; i < nTail; i++) {
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
			for (int k = 1; k < nTail; k++) {
				gotoxy(tailX[k], tailY[k]);
				cout << item;
				prev3X = tailX[k];
				prev3Y = tailY[k];
				
				}
		}

	}
void eat_fruit() {
	if (x == fruitx && y == fruity) {
		score = score + 50;
		fruit_generation();
		nTail++;
		gotoxy(0, 25);
		cout << "tails: " << nTail;
	}
}
void menu() {
	
	do {
		choice2 = 0;
		mainMenu();

		switch (choice1) {

		case 1:
			start_game();
			break;
		case 2:
			store(item);
			break;
		case 3:
			options();
			break;
		case 4:
			inventory(item);
		case 5:
			break;

		}

	} while (choice1 != 5);


}
void options(void) {
	system("CLS");
	do {
		optionsMenu();

		switch (choice2) {

		case 1:
			cout << "1 - Very Hard!\n";
			cout << "2 - Hard!\n";
			cout << "3 - Medium!\n";
			cout << "4 - Easy!\n";
			cin >> choice3;
			break;

		case 2:
			cout << "Beep!\n";
			break;

		case 3:
			break;

		default:
			break;

		}

	} while (choice2 != 3);


}
void mainMenu(void) {


	system("CLS");
	cout << "Main Menu\n";
	cout << "1 - Start game\n";
	cout << "2 - Store\n";
	cout << "3 - Options\n";
	cout << "4 - Inventory\n";
	cout << "5 - Quit\n";
	cout << "Please choose: ";
	cin >> choice1;

}
void optionsMenu(void) {


	system("CLS");
	cout << "Options Menu\n";
	cout << "1 - Difficulty\n";
	cout << "2 - Sound\n";
	cout << "3 - Back\n";
	cout << "Please choose: ";
	cin >> choice2;

}
void start_game() {
	system("CLS");
	switch (choice3) {
	case 1:
		difficulty = 50;
		break;
	case 2:
		difficulty = 100;
		break;
	case 3:
		difficulty = 150;
		break;
	case 4:
		difficulty = 200;
		break;
	}
	switch (item) {
	case '1': 
		item = 'G';
		break;
	case '2':
		item = 'R';
		break;
	case '3':
		item = 'B';
		break;
	case '4':
		item = 'Y';
		break;
	case '5':
		item = 'P';
		break;
	default:
		item = 'o';
		break;
	}
	setup();
	gotoxy(0, 28);
	cout << difficulty;
	gotoxy(0, 29);
	cout << item;
	char ch = _getch();

	while (gameover == false) {
		logic(ch, difficulty);
	}
	gotoxy(0, 25);
	cout << "GAME OVER!";
}
void store(char) {
	cout << "Choose item of your snake: \n";
	cout << "1 - Green " << str << "\n";
	cout << "2 - Red " << str << "\n";
	cout << "3 - Blue " << str << "\n";
	cout << "4 - Yellow " << str << "\n";
	cout << "5 - Purple " << str << "\n";
	cout << "6 - Back";
	cin >> item;
	
}
void inventory(char) {
	system("CLS");
	do {
		for (int i = 0; i < stored_items; i++) {
			switch (i) {
			case 0:
				cout << "1 - choose a regular color\n";
				break;
			case 1:
				cout << "2 - choose a numbered color\n";
				break;
			case 2:
				cout << "3 - choose a green color\n";
				break;
			case 3:
				cout << "4 - choose a red color\n";
				break;
			case 4:
				cout << "5 - choose a blue color\n";
				break;
			case 5:
				cout << "6 - choose a yellow color\n";
				break;
			case 6:
				cout << "7 - choose a purple color\n";
				break;
			}
			if (i == stored_items - 1)
				cout << stored_items+1 << " - Back";
		}
		cout << "Please choose: ";
		cin >> item;
		switch (item) {
		case '1':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		case '2':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		case '3':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		case '4':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		case '5':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		case '6':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		case '7':
			gotoxy(30, 0);
			cout << "(chosen)";
			break;
		}
	} while (item != stored_items + 1);
	
	system("pause");
}