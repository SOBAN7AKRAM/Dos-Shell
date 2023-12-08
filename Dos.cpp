#include <iostream>
#include "Tree.cpp"
#include "Folder.cpp"
#include "File.cpp"
#pragma once
using namespace std;
class Dos
{
    // friend class Tree;
    // friend class Folder;
    private:
        Tree tree;
        string command = "";
    public:
    bool isMakeDirectory()
    {
        string temp = command.substr(0, 5);
        if (temp == "mkdir" && command.length() > 5)
        {
            string newFolder = command.substr(6, command.length());
            tree.current->insertSubFolder(newFolder);
            return true;
        }
        return false;
    }
    bool isChangeDirectory()
    {
        string temp = command.substr(0, 2);
        if (temp == "cd" && command.length() > 3 && command != "cd..")
        {
            string folder = command.substr(3, command.length());
            tree.goToSubFolder(folder);
            return true;
        }
        return false;
    }
    bool isPrintCurrentPath()
    {
        string temp = command.substr(0, 3);
        if (temp == "cd." && command != "cd..")
        {
            tree.current->printCurrentPath();
            return true;
        } 
        return false;
    }
    bool isPreviousDirectory()
    {
        if (command == "cd..")
        {
            tree.current = tree.current->parent;
            return true;
        }
        else if (command == "cd\\")
        {
            tree.current = tree.root;
            return true;
        }
        return false;
    }
    bool isPrintCurrentDir()
    {
        if (command == "dir")
        {
            tree.current->printCurrentDir();
            return true;
        }
        return false;
    }
    string getCommand()
    {
        string cmd = "";
        int i = 0;
        while (command[i] != ' ' && command[i] != '\0')
        {
            cmd += command[i];
            i++;
        }
        return cmd;
    }
    bool takeInput()
    {
        cout << tree.current->path << ">";
        getline(cin, command);
        if (command == "exit")
        {
            return false;
        }
        else if (isMakeDirectory())
        {
            // create a new directory
        }
        else if (isChangeDirectory())
        {
            // change directory
        }
        else if (isPrintCurrentPath())
        {
            // print current directory
        }
        else if (isPreviousDirectory())
        {
            // return to parent directory
        }
        else if (isPrintCurrentDir())
        {
            // print current directory files or folders
        }
        else
        {
            cout << "'" << getCommand() << "' is not recognized as an internal or external command" << endl;
        }
        return true;
    }
};