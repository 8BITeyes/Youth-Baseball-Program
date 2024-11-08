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
#include <cstdio>
#include <random>
using namespace std;

struct player {
	string name;
	int average{};
};

//Constant declarations
const int NUMOFPLAYERS = 12;
const int NUMOFINNINGS = 5;
const int MIN = 0;
const string POSITIONS[NUMOFPLAYERS + 1] = { "P", "C", "1B", "2B", "SS", "3B", "RF", "LF", "RCF", "LCF", "OUT", "OUT"};

//Function declarations
player* sortPlayers(player playersArray[], player sortedPlayerAverages[]);
string displayArray(string playersArray);
string* sortLineup(player sortedPlayerArray[], string playerLineup[][NUMOFINNINGS + 1]);
bool existsInColumn(int positionOccupiedArray[][NUMOFINNINGS], int rowNum, int randomNum);

int main() {
	//declarations
	player players[NUMOFPLAYERS];
	player sortedPlayers[NUMOFPLAYERS];
	string playerLineup[NUMOFPLAYERS][NUMOFINNINGS + 1];

	//get user input
	cout << "Enter 12 player names: " << endl;
	for (int i = 0; i < NUMOFPLAYERS; i++) {
		cout << "What is player " << i + 1 << "'s name: ";
		cin >> players[i].name;
	} // Inputs the players' names into playerNames Array

	cout << "\nEnter the averages for each player:" << endl << "-----------------------------------" << endl;
	for (int i = 0; i < NUMOFPLAYERS; i++) {
		cout << "What is " << players[i].name << "'s average: ";
		cin >> players[i].average;
	} // Inputs the players' averages into an array playerAverages


	sortPlayers(players, sortedPlayers);
	sortLineup(sortedPlayers, playerLineup);


	//displayArray(playerLineup);

	return 0;
}

player* sortPlayers(player playerAverageArray[], player sortedPlayers[]) {
	int currentMaxAverageInIteration;
	string currentNameInIteration;

	for (int i = 0; i < NUMOFPLAYERS; i++) {
		currentMaxAverageInIteration = playerAverageArray[i].average;
		currentNameInIteration = playerAverageArray[i].name;

		for (int j = 1; j < NUMOFPLAYERS; j++) {
			if (currentMaxAverageInIteration < playerAverageArray[j].average) {
				currentMaxAverageInIteration = playerAverageArray[j].average;
				sortedPlayers[i].average = playerAverageArray[j].average;
				sortedPlayers[i].name = playerAverageArray[j].name;
				playerAverageArray[j].average = currentMaxAverageInIteration;
			}
		}

		sortedPlayers[i].average = currentMaxAverageInIteration;
		sortedPlayers[i].name = currentNameInIteration;
	}

	return sortedPlayers;
}

string* sortLineup(player sortedPlayerArray[], string playerLineup[][NUMOFINNINGS]) {
	srand((unsigned) time(NULL));
	int column = 0;
	int row = 0;
	int occupiedNums[NUMOFPLAYERS][NUMOFINNINGS];

	for (int i = row; i < NUMOFPLAYERS; i++) {
		playerLineup[i][column] = sortedPlayerArray[i].name;
	}// Inputs the players names in order into the first column of the lineup (2D array)


	for (int i = row + 1; i < NUMOFPLAYERS; i++) {

		for (int j = column; j <= NUMOFPLAYERS; j++) {
			bool exists;
			int random = rand() % 12; //random number that will be generated between 0 and 12

			exists = existsInColumn(occupiedNums, j, random);

			if (exists == true) {
				random = rand() % 12;
				exists = existsInColumn(occupiedNums, j, random);
			}
			else {
				occupiedNums[i][j] = random;
				playerLineup[i][j] = POSITIONS[random];
			}

		}

	} //populates the rows after the name row

	return *playerLineup;
};

/*string displayArray(string playersArray) {
	cout << "Game lineup and field positions:" << endl;
	cout << "________________________________" << endl;
	cout << "Name \t Inning 1 \t Inning 2 \t Inning 3 \t Inning 4 \t Inning 5" << endl;

} */

bool existsInColumn(int positionOccupiedArray[][NUMOFINNINGS], int columnNum, int randomNum) {
	int row;
	int column = columnNum;
	bool exists;

	for (int row = 0; row < NUMOFPLAYERS; row++) {
		if (positionOccupiedArray[row][columnNum] == randomNum) {
			exists = true;
		}
		else {
			exists = false;
		}
	}

	return exists;
}