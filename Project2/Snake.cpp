#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <WinUser.h>
using namespace std;
bool gameover;
int width = 40;
int height = 20;
int nTail = 1;
int value = 1;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int prev3X, prev3Y, prev2X, prev2Y, prev4X, prev4Y;
int ratas = 0;
int ratas2 = 0;
int glob_val = 0;
int stored_items = 2;
int kintamasis = 1;
int difficulty;
int prev_stored_items = 0;
bool first_loop = false;
bool first_loop2 = false;
bool no_walls = true;
void menu();
void mainMenu();
void optionsMenu();
void options();
void store();
void inventory(char );
int choice1 = 0;
int choice2 = 3;
int choice3 = 4;
int choice4 = 0;
char item = 'o';
char str[] = "(locked)";
char bought[] = "(already bought)";
char bought_items[5];
enum eDirections { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirections dir;
void gotoxy(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setup();
void logic(char, int);
void map_draw();
void default_snake_draw(char);
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
	default_snake_draw(item);
	fruit_generation();

};
void logic(char ch, int difficulty) {	 
	do {
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
					if (ch == 's' || ch == 'w' || ch == 'q') {
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
					if (ch == 's' || ch == 'w' || ch == 'q') {
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
					if (ch == 'a' || ch == 'd'|| ch == 'q') {
						logic(ch, difficulty);
					}
				}
			}
			break;
		case 's':
			while (1)
			{
				eat_fruit();
				moving_snake_draw(item);
				y++;
				Sleep(difficulty);
				if (_kbhit()) {
					ch = _getch();
					if (ch == 'a' || ch == 'd'|| ch == 'q') {
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
	} while (gameover != true);




};
void map_draw() {
	width = (rand() % 120) + 10;
	height = (rand() % 25) + 5;

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
void default_snake_draw(char item) {
	gotoxy(x, y);
	cout << "@";
	gotoxy(x - 1, y);
	cout << item;
}
void fruit_generation() {
	fruitx = rand() % width;
	fruity = (rand() % height) + 1;
	gotoxy(fruitx, fruity);
	cout << "F";
}
void moving_snake_draw(char item) {

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gotoxy(20, 20);
			cout << "GAME OVER!!";
			exit(1);
		}
	}
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
		if (ratas == 0) {
			prevX = x - 1;
			prevY = y;
		}
		if (ratas != 0) {
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
		if (ratas2 == 0) {
			gotoxy(prev2X, prev2Y);
			cout << " ";
			prev4X = prev3X;
			prev4Y = prev3Y;
		}
		if (ratas2 > 0) {
		gotoxy(prev4X, prev4Y);
		prev4X = prev3X;
		prev4Y = prev3Y;
		cout << " ";
		}
		ratas2++;
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
	
	if (no_walls == true) {
	if (x > width - 1) {
		x = 1;
	}
	else if (x == 1) {
		x = width - 1;
	}
	else if (y == height) {
		y = 1;
	}
	else if (y == 0) {
		y = height;
	}
	}
	else {
		if (x > width || x < 0 || y > height || y < 0) {
		gotoxy(20, 20);
		cout << "GAME OVER!!";
		exit(1);
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
			store();
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
			system("CLS");
			cout << "1 - Very Hard!\n";
			cout << "2 - Hard!\n";
			cout << "3 - Medium!\n";
			cout << "4 - Easy!\n";
			cin >> choice3;
			break;

		case 2:
			
			do {
				system("CLS");
				cout << "1 - No walls! ";
				if (no_walls == false) {
					cout << "                  ";
					gotoxy(20, 0);
					cout << "(off)\n";
				}
				else {
					cout << "                  ";
					gotoxy(20, 0);
					cout << "(on)\n";
				}
				cout << "2 - Back\n";
				cout << "Please choose: ";
				cin >> choice4;
				if (choice4 == 1 && no_walls == false) {
					no_walls = true;
				}
				else if (choice4 == 1 && no_walls == true) {
					no_walls = false;
				}
			} while (choice4 != 2);
		
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
	cout << "2 - Game mode\n";
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
	setup();
	char ch = _getch();
	while (gameover == false) {
		logic(ch, difficulty);
	}
	gotoxy(0, 25);
	cout << "GAME OVER!";
}
void store() {
	system("CLS");
	int value;
		cout << "Buy a new color for your snake: \n";
		cout << "1 - Green color \n";
		cout << "2 - Red color \n";
		cout << "3 - Blue color \n";
		cout << "4 - Yellow color \n";
		cout << "5 - Purple color \n";
		cout << "6 - Back\n";
		cout << "Please choose: ";

		for (int i = 1; i <= 5; i++) {
			if (bought_items[i-1] != 't') {
				gotoxy(20, i);
				cout << str << endl;
			}
			else {
				gotoxy(20, i);
				cout << bought << endl;
			}
		}
		do {
		gotoxy(15, 7);
		cin >> value;
		value = value - 1;
		switch (value) {
		case 0:
			gotoxy(20, value+1);
			cout << bought;
			bought_items[value] = 't';
			stored_items++;
			break;
		case 1:
			gotoxy(20, value+1);
			cout << bought;
			bought_items[value] = 't';
			stored_items++;
			break;
		case 2:
			gotoxy(20, value+1);
			cout << bought;
			bought_items[value] = 't';
			stored_items++;
			break;
		case 3:
			gotoxy(20, value+1);
			cout << bought;
			bought_items[value] = 't';
			stored_items++;
			break;
		case 4:
			gotoxy(20, value+1);
			cout << bought;
			bought_items[value] = 't';
			stored_items++;
			break;
		case 5:
			menu();
			break;
		}
		} while (value != 6);
	
	}
void inventory(char) {
	system("CLS");
	char printed[4];
	int x = 0;
	int prev_value;
	for (int i = 0; i < stored_items; i++) {
		switch (i) {
		case 0:
			cout << i + 1 << " - choose a regular color\n";
			break;
		case 1:
			cout << i + 1 << " - choose a numbered color\n";
			break;
		case 2:
			if (bought_items[i-2] == 't' && printed[i-2] != 't') {
				cout << i + 1 << " - choose a green color\n";
				printed[i-2] = 't';
				break;
			}
			else { i++; }
		case 3:
			if (bought_items[i-2] == 't' && printed[i-2] != 't') {
				if (stored_items == 7) {
					cout << stored_items - 3;
				}
				else if (stored_items == 6) {
					if (bought_items[i - 3] == 't') {
						cout << stored_items - 2;
					}
					else {
						cout << stored_items - 3;
					}
				}
				else if (stored_items == 5) {
					if (bought_items[i-3] == 't') {
						cout << stored_items - 1;
					}
					else {
						cout << stored_items -2;
					}
				}
				else if (stored_items == 4) {
					if (bought_items[i - 3] == 't') {
						cout << stored_items ;
					}
					else {
						cout << stored_items-1;
					}
				}
				else {
					cout << stored_items;
				}
				cout << " - choose a red color\n";
				printed[i-2] = 't';
				i = 2;
				break;
			}
			else { i++; }
		case 4:
				if (bought_items[i-2] == 't' && printed[i-2] != 't') {

					if (stored_items == 7) {
						cout << stored_items - 2;
					}
					else if (stored_items == 6) {
						cout << stored_items - 1;
					}
					else if (stored_items == 5) {
						if (bought_items[i] == 't' && bought_items[i-1] == 't') {
							cout << stored_items - 2;
						}
						else if (bought_items[i] == 't' || bought_items[i-1] == 't') {
							cout << stored_items - 1;
						}
						else {
							cout << stored_items;
						}
					}
					else if (stored_items == 4) {
						if (bought_items[i] == 't' || bought_items[i-1] == 't') {
							cout << stored_items - 1;
						}
						else {
							cout << stored_items;
						}
					}
					else {
						cout << stored_items;
					}
					cout << " - choose a blue color\n";
					printed[i-2] = 't';
					i = 2;
					break;
				}
				else { i++; }
		case 5:

			if (bought_items[i-2] == 't' && printed[i-2] != 't') {
				if (stored_items == 7) {
					cout << stored_items - 1;
				}
				else if (stored_items == 6) {
					if (bought_items[i-1] != 't') {
						cout << stored_items;
					}
					else {
						cout << stored_items - 1;
					}
				}
				else if (stored_items == 5) {
					if (bought_items[i-1] == 't') {
						cout << stored_items - 1;
					}
					else {
						cout << stored_items;
					}
				}
				else if (stored_items == 4) {
					if (bought_items[i-1] == 't') {
						cout << stored_items - 1;
					}
					else {
						cout << stored_items;
					}
				}
				else {
					cout << stored_items;
				}
				cout << " - choose a yellow color\n";
				printed[i-2] = 't';
				i = 2;
				break;
			}
			else { i++; }
		case 6:
			if (bought_items[i-2] == 't' && printed[i-2] != 't') {
				for (int i = 3; i <= 7; i++) {
					if (stored_items == i) {
						cout << stored_items;
					}
				}
				cout << " - choose a purple color\n";
				printed[i-2] = 't';
				break;
			}
			else { i++; };
			}
		}
		cout << stored_items + 1 << " - Back\n";
		cout << "Please choose: ";

		do {

			prev_value = value;
			
			if (prev_stored_items < stored_items && prev_stored_items != 0) {
				int i = stored_items - prev_stored_items;
				first_loop = true;
				switch (i) {
				case 1:
					if (item == 'R') {
						if (bought_items[0] == 't') {
							gotoxy(30, value - 1);
							cout << "          ";
						}
					}
					else if (item == 'B') {
						if (bought_items[0] == 't' || bought_items[1] == 't') {
							gotoxy(30, value - 1);
							cout << "           ";
						}
					}
					else if (item == 'Y') {
						if (bought_items[0] == 't' || bought_items[1] == 't' || bought_items[2] == 't') {
							gotoxy(30, value - 1);
							cout << "           ";
						}
					}
					else if (item == 'P') {
						if (bought_items[0] == 't' || bought_items[1] == 't' || bought_items[2] == 't' || bought_items[3] == 't') {
							gotoxy(30, value - 1);
							cout << "           ";
						}
					}
					break;
				case 2:
					if (item == 'R') {
						if (bought_items[0] == 't') {
							gotoxy(30, value - 1);
							cout << "          ";
						}
					}
					else if (item == 'B') {
						if (bought_items[0] == 't' && bought_items[1] == 't') {
							gotoxy(30, value-2);
							cout << "           ";
						}
						else if (bought_items[0] == 't' || bought_items[1] == 't') {
							gotoxy(30, value - 1);
							cout << "           ";
						}
					}
					else if (item == 'Y') {
						if ((bought_items[0] == 't' && bought_items[1] == 't') || (bought_items[0] == 't' && bought_items[2] == 't') || (bought_items[1] == 't' && bought_items[2] == 't')) {
							gotoxy(30, value - 2);
							cout << "           ";
						}
						else if (bought_items[0] == 't' || bought_items[1] == 't' || bought_items[2] == 't') {
							gotoxy(30, value - 1);
							cout << "           ";
						}
					}
					else if (item == 'P') {
							gotoxy(30, value - 2);
							cout << "           ";
					}
					break;
				}
			}
			else {
				first_loop = false;
			}
			if (first_loop == false) {
				switch (value) {
				case 1:
					gotoxy(30, 0);
					cout << "(chosen)";
					item = 'o';
					value = 1;
					break;
				case 2:
					gotoxy(30, 1);
					cout << "(chosen)";
					item = '5';
					value = 2;
					break;
				case 3:
					if (stored_items >= value) {
						gotoxy(30, 2);
						cout << "(chosen)";
						value = 3;
						int i = 0;
						if (bought_items[i] == 't') {
							item = 'G';
						}
						else if (bought_items[i + 1] == 't') {
							item = 'R';
						}
						else if (bought_items[i + 2] == 't') {
							item = 'B';
						}
						else if (bought_items[i + 3] == 't') {
							item = 'Y';
						}
						else
						{
							item = 'P';
						}
					}
					break;
				case 4:
					if (stored_items >= value) {
						gotoxy(30, 3);
						cout << "(chosen)";
						value = 4;
						int i = 1;
						if (bought_items[i] == 't') {
							item = 'R';
						}
						else if (bought_items[i + 1] == 't') {
							item = 'B';
						}
						else if (bought_items[i + 2] == 't') {
							item = 'Y';
						}
						else
						{
							item = 'P';
						}
					}
					break;
				case 5:
					if (stored_items >= value) {
						gotoxy(30, 4);
						cout << "(chosen)";
						value = 5;
						int i = 2;
						if (bought_items[i] == 't') {
							item = 'B';
						}
						else if (bought_items[i + 1] == 't') {
							item = 'Y';
						}
						else
						{
							item = 'P';
						}

					}
					break;
				case 6:
					if (stored_items >= value) {
						gotoxy(30, 5);
						cout << "(chosen)";
						value = 6;
						int i = 3;
						if (bought_items[i] == 't') {
							item = 'Y';
						}
						else
						{
							item = 'P';
						}

					}
					break;
				case 7:
					if (stored_items >= value) {
						gotoxy(30, 6);
						cout << "(chosen)";
						value = 7;
						item = 'P';
					}
					break;
				}
			}
			gotoxy(15, stored_items + 1);
			cin >> value;
			if (value != prev_value && stored_items >= value && value != stored_items + 1) {
				gotoxy(30, prev_value - 1);
				cout << "           ";
			}
		prev_stored_items = stored_items;
		} while (value != stored_items + 1);
		if (value == stored_items + 1) {
			value = prev_value;
		}
		
		menu();
		system("pause");
	}
