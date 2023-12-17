#pragma once
#include <iostream>
#include <list>
using namespace std;
class File
{
    friend class Folder;
    private:
        string name;
        list<char> data;
    public:
        File(string name = "")
        {
            this -> name = name;
        }
};