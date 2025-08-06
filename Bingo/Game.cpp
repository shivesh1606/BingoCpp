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
		cout << "Enter Player " << i + 1 << " info:\n";
		player * new_player = new player();
		getPlayerinfo(*new_player);
		addPlayer(new_player);
		clearScreen(); // Clear the screen after each player input
	}
	for (int i = num_players - ai_count; i < num_players; i++) {
		player* new_player = new player();
		new_player->playerName = "AI Player " + to_string(i + 1);
		new_player->playerPass = "ai_pass";
		new_player->isAI = true; // Mark this player as AI
		generateAiCard(*new_player);
		addPlayer(new_player);
	}
	cout << "All players have been initialized.\n Starting Game \n";
	cin.get(); // Wait for user input to proceed

	while(!gameComplete()){
		clearScreen(); // Clear the screen before each turn
		cout << "-------------------------\n";
		for (auto& player : players) {
			chance(player); // Each player takes a turn
		}
	}
	cout << "\n Game Over!\n";
	displayPlayersCard(); // Display all players' cards at the end of the game
	for(auto& player : players) {
		if (checkRow(*player) + checkCol(*player) + diagCount(*player) >= 5) {
			cout << player->playerName << " wins!\n";
			return; // Exit the game loop if a player wins
		}
	}

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
void Game::displayPlayersCard() const {
	cout << "Displaying all players' cards:\n";
	for (const auto& player : players) {
		cout << player->playerName << "'s Card:\n";
		display_card(*player,player->playerPass); // Display each player's card
	}
}

bool Game::gameComplete() const{
	for(auto player: players) {
		if (checkRow(*player) + checkCol(*player) + diagCount(*player) >= 5) {
			cout << player->playerName << " wins!\n";
			return true;
		}
	}
	return false; // Game is not complete yet
}

void Game::chance(player* user)
{
	clearScreen(); // <--- clear before showing menu
	string pass;
	bool isAI = user->isAI; // Check if the player is an AI
	if(isAI==false)
	{
		cout << user->playerName << " : Please enter password: ";
		cin >> pass;
		display_card(*user, pass);
	}
	else
	{
		pass = user->playerPass; // Use the player's password
		cout << user->playerName << " : AI Player, no password required.\n";
		//display_card(*user, user->playerPass);
	}
	while (true)
	{
		if(!isAI)
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
			cout << "Input completed for " << user->playerName << "Enter to continue.\n";
			cin.get(); // Wait for user input to proceed
		}
		else
		{
			cout << user->playerName << " is AI, cutting a random number.\n";
			cut_num(user, true); // AI cuts a random number
			//display_card(*user, pass);
			sleep_for_sec(0.5); // Sleep for a second to simulate AI thinking
		}

		break;
	}
}
int Game::generateRandomNotCutValue(player* user) {
	
	set <int> used; // Set to keep track of used numbers
	int num;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (user->ithCardMap(i, j)) {
				used.insert(user->card[i][j]);
			}
		}
	}
	do {
		num = rand() % 25 + 1; // Generate a random number between 1 and 25
	} while (used.count(num)); // Ensure the number is not already cut
	return num;
}
bool Game::cut_num(player* user, bool random)
{
	int num;
	if (random) {
		num = generateRandomNotCutValue(user); // Generate a random number between 1 and 25

	}
	else {
		cout << "Enter the number to cut (1-25): ";
		num = safeInput();
	}

	  for (auto person : players) {
		  cutNumFromUser(person, num); // Cut the number from all players' cards
	  }

	cout << "Number " << num << " cut from every the card.\n";
	return false;
}
