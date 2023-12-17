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
        list<Folder*> subFolders;
        list<File*> files;
        Folder* parent;
        string path;
    public:
        Folder(string name = "", Folder* parent = nullptr, string path = " ")
        {
            this->name = name;
            this->parent = parent;
            this->path = path;
            subFolders = list<Folder*>();
            files = list<File*>();
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
        void insertFile(string name)
        {
            File* temp = new File(name);
            files.push_back(temp);
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
            list<File*>::iterator fi;
            for (fi = files.begin(); fi!= files.end(); fi++)
            {
                cout << (*fi) -> name << endl;
            }
        }
        void removeDir(Folder* folder)
        {
            while (!folder->subFolders.empty())
            {
                Folder* f = folder->subFolders.front();
                folder->subFolders.pop_front();
                removeDir(f);
            }
            for (auto i: folder->files)
            {
                delete i;
            }
            folder->files.clear();
            folder->parent->subFolders.remove(folder);
            delete folder;
        }
        File* findFile(string name)
        {
            list<File*>::iterator it;
            for (it = files.begin(); it != files.end(); it++)
            {
                if ((*it) -> name == name)
                {
                    return (*it);
                }
            }
            return nullptr;
        }
        void renameFile(File* file, string newName)
        {
            if (file != nullptr)
            {
                file -> name = newName;
            }
        }


};