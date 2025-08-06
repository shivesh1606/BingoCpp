#pragma once
#include "utils.h"
#include <iomanip>
#include <iostream>
#include <vector>

#include <cstdlib> // Add this include at the top of your file for rand()
#include <set>

// Red color if marked, white otherwise
#define RED "\033[1;31m"
#define RESET "\033[0m"
struct player
{
    vector<vector<int>> card;
    long int card_map=0;

    string playerName;
    string playerPass;
    bool ithCardMap(int i,int j)
    {
		return (card_map & (1 << (i * 5 + j))) != 0; // Check if the bit for the position (i, j) is set
    }
    void updateCardMap(int i, int j)
    {
        card_map |= (1 << (i * 5 + j)); // Set the bit for the position (i, j)
	}
};
vector<player* > players;
void display(player& user)
{
    cout << user.playerName << " :\n Please enter password:";
    string pass;
    cin >> pass;
    if (pass == user.playerPass)
    {
        for (auto row : user.card)
        {
            for (auto col : row)
            {
                cout << setw(3) << col << " "; // 3-character wide column
            }
            cout << "\n";
        }
    }
    else
    {
        cout << "Wrong password\n";
    }
    cout << "......................\n";
}
int checkRow(player& user)
{
    int row_count = 0;
    for (int i = 0; i < 5; i++)
    {
        int cross = 0;
        for (int j = 0; j < 5; j++)
        {
            if (user.ithCardMap(i, j))
                cross++;
        }
        if (cross == 5)
            row_count++;
    }
    return row_count;
}

int checkCol(player& user)
{
    int col_count = 0;
    for (int j = 0; j < 5; j++)
    {
        int cross = 0;
        for (int i = 0; i < 5; i++)
        {
            if (user.ithCardMap(i, j))
                cross++;
        }
        if (cross == 5)
            col_count++;
    }
    return col_count;
}

int diagCount(player& user)
{
    int count = 0;
    if (user.ithCardMap(0,0) == 1 && user.ithCardMap(1, 1) == 1 && user.ithCardMap(2, 2) == 1 && user.ithCardMap(3, 3) == 1 && user.ithCardMap(4, 4) == 1)
        count++;
    if (user.ithCardMap(0, 4) == 1 && user.ithCardMap(1, 3) == 1 && user.ithCardMap(2, 2) == 1 && user.ithCardMap(3, 1) == 1 && user.ithCardMap(4, 0) == 1)
        count++;
    return count;
}
bool gameComplete(player& userA, player& userB)
{
    int row_countA = checkRow(userA);
    int col_countA = checkCol(userA);
    int diag_countA = diagCount(userA);
    int row_countB = checkRow(userB);
    int col_countB = checkCol(userB);
    int diag_countB = diagCount(userB);
    if (row_countA + col_countA + diag_countA >= 5 || row_countB + col_countB + diag_countB >= 5)
        return true;
    return false;
}
void display_card(player& user,string &pass)
{

    if (pass == user.playerPass)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {


                if (user.ithCardMap(i, j))
                    cout << RED << setw(3) << user.card[i][j] << RESET << " ";
                else
                    cout << setw(3) << user.card[i][j] << " ";


            }
            cout << "\n";
        }
    }
    else
    {
        cout << "Wrong password\n";
    }
    cout << "......................\n";
}

void cutNumFromUser(player* user, int num) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (user->card[i][j] == num) {
                user->updateCardMap(i, j); // Update the card map to mark the number as cut
                return;
            }
        }
    }
}
bool cut_num(player* user,bool random=false) {
	
	int num;
    if (random) {
		num = rand() % 25 + 1; // Generate a random number between 1 and 25
    }
    else{ 
        cout << "Enter the number to cut (1-25): "; 
        num = safeInput();
    }

    for (auto person : players) {
		cutNumFromUser(person, num); // Cut the number from all players' cards
    }
    
    cout << "Number " << num << " cut from both the card.\n";
    return false;
}
void chance(player* user)
{
    clearScreen(); // <--- clear before showing menu
    cout << user->playerName << " : Please enter password: ";
    string pass;
    cin >> pass;
    display_card(*user,pass);
    while (true)
    {
        cout << "Select Choice: 1.Enter Number to cut\n2.Cut Random Number\n";
        int num;
        num = safeInput();
        switch (num)
        {
        case 1:
			cut_num(user);
            break;
        case 2:
            cut_num(user, true);
            break;
		default:
            cout << "Wrong Choice\n";
            continue;
        }
		cout << "Update Card:\n";
        display_card(*user, pass);
        cin >> num;
        break;
    }
}