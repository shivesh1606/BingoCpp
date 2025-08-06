#include "Bingo.h"


bool getPlayerCard(player& user)
{
    user.card = vector<vector<int>>(5, vector<int>(5));
    set<int> used;

    for (int i = 0; i < 5; i++)
    {
        cout << "Enter 5 numbers for row " << i + 1 << " (1-25): ";
        for (int j = 0; j < 5; j++)
        {
			int val = safeInput();
            if (val <= 0 || val > 25 || used.count(val))
            {
                cout << "Invalid or duplicate number: " << val << "\n";
                return false;
            }
            user.card[i][j] = val;
            used.insert(val);
        }
    }
    return true;
}

void getPlayerinfo(player& user)
{
    cout << "Enter Player Name\n";
    cin >> user.playerName;
    cout << "Enter Player Pass\n";
    cin >> user.playerPass;
    cout << "Enter Player Bingo Card (5x5):\n";
    while (!getPlayerCard(user)) {
        cout << "Enter Again!!";
    };

}
void PlayerInfo(player& user)
{
    user.card = vector<vector<int>>(5, vector<int>(5, 0));
    user.card_map = 0;
    clearScreen(); // <--- clear before showing menu
    while (true)
    {
        int choice;
        int exit_case = 0;
        cout << "1. Add Player\n2. View Player\n3. Edit Player Card\n4. Save Player Info\n";
        choice = safeInput();
        switch (choice)
        {
        case 1:
            getPlayerinfo(user);

            break;
        case 2:
            display(user);
            break;
        case 3:
            getPlayerinfo(user);
			break;
        case 4:
            exit_case = 1;
            break;
        default:
            cout << "Wrong Choice\n";
            break;
        }
        if (exit_case)
            break;
    }
}
int main()
{
    player userA, userB;

    cout << "Player A........\n";
    PlayerInfo(userA);
    clearScreen(); // <--- here
    clearScreen(); // <--- here
    cout << "Player B........\n";
    PlayerInfo(userB);

    players.push_back(&userA);

    players.push_back(&userB);

    player* user = &userA;

    while (!gameComplete(userA, userB))
    {
        clearScreen(); // <--- here
        cout << "-------------------------\n";
        cout << "Player " << user->playerName << "'s turn\n";
        chance(user);
        user = (user == &userA) ? &userB : &userA;
    }

    cout << "\n Game Over!\n";
    if (checkRow(userA) + checkCol(userA) + diagCount(userA) >= 5)
        cout << userA.playerName << " wins!\n";
    else
        cout << userB.playerName << " wins!\n";

    return 0;
}
