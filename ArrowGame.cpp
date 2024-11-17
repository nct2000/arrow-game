#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>

using namespace std;

// Enum for arrow keys
enum ArrowKey { UP = VK_UP, DOWN = VK_DOWN, LEFT = VK_LEFT, RIGHT = VK_RIGHT };

// Function to generate a random arrow key
ArrowKey getRandomArrow() {
    int random = rand() % 4;
    switch (random) {
    case 0: return UP;
    case 1: return DOWN;
    case 2: return LEFT;
    case 3: return RIGHT;
    }
    return UP;  // Default case
}

// Function to display the arrow key as a string
string arrowKeyToString(ArrowKey key) {
    switch (key) {
    case UP: return "UP";
    case DOWN: return "DOWN";
    case LEFT: return "LEFT";
    case RIGHT: return "RIGHT";
    default: return "UNKNOWN";
    }
}

// Function to check if a specific key is pressed
bool isKeyPressed(ArrowKey key) {
    return GetAsyncKeyState(key) & 0x8000;
}

// Function to position the console cursor
void moveCursorToPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to display the static text once on line 3
void displayStaticStatus() {
    moveCursorToPosition(0, 3); // Move to line 3
    cout << "Time Left:    seconds | Next Key: [";
}

// Function to update the dynamic parts of the status line on line 3
void updateStatus(int timeLeft, const string& nextKey) {
    moveCursorToPosition(11, 3);
    cout << "  ";
    moveCursorToPosition(35, 3);
    cout << "                 ";

    // Write the new dynamic values
    moveCursorToPosition(11, 3);
    cout << timeLeft;
    moveCursorToPosition(35, 3);
    cout << nextKey << "] to attack!";
}

// Function to handle game logic
void startGame() {
    const int sequenceLength = 20;
    vector<ArrowKey> sequence(sequenceLength);

    // Initialize random number generator
    srand(static_cast<unsigned>(time(0)));

    // Generate a random sequence of arrow keys
    for (int i = 0; i < sequenceLength; ++i) {
        sequence[i] = getRandomArrow();
    }

    // Display instructions
    cout << "Press the following arrow keys in the correct order:" << endl;
    for (int i = 0; i < sequenceLength; ++i) {
        cout << arrowKeyToString(sequence[i]) << " ";
    }
    cout << endl;

    // Display static status line
    displayStaticStatus();

    // Start a 20-second timer
    auto startTime = chrono::steady_clock::now();
    int currentIndex = 0;
    bool gameWon = false;

    // Game loop
    while (chrono::steady_clock::now() - startTime < chrono::seconds(20)) {
        int timeLeft = 20 - chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
        string nextKey = currentIndex < sequenceLength ? arrowKeyToString(sequence[currentIndex]) : "None";

        // Update the dynamic parts of the status line
        updateStatus(timeLeft, nextKey);

        // Check for correct key press
        if (currentIndex < sequenceLength && isKeyPressed(sequence[currentIndex])) {
            currentIndex++;  // Move to the next key

            // Wait for key release to prevent double detection
            while (isKeyPressed(sequence[currentIndex - 1])) {
                this_thread::sleep_for(chrono::milliseconds(10));
            }
        }

        // Check if the sequence is completed
        if (currentIndex == sequenceLength) {
            gameWon = true;
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(10));  // Frequent checks for keypress
    }

    // Move the cursor to a new line for game feedback
    moveCursorToPosition(0, 5);
    if (gameWon) {
        cout << "Congratulations! You completed the sequence correctly!" << endl;
    }
    else {
        cout << "Time's up! You failed to complete the sequence in time." << endl;
    }
}

int main() {
    startGame();
    return 0;
}
