#include <iostream>
#include "Folder.cpp"
#pragma once
using namespace std;
class Tree
{
    friend class Dos;
    private:
        Folder* current;
        Folder* root;
    public:
        Tree()
        {
            root = current = new Folder("V:", nullptr, "V:\\");
        }
        void goToSubFolder(string folderName)
        {
            Folder* temp = current->findFolder(folderName);
            if (temp != nullptr)
            {
                current = temp;
            }
            else
            {
                cout << "Folder does not exist" << endl;
            }
        }
};