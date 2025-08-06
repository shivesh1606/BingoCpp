#include "Bingo.h"
void display(player& user) {
    cout << user.playerName << " :\nPlease enter password: ";
    string pass;
    cin >> pass;

    if (pass == user.playerPass) {
        for (auto& row : user.card) {
            for (auto& col : row) {
                cout << setw(3) << col << " ";
            }
            cout << "\n";
        }
    }
    else {
        cout << "Wrong password\n";
    }
    cout << "......................\n";
}

bool getPlayerCard(player& user)
{
    user.card = vector<vector<int>>(5, vector<int>(5));
    set<int> used;

    for (int i = 0; i < 5;)
    {
        cout << "Enter 5 numbers for row " << i + 1 << " (1-25): ";
        bool rowCorrect = true;
        for (int j = 0; j < 5; j++)
        {
            int val = safeInput();

            if (val <= 0 || val > 25 || used.count(val))
            {
                cout << "Invalid or duplicate number: " << val << "\n";
				rowCorrect = false;
                break;
            }
            user.card[i][j] = val;
            used.insert(val);
        }
        if (!rowCorrect) {
            for(int j = 0; j < 5; j++) {
				used.erase(user.card[i][j]); // Remove the invalid numbers from the set
                user.card[i][j] = 0; // Reset the row to zero if invalid
                
			}
            cout << "Please enter the row again.\n";
            continue; // Skip to the next iteration to re-enter the row
		}
        i++;
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
void PlayerInfo(player& user) {
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
    if (user.ithCardMap(0, 0) == 1 && user.ithCardMap(1, 1) == 1 && user.ithCardMap(2, 2) == 1 && user.ithCardMap(3, 3) == 1 && user.ithCardMap(4, 4) == 1)
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
void display_card(player& user, string& pass)
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
