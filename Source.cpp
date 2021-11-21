#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;
bool gameOver, test, stop;
int heigst, wights, frutx, fruty, playerx, playery, score, c;
string dir;
vector <vector <int> > body;
void setup() {
    srand(time(NULL));
    heigst = 20;
    wights = 20;
    gameOver = false;
    stop = false;
    test = true;
    frutx = 1 + rand() % 17;
    fruty = 1 + rand() % 17;
    playerx = 10;
    playery = 10;
    score = 0;
    dir = "up";
    body = { {playerx, playery}, {playerx, playery-1} };
    system("mode con: cols=35 lines=20 && title Snake Game!");
}
void update() {
    system("cls");
    for (int j = 0; j < wights+1; j++) {
        cout << "#";
    }
    cout << "  Score: " << score << endl;
    for (int i = 1; i < heigst - 2; i++) {
        cout << "#";
        for (int j = 1; j < wights; j++) {
            int c = 0;
            for (int k = 1; k < body.size(); k++)
                if (body[k][0] == i && body[k][1] == j) { cout << "o"; c = 1; }
            if (c == 0) {
                if (playery == i && playerx == j) { cout << "x"; }
                else if (fruty == i && frutx == j) { cout << "@"; }
                else { cout << " "; }
            }
        }
        if (i == 2) cout << "#  x - Snake" << endl;
        else if (i == 3) cout << "#  o - Body" << endl;
        else if (i == 4) cout << "#  # - Border" << endl;
        else if (i == 6) cout << "#  wasd - Mana-" << endl;
        else if (i == 7) cout << "#  gement" << endl;
        else if (i == 9) cout << "#  q - quit" << endl;
        else cout << "#" << endl;
    }
    for (int j = 0; j < wights+1; j++) {
        cout << "#";
    }
}
void input() {
    if (_kbhit()){
        switch (_getch()) {
            case 'w': dir = "up"; break;
            case 's': dir = "down"; break;
            case 'a': dir = "left"; break;
            case 'd': dir = "right"; break;
            case 'q': stop = true; gameOver = true;  break;
        }
    }
}
void logic() {
    if (playerx == 0 || playerx == heigst || playery == 0 || playery == wights-2)
        gameOver = true;  
    if (playerx == frutx && playery == fruty) {
        test = true;
        int x = body[body.size() - 1][0] - 1;
        int y = body[body.size() - 1][1] - 1;
        body.push_back({ x, y });
        score += 1;
        while (test) {
            int b = 0;
            frutx = 1 + rand() % 17;
            fruty = 1 + rand() % 17;
            for (int i = body.size() - 1; i >= 0; i--) {
                if (body[i][0] == frutx || body[i][1] == fruty) {
                    b += 1;
                }
            }
            if (b == 0) { test = false; }
        }
    }
    if (dir == "up") playery -= 1;
    else if (dir == "down") playery += 1;
    else if (dir == "left") playerx -= 1;
    else if (dir == "right") playerx += 1;
    for (int i = body.size() - 1; i > 0; i--) {
        body[i][0] = body[i - 1][0];
        body[i][1] = body[i - 1][1];
    }
    body[0] = { playery, playerx };
    for (int i = body.size() - 1; i > 0; i--) {
        if (body[i][0] == playery && body[i][1] == playerx)
            gameOver = true;
    }
}
void menu() {
    cout << "Snake Game" << endl << endl << "Press any key to start";
    system("pause > nul");
}
int main() {
    setup();
    while (!stop) {
        setup();
        menu();
        while (!gameOver) {
            update();
            input();
            logic();
            Sleep(80);
        }
    }
    return 0;
}
