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
        string path;
    public:
        File(string name = "", string path ="")
        {
            this -> name = name;
            this -> path = path;
        }
};