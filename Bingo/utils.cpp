#include "utils.h"
#include <cstdlib>
#include <limits>

#define NOMINMAX
#include <windows.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int safeInput() {
    int val;
    while (!(cin >> val)) {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return val;
}

void sleep_for_sec(float seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000); // Sleep takes milliseconds
#else
    sleep(seconds); // Sleep takes seconds
#endif
}
