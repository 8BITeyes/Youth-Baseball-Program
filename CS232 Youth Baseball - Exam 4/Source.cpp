/* 1. The line-up should include batting order and player’s defensive positions for each of the five innings.

2. Each team shall play all players in the field in defensive positions. Additional players, (short fielders), shall be
positioned in the outfield no closer than 20 feet to the baseline when the ball is hit and will be considered
outfielders.

3. Each player must be scheduled to play an infield position at least one (1) inning. Catcher will be considered an
infield position. A player may only be scheduled to play catcher a maximum of one (1) inning per game. No
player may play a second inning of infield until every other player has played one inning of infield.

4. A player cannot play the same defensive position for more than one (1) inning per game.

5. A player can only sit out one (1) inning per game.
*/

#include <iostream>
#include <string>
using namespace std;

const int NUMOFPLAYERS = 12;

int* sortPlayerAverages(int playerAverageArray[], int sortedPlayerAverages[]);

int main() {
	//declarations
	string playerNames[NUMOFPLAYERS];
	int playerAverages[NUMOFPLAYERS];
	int sortedPlayerAveragesArray[NUMOFPLAYERS];

	//get user input
	cout << "Enter 12 player names: " << endl;
	for (int i = 0; i < NUMOFPLAYERS; i++) {
		cout << "What is player " << i + 1 << "'s name: ";
		cin >> playerNames[i];
	} // Inputs the players' names into playerNames Array

	cout << "\nEnter the averages for each player:" << endl << "-----------------------------------" << endl;
	for (int i = 0; i < NUMOFPLAYERS; i++) {
		cout << "What is " << playerNames[i] << "'s average: ";
		cin >> playerAverages[i];
	} // Inputs the players' averages into an array playerAverages

	sortPlayerAverages(playerAverages, sortedPlayerAveragesArray);



	for (int i = 0; i < NUMOFPLAYERS; i++) {
		cout << playerAverages[i] << endl;
	}

	return 0;
}

int* sortPlayerAverages(int playerAverageArray[], int sortedPlayerAverages[]) {
	int lastMaxNum = 1000;

	for (int i = 0; i < NUMOFPLAYERS; i++) {
		int currentMaxNum = 0;

		for (int j = 0; j < NUMOFPLAYERS; j++) {
			if (playerAverageArray[j] > currentMaxNum && playerAverageArray[j] < lastMaxNum)
				currentMaxNum = playerAverageArray[j];
		}

		sortedPlayerAverages[i] = currentMaxNum;
		lastMaxNum = currentMaxNum;
	}





	return sortedPlayerAverages;
}