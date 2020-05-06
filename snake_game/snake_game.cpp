#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

const int dx[4] = { 0, -1, 0, 1 };
const int dy[4] = { -1, 0, 1, 0 };

enum DIRECTION
{
	LEFT = 0,
	UP,
	RIGHT,
	DOWN
};

struct Point
{
	int x;
	int y;
	Point() {
		setPoint(0, 0);
	}
	Point(int x, int y) {
		setPoint(x, y);
	}
	void setPoint(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void update(DIRECTION direct) {
		this->x += dx[direct];
		this->y += dy[direct];
	}
	bool checkOutBoard() {
		return (0 == this->x || HEIGHT - 1 == this->x || 0 == this->y || WIDTH - 1 == this->y);
	}
};

int board[HEIGHT][WIDTH];
DIRECTION g_direct;
Point g_head;
int g_score;

void create_food() {
	while (true) {
		Point food((rand() % (HEIGHT - 2) + 1), (rand() % (WIDTH - 2) + 1));
		if (board[food.x][food.y] == 0) {
			board[food.x][food.y] = -2;
			break;
		}
		
	}
}

void init_game() {
	
	g_direct = RIGHT;
	g_head.setPoint(1, 3);
	g_score = 3;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
				board[i][j] = -1;
			else
				board[i][j] = 0;
		}
	}
	for (int i = 1; i < 4; i++)
		board[1][i] = i;

	create_food();
}


void update_board() {
	g_head.update(g_direct);
	if (board[g_head.x][g_head.y] == -2) {
		board[g_head.x][g_head.y] = ++g_score;
		create_food();
		return;
	}
	
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			board[i][j] = board[i][j] > 0 ? board[i][j] - 1 : board[i][j];
	board[g_head.x][g_head.y] = g_score;
	
}

void show_board()
{
	system("CLS");
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (-1 == board[i][j])
				printf("x");
			else if (0 == board[i][j])
				printf(" ");
			else if (-2 == board[i][j])
				printf("1");
			else
				printf("o");
		}
		printf("\n");
	}
}

int snake_game()
{
	char pressed_key;
PLAY_AGAIN:
	init_game();
	show_board();

	while (true)
	{
		update_board();
		show_board();
		if (g_head.checkOutBoard())
			break;

		if (_kbhit()) {
			pressed_key = _getch();
			//printf("pressed_key %d \n", pressed_key);
			switch (pressed_key)
			{
			case 27:
				break;
			case 97:
				g_direct = LEFT;
				break;
			case 119:
				g_direct = UP;
				break;
			case 100:
				g_direct = RIGHT;
				break;
			case 115:
				g_direct = DOWN;
				break;
			}
		}
		
		Sleep(50);
	}
	printf("\nYour score is %d\n\n", g_score);
	printf("\nDo you want to play again? (y/n) ");
	fflush(stdin);
	scanf("%c",&pressed_key);
	if (pressed_key == 'y')
		goto PLAY_AGAIN;
	fflush(stdin);
	
	return 0;
}