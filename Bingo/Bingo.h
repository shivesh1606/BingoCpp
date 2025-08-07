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
	bool isAI = false; // Flag to indicate if the player is an AI
    bool ithCardMap(int i,int j)
    {
		return (card_map & (1 << (i * 5 + j))) != 0; // Check if the bit for the position (i, j) is set
    }
    void updateCardMap(int i, int j)
    {
        card_map |= (1 << (i * 5 + j)); // Set the bit for the position (i, j)
	}
};
void display(player& user);

bool getPlayerCard(player& user);

void getPlayerinfo(player& user);
void PlayerInfo(player& user);
int checkRow(player& user);
int checkCol(player& user);
int diagCount(player& user);
bool gameComplete(player& userA, player& userB);
void display_card(player& user, string& pass);
void cutNumFromUser(player* user, int num);