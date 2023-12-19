#include <iostream>
#include <Windows.h>
#include "Dos.cpp"
#include "Folder.cpp"

using namespace std;

// void printName();
// void gotoxy(int x, int y);

int main()
{
    Dos d;
    printName();
    while (d.takeInput())
    {
        // to take the input until true
    }
}
// void printName()
// {
//     system("cls");
//     gotoxy(40, 0);
//     cout << "M Soban Akram || 2022-CS-173 || BSc. Computer Science" << endl << endl << endl;
// }
// void gotoxy(int x, int y)
// {
//     COORD cordinates;
//     cordinates.X = x;
//     cordinates.Y = y;
//     HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleCursorPosition(hOutput, cordinates);
// }
