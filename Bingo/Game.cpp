#include "Game.h"
#include <string>

void Game::start() {
	// Implement the game logic here
	cout << "Enterting Fun Game Bingo.\n";
	int ai_count = 0;
	cout << "Enter number of players: ";
	int num_players = safeInput();
	cout << "Enter Ai number of players: ";
	ai_count = safeInput();
	for (int i = 0; i < num_players-ai_count; i++) {
		player * new_player = new player();
		getPlayerinfo(*new_player);
		addPlayer(new_player);
	}
	for (int i = num_players - ai_count; i < num_players; i++) {
		player* new_player = new player();
		new_player->playerName = "AI Player " + to_string(i + 1);
		new_player->playerPass = "ai_pass";
		generateAiCard(*new_player);
		addPlayer(new_player);
	}
	cout << "All players have been initialized.\n";
}

void Game::generateAiCard(player& newPlayer) {
	// Generate a random Bingo card for the AI player
	newPlayer.card = vector<vector<int>>(5, vector<int>(5));
	set<int> used;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int val;
			do {
				val = rand() % 25 + 1; // Random number between 1 and 25
			} while (used.count(val)); // Ensure no duplicates
			newPlayer.card[i][j] = val;
			used.insert(val);
		}
	}
}