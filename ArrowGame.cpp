#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Enum for arrow keys for better clarity
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
    return UP;  // Default case (this should never happen)
}

// Function to display the corresponding arrow key as a string
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
    return GetAsyncKeyState(key) & 0x8000;  // Check if key is pressed
}

// Function to display the remaining time (10 seconds countdown)
void displayTimer(int timeLeft) {
    cout << "\rTime Left: " << timeLeft << " seconds remaining...   " << flush;
}

// Function to handle game logic
void startGame() {
    const int sequenceLength = 10;
    ArrowKey sequence[sequenceLength];

    // Initialize random number generator
    srand(static_cast<unsigned>(time(0)));

    // Generate a random sequence of arrow keys
    for (int i = 0; i < sequenceLength; ++i) {
        sequence[i] = getRandomArrow();
    }

    // Set a 10-second timer
    auto startTime = chrono::steady_clock::now();
    int currentIndex = 0;
    bool gameWon = false;
    bool keyPressed = false;

    // Display instructions
    cout << "Press the following arrow keys in the correct order:" << endl;
    for (int i = 0; i < sequenceLength; ++i) {
        cout << arrowKeyToString(sequence[i]) << " ";
    }
    cout << endl;

    // Start the countdown and game logic
    while (chrono::steady_clock::now() - startTime < chrono::seconds(10)) {
        // Get the remaining time
        int timeLeft = 10 - chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
        displayTimer(timeLeft);

        if (currentIndex < sequenceLength) {
            // Check for key press in sequence
            if (!keyPressed) {
                if (isKeyPressed(sequence[currentIndex])) {
                    currentIndex++;  // Move to next key in sequence
                    keyPressed = true;  // Block further input until the key is released
                    system("CLS");
                    cout << "Press the following arrow keys in the correct order:" << endl;
                    for (int i = 0; i < sequenceLength; ++i) {
                        cout << arrowKeyToString(sequence[i]) << " ";
                    }
                    cout << endl;
                    cout << "\nCorrect! NEXT [" << arrowKeyToString(sequence[currentIndex]) << "]" << endl;
                    cout << endl;
                }
            }
        }
        else {
            // Player has completed the sequence
            gameWon = true;
            break;
        }

        // If the player has pressed the correct key, wait for key release before accepting next key press
        if (keyPressed) {
            // Wait for key release before accepting the next key press
            while (isKeyPressed(sequence[currentIndex - 1])) {
                this_thread::sleep_for(chrono::milliseconds(10));  // Just to prevent high CPU usage
            }
            keyPressed = false;  // Reset to allow next press
        }

        // Add a small delay to prevent CPU overuse
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    // End of game feedback
    if (gameWon) {
        cout << "\nCongratulations! You completed the sequence correctly!" << endl;
    }
    else {
        cout << "\nTime's up! You failed to complete the sequence in time." << endl;
    }
}

int main() {
    // Start the game
    startGame();
    return 0;
}
