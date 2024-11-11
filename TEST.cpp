#include <iostream>
#include <windows.h>  // For GetAsyncKeyState()

int main() {
    // Bold text
    std::cout << "\033[1mThis is bold text.\033[0m\n";

    // Underlined text
    std::cout << "\033[4mThis is underlined text.\033[0m\n";

    // Colored text (Red)
    std::cout << "\033[31mThis is red text.\033[0m\n";

    std::cout << "Press Arrow keys or ESC to trigger actions. Press 'Esc' to quit." << std::endl;

    // Keep track of the previous state of each key
    bool upKeyPreviouslyPressed = false;
    bool downKeyPreviouslyPressed = false;
    bool leftKeyPreviouslyPressed = false;
    bool rightKeyPreviouslyPressed = false;
    bool escKeyPreviouslyPressed = false;

    while (true) {
        // Check the state of the Arrow keys and ESC key
        SHORT upKeyState = GetAsyncKeyState(VK_UP);
        SHORT downKeyState = GetAsyncKeyState(VK_DOWN);
        SHORT leftKeyState = GetAsyncKeyState(VK_LEFT);
        SHORT rightKeyState = GetAsyncKeyState(VK_RIGHT);
        SHORT escKeyState = GetAsyncKeyState(VK_ESCAPE);

        // Check if the 'Up' Arrow key was just pressed
        if ((upKeyState & 0x8000) && !upKeyPreviouslyPressed) {
            std::cout << "Up Arrow key pressed!" << std::endl;
        }

        // Check if the 'Down' Arrow key was just pressed
        if ((downKeyState & 0x8000) && !downKeyPreviouslyPressed) {
            std::cout << "Down Arrow key pressed!" << std::endl;
        }

        // Check if the 'Left' Arrow key was just pressed
        if ((leftKeyState & 0x8000) && !leftKeyPreviouslyPressed) {
            std::cout << "Left Arrow key pressed!" << std::endl;
        }

        // Check if the 'Right' Arrow key was just pressed
        if ((rightKeyState & 0x8000) && !rightKeyPreviouslyPressed) {
            std::cout << "Right Arrow key pressed!" << std::endl;
        }

        // Check if the 'Esc' key was just pressed
        if ((escKeyState & 0x8000) && !escKeyPreviouslyPressed) {
            std::cout << "Esc key pressed. Exiting program." << std::endl;
            break;  // Exit the program
        }

        // Update the previous key state to the current state for each key
        upKeyPreviouslyPressed = (upKeyState & 0x8000) != 0;
        downKeyPreviouslyPressed = (downKeyState & 0x8000) != 0;
        leftKeyPreviouslyPressed = (leftKeyState & 0x8000) != 0;
        rightKeyPreviouslyPressed = (rightKeyState & 0x8000) != 0;
        escKeyPreviouslyPressed = (escKeyState & 0x8000) != 0;

        // Optional: slow down the loop to prevent excessive CPU usage
        Sleep(10);  // Sleep for 10 milliseconds
    }

    return 0;
}
