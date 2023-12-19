#include <iostream>
#include <sstream>
#include <queue>
#include "Tree.cpp"
#include "Folder.cpp"
#include "File.cpp"
#include "currentFile.cpp"
#pragma once
using namespace std;
void gotoxy(int x, int y)
{
    COORD cordinates;
    cordinates.X = x;
    cordinates.Y = y;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, cordinates);
}
void printName()
{
    system("cls");
    gotoxy(40, 0);
    cout << "M Soban Akram || 2022-CS-173 || BSc. Computer Science" << endl << endl << endl;
}
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
    bool isCreateFile()
    {
        string temp = command.substr(0, 6);
        if (temp == "create")
        {
            string ext = command.substr(command.length() - 4, command.length());
            if (ext == ".txt")
            {
                string name = command.substr(7, command.length() - 5);
                tree.current -> insertFile(name);
                return true;
            }
            else 
            {
                cout << "Invalid Extension!" << endl;
                return false;
            }
        }
        return false;
    }
    bool isRemoveDir()
    {
        string temp = command.substr(0, 5);
        if (temp == "rmdir")
        {
            string folder = command.substr(6, command.length());
            Folder* f = tree.current -> findFolder(folder);
            if (f != nullptr)
            {
                tree.current->removeDir(f);
            }
            else 
            {
                cout << "Folder does not exist" << endl;
            }
            return true;
        }
        return false;
    }
    bool isRename()
    {
        size_t first = command.find(' ');
        string temp = command.substr(0, first);
        if (temp == "rename")
        {
            size_t second = command.find(' ', first + 1);
            string name = command.substr(first + 1, second - first - 1);
            string newName = command.substr(second + 1, command.find(' ', second + 1));
            File* f = tree.current->findFile(name);
            if (f != nullptr)
            {
                tree.current->renameFile(f, newName);
            }
            else 
            {
                cout << "File does not exist" << endl;
            }

            return true;
        }
        return false;
    }
    bool isCopy()
    {
        size_t firstSpace = command.find_first_of(' ', 0);
        string temp = command.substr(0, firstSpace);
        if (temp == "copy")
        {
            int sizeStart = command.find(' ') + 1;
            string name = command.substr(sizeStart, command.find(' ', sizeStart) - sizeStart);
            File* f = tree.current->findFile(name);
            if (f != nullptr)
            {
                string location = command.substr(command.find(' ', sizeStart) + 1);
                string p = location.substr(0, location.find('\\') + 1);
                if (p == "V:\\")
                {
                    Folder* fd = tree.current->findPath(location, tree.root);
                    if (fd != nullptr)
                    {
                        fd->insertFile(name);
                    }
                    else cout << "Destination is not found" << endl;
                }
                else 
                {
                    Folder* fd = tree.current->findPath(tree.current -> path + location, tree.current);
                    if (fd != nullptr)
                    {
                        fd -> insertFile(name);
                    }
                    else cout << "Destination is not found" << endl;
                }

            }
            else
            {
                cout << "File does not exist" << endl;
            }
            return true;
        }
        return false;
    }
    bool isDel()
    {
        size_t first = command.find(' ');
        string temp = command.substr(0, first);
        if (temp == "del")
        {
            string name = command.substr(first + 1, command.length() - first);
            File* f = tree.current->findFile(name);
            if (f != nullptr)
            {
                tree.current->deleteFile(f);
            }
            else 
            {
                cout << "File does not Exist" << endl;
            }
            return true;
        }
        return false;
    }
    bool isMove()
    {
        size_t first = command.find(' ');
        string temp = command.substr(0, first);
        if (temp == "move")
        {
            int sizeStart = command.find(' ') + 1;
            string name = command.substr(sizeStart, command.find(' ', sizeStart) - sizeStart);
            File* f = tree.current->findFile(name);
             if (f != nullptr)
            {
                string location = command.substr(command.find(' ', sizeStart) + 1);
                string p = location.substr(0, location.find('\\') + 1);
                if (p == "V:\\")
                {
                    Folder* fd = tree.current->findPath(location, tree.root);
                    if (fd != nullptr)
                    {
                        fd->insertFile(name);
                        tree.current->deleteFile(f);
                    }
                    else cout << "Destination is not found" << endl;
                }
                else 
                {
                    Folder* fd = tree.current->findPath(tree.current -> path + location, tree.current);
                    if (fd != nullptr)
                    {
                        fd -> insertFile(name);
                    }
                    else cout << "Destination is not found" << endl;
                }

            }
            else
            {
                cout << "File does not exist" << endl;
            }
            return true;
        }
        return false;
    }
    bool isFind()
    {
        size_t first = command.find(' ');
        string temp = command.substr(0, first);
        if (temp == "find")
        {
            int sizeStart = command.find(' ') + 1;
            string location = command.substr(sizeStart, command.find(' ', sizeStart) - sizeStart);
            string name = command.substr(command.find(' ', sizeStart) + 1);
            Folder* fd = tree.current->findPath(location, tree.root);
            if (fd != nullptr)
            {
                File* file = fd->findFile(name);
                if (file != nullptr)
                {
                    cout << "File Exist" << endl;
                }
                else 
                {
                    cout <<"File does not Exist in that Directory" << endl;
                }
            }
            else
            {
                cout << "Path is not found" << endl;
            }
            return true;
        }
        return false;
    }
    bool isFormat()
    {
        if (command == "format")
        {
            tree.current->removeDir(tree.root);
            tree.current = tree.root;
            return true;
        }
        return false;
    }
    bool isEdit()
    {
        string temp = command.substr(0, command.find(' '));
        if (temp == "edit")
        {
            string name = command.substr(command.find(' ') + 1, command.length());
            File* f = tree.current->findFile(name);
            if (f != nullptr)
            {       
                system("cls");
                f->currFile->edit();
                cout << endl;
            }
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
        else if (isCreateFile())
        {
            // create a new text file
        }
        else if (isRemoveDir())
        {
            // remove the directory of current folder
        }
        else if (isRename())
        {
            // rename the file
        }
        else if (isCopy())
        {
            // copy the file
        }
        else if(isDel())
        {
            // delete the file
        }
        else if(isMove())
        {
            // move the file
        }
        else if(isFind())
        {
            // find the file in provided path
        }
        else if(isFormat())
        {
            // Format the entire disk
        }
        else if(isEdit())
        {
            system("cls");
            printName();
            // Edit the file
        }
        else if(command == "pwd")
        {
            cout << tree.current->path << endl;
        }
        else if(command == "ver")
        {
            cout << "Dos Shell 2.0.7" << endl;
        }
        else
        {
            cout << "'" << getCommand() << "' is not recognized as an internal or external command" << endl;
        }
        return true;
    }
};