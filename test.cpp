#include <iostream> 
using namespace std;
int main()
{
    char slash = '\0';
    string temp = "hello";
    cout << temp.length() << endl;
    cout << temp;
    temp = temp + slash;
    cout << temp.length() << endl;
    cout << temp;
}