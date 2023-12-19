#pragma once
#include <iostream>
#include <list>
#include "currentFile.cpp"
using namespace std;
class File
{
    friend class Folder;
    friend class Dos;
    private:
        string name;
        string path;
        currentFile* currFile;
    public:
        File(string name = "", string path ="")
        {
            this -> name = name;
            this -> path = path;
            currFile = new currentFile(name);
        }

};