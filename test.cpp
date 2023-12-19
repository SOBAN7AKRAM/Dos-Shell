#include <iostream>
#include <list>
#include <string>
#include <conio.h>

using namespace std;

// Function to display the text
void displayText(const list<string>& text) {
    for (const auto& line : text) {
        cout << line << endl;
    }
}

int main() {
    list<string> text;  // Each element of the list represents a line of text

    // Sample text for demonstration
    text.push_back("This is line 1");
    text.push_back("This is line 2");
    text.push_back("This is line 3");

    int currentRow = 0; // Track the current row for user input
    int currentCol = 0; // Track the current column for user input

    // Display initial text
    displayText(text);

    while (true) {
        char ch = _getch();  // Get a character from the user

        if (ch == 27) {  // Check for the ESC key (you can use any condition to exit)
            break;
        } else if (ch == '\b') {  // Check for backspace key
            // Implement backspace logic if needed
        } else if (ch == '\r') {  // Check for Enter key
            // Implement new line logic if needed
        } else {
            // Insert the character at the current position
            auto iter = text.begin();
            advance(iter, currentRow);
            iter->insert(iter->begin() + currentCol, ch);
        }

        // Display the updated text
        system("cls"); // Clear console screen (Windows specific)
        displayText(text);
    }

    return 0;
}
