#include <iostream>
#include <list>
#include <conio.h>
// #include "Dos.cpp"
#include <Windows.h>
#include <stack>
#include <deque>
#pragma once
using namespace std;
struct state
{
    list<list<char>> text;
    list<list<char>>::iterator ritr;
    list<char>::iterator citr;
    int currentRow, currentCol;
};
class currentFile
{
    friend class File;
    friend class Dos;

private:
    list<list<char>> text;
    list<list<char>>::iterator ritr;
    list<char>::iterator citr;
    int currentRow, currentCol;
    string name;
    int size;
    deque<state> redo;
    deque<state> undo;

public:
    currentFile(string name = "")
    {
        this->currentCol = 0;
        this->currentRow = 0;
        this->size = 0;
        this->name = name;
        text.push_back(list<char>());
        ritr = text.begin();
        (*ritr).push_back(' ');
        citr = (*ritr).begin();
    }
    void showText()
    {
        list<list<char>>::iterator row;
        for (row = text.begin(); row != text.end(); row++)
        {
            list<char>::iterator col;
            for (col = (*row).begin(); col != (*row).end(); col++)
            {
                cout << *col;
            }
            cout << endl;
        }
    }
    // void edit()
    // {
    //     gotoxy(0, 0);
    //     if (size > 0)
    //     {
    //         openSaveFile();
    //     }
    //     gotoxy(currentRow, currentCol);
    //     while (true)
    //     {
    //         char ch = _getch();
    //         if (GetAsyncKeyState(VK_LEFT))
    //         {
    //             if (currentCol > 0)
    //             {
    //                 currentCol--;
    //                 gotoxy(currentRow, currentCol);
    //             }
    //         }
    //         else if (GetAsyncKeyState(VK_RIGHT))
    //         {
    //             if (currentCol < ritr->size())
    //             {

    //                 currentCol++;
    //                 gotoxy(currentRow, currentCol);
    //             }
    //         }
    //         else if (GetAsyncKeyState(VK_UP))
    //         {
    //             if (currentRow > 0)
    //             {
    //                 currentRow--;
    //                 gotoxy(currentRow, currentCol);
    //             }
    //         }
    //         else if (GetAsyncKeyState(VK_DOWN))
    //         {
    //             if (currentRow < text.size() - 1)
    //             {
    //                 currentRow++;
    //                 gotoxy(currentRow, currentCol);
    //             }
    //         }
    //         else if (GetAsyncKeyState(VK_BACK))
    //         {
    //             // delete word
    //         }
    //         else if (ch == '0')
    //         {
    //             return;
    //         }
    //         else
    //         {
    //             size++;
    //             if (currentCol < ritr->size() - 1)
    //             {
    //                 auto r = text.begin();
    //                 advance(r, currentRow);
    //                 auto c = r->begin();
    //                 advance(c, currentCol);
    //                 r->insert(c, ch);
    //                 currentCol++;
    //                 system("cls");
    //                 openSaveFile();
    //                 gotoxy(currentRow, currentCol);
    //             }
    //             else
    //             {
    //                 ritr->push_back(ch);
    //                 currentCol++;
    //                 citr++;
    //                 cout << *citr;
    //             }
    //         }
    //     }
    // }
    void edit()
    {
        gotoxy(0, 0);
        if (size > 0)
        {
            showText();
        }
        gotoxy(currentRow, currentCol);
        while (true)
        {
            char ch = _getch();
            if (GetAsyncKeyState(VK_LEFT))
            {
                if (currentCol > 0)
                {
                    currentCol--;
                    citr--;
                    gotoxy(currentRow, currentCol);
                }
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                if (currentCol < ritr->size())
                {

                    currentCol++;
                    citr++;
                    gotoxy(currentRow, currentCol);
                }
            }
            else if (GetAsyncKeyState(VK_UP))
            {
                if (currentRow > 0)
                {
                    currentRow--;
                    ritr--;
                    gotoxy(currentRow, currentCol);
                }
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
                if (currentRow < text.size() - 1)
                {
                    currentRow++;
                    ritr++;
                    gotoxy(currentRow, currentCol);
                }
            }
            else if (GetAsyncKeyState(VK_CONTROL) && (GetAsyncKeyState('Z')))
            {
                pushInRedo();
                undoOneStep();
                system("cls");
                showText();
                gotoxy(currentRow, currentCol);
            }
            else if (GetAsyncKeyState(VK_CONTROL) && (GetAsyncKeyState('Y')))
            {
                pushInUndo();
                redoOneStep();
                system("cls");
                showText();
                gotoxy(currentRow, currentCol);
            }
            else if (ch == 8) // backspace key
            {
                // delete word
                if (currentCol > 0 && citr != ritr->begin())
                {
                    auto c = citr;
                    pushInUndo();
                    citr--;
                    ritr->erase(c);
                    currentCol--;
                    system("cls");
                    showText();
                    gotoxy(currentRow, currentCol);
                }
            }
            else if (ch == '0')
            {
                return;
            }
            else
            {
                size++;
                pushInUndo();
                if (currentCol < ritr->size() - 1)
                {
                    ritr->insert(citr, ch);
                    currentCol++;
                    system("cls");
                    showText();
                    gotoxy(currentRow, currentCol);
                }
                else
                {

                    ritr->push_back(ch);
                    currentCol++;
                    citr++;
                    cout << *citr;
                }
            }
            
        }
    }
    void insertText(char c)
    {
        if (c == '\n')
        {
            text.push_back(list<char>());
            currentRow++;
            ritr++;
        }
        else
        {
            (*ritr).push_back(c);
            currentCol++;
            citr++;
        }
        gotoxy(currentRow, currentCol);
    }
    void gotoxy(int x, int y)
    {
        COORD cordinates;
        cordinates.X = y;
        cordinates.Y = x;
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOutput, cordinates);
    }
    void pushInUndo()
    {
        state t;
        t.citr = this -> citr;
        t.ritr = this -> ritr;
        t.currentCol = this -> currentCol;
        t.currentRow = this -> currentRow;
        t.text = this -> text;
        if (undo.size() < 5)
        {
            undo.emplace_back(t);
        }
        else 
        {
            undo.pop_front();
            undo.emplace_back(t);
        }
    }
    void undoOneStep()
    {
        if (!undo.empty())
        {
            state t = undo.back();
            undo.pop_back();
            this -> currentRow = t.currentRow;
            this -> currentCol = t.currentCol;
            this -> text = t.text;
            this -> ritr = t.ritr;
            this -> citr = t.citr;
            size++;
        }
    }
    void redoOneStep()
    {
        if (!redo.empty())
        {
            state t = redo.back();
            redo.pop_back();
            this -> currentRow = t.currentRow;
            this -> currentCol = t.currentCol;
            this -> text = t.text;
            this -> ritr = t.ritr;
            this -> citr = t.citr;
            size++;
        }
    }
    void pushInRedo()
    {
        state t;
        t.citr = this -> citr;
        t.ritr = this -> ritr;
        t.currentCol = this -> currentCol;
        t.currentRow = this -> currentRow;
        t.text = this -> text;
        if (redo.size() < 5)
        {
            redo.emplace_back(t);
        }
        else
        {
            redo.pop_front();
            redo.emplace_back(t);
        }
    }
};
