#include <iostream>
#include <list>
#include <string>
#include "File.cpp"
#pragma once
using namespace std;
class Folder
{
    friend class Dos;
    friend class Tree;
    private:
        string name;
        string time;
        list<Folder*> subFolders = list<Folder*>();
        list<File*> files = list<File*>();
        Folder* parent;
        string path;
    public:
        Folder(string name = "", Folder* parent = nullptr, string path = " ")
        {
            this->name = name;
            this->parent = parent;
            this->path = path;
        }
        void insertSubFolder(string name)
        {
            char slash = '\0';
            if (name == "V:")
            {
                return;
            }
            if (path[path.length() - 1] != '\\')
            {
                slash = 92;
            }
                Folder* temp = new Folder(name, this, path + slash + name);
                subFolders.push_back(temp);
        }
        Folder* findFolder(string folderName)
        {
            list<Folder*>::iterator it;
            for(it = subFolders.begin(); it != subFolders.end(); it++)
            {
                if ((*it) -> name == folderName)
                {
                    return (*it);
                }
            }
            return nullptr;
        }
        void printCurrentPath()
        {
            cout << this -> path << endl;
        }
        void printCurrentDir()
        {
            list<Folder*>::iterator it;
            for (it = subFolders.begin(); it != subFolders.end(); it++)
            {
                cout << (*it) -> name << endl;
            }
        }


};