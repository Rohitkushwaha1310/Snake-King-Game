#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;

bool gameover;
const int height = 20, width = 20;
int headx, heady, fruitx, fruity, score, tail_len;
int tailx[100], taily[100];

void setCursor(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setup() {
    srand(time(0));
    gameover = false;
    dir = STOP;
    headx = width / 2;
    heady = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
    tail_len = 0;

    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void draw() {
    setCursor(0, 0);

    cout << "\t\t";
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        cout << "\t\t";
        for (int j = 0; j < width; j++) {

            if (j == 0)
                cout << "#";

            if (i == heady && j == headx)
                cout << "O";
            else if (i == fruity && j == fruitx)
                cout << "*";
            else {
                bool print = false;
                for (int k = 0; k < tail_len; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        cout << "o";
                        print = true;
                        break;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    cout << "\t\t";
    for (int i = 0; i < width; i++)
        cout << "#";

    cout << "\t\tScore: " << score << endl;
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 'a':
        case 'A':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
        case 'D':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
        case 'W':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
        case 'S':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameover = true;
            break;
        }
    }
}

void logic() {
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;

    tailx[0] = headx;
    taily[0] = heady;

    for (int i = 1; i < tail_len; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch (dir) {
    case LEFT:
        headx--;
        break;
    case RIGHT:
        headx++;
        break;
    case UP:
        heady--;
        break;
    case DOWN:
        heady++;
        break;
    default:
        break;
    }

    if (headx >= width) headx = 0;
    else if (headx < 0) headx = width - 1;

    if (heady >= height) heady = 0;
    else if (heady < 0) heady = height - 1;

    for (int i = 0; i < tail_len; i++) {
        if (tailx[i] == headx && taily[i] == heady)
            gameover = true;
    }

    if (headx == fruitx && heady == fruity) {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        tail_len++;
    }
}

int main() {
    char start;
    cout << "\t------------------------" << endl;
    cout << "\t\t : Snake King :" << endl;
    cout << "\t------------------------" << endl;
    cout << "\tPress 's' to start: ";
    cin >> start;

    if (start == 's' || start == 'S') {
        setup();
        while (!gameover) {
            draw();
            input();
            logic();
            Sleep(120);
        }
        cout << "\n\t\tGame Over! Final Score: " << score << endl;
    }

    return 0;
}
