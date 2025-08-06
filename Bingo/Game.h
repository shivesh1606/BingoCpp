#pragma once
#include "Bingo.h"
class Game
{
	private:
		vector<player*> players; // Vector to hold players
	public:
		Game() {} // Default constructor
		Game(const vector<player*>& players) : players(players) {} // Constructor with players

	void start(); // Start the game
	void addPlayer(player* newPlayer) { players.push_back(newPlayer); } // Add a player to the game
	void generateAiCard(player& newPlayer); // Generate a random Bingo card for the AI player
	void displayPlayersCard() const; // Display all players' cards
	bool gameComplete() const;
	void chance(player* user);
	bool cut_num(player* user, bool random=false);
	int generateRandomNotCutValue(player* user);
	//virtual void display() = 0; // Display the game state
	//virtual void makeMove(int playerId, int move) = 0; // Make a move for a player
	//virtual bool isGameOver() const = 0; // Check if the game is over
	//virtual int getWinner() const = 0; // Get the winner of the game
	virtual ~Game() {} // Virtual destructor for cleanup
};

