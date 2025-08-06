#pragma once
#include <cstdlib>
#include <limits>
#include <iostream>
#include <string>


using namespace std;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return val;
}


