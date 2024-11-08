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
string* sortLineup(player sortedPlayerArray[], string playerLineup[][NUMOFINNINGS + 1]);
bool existsInColumn(int positionOccupiedArray[][NUMOFINNINGS], int rowNum, int randomNum);
//string displayArray(string playersArray);

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

player* sortPlayers(player playerAverageArray[], player sortedPlayerAverages[]) {
	int lastMaxNum = 1000;

	for (int i = 0; i < NUMOFPLAYERS; i++) {
		int currentMaxNum = 0;
		string currentName = playerAverageArray[i].name;

		for (int j = 0; j < NUMOFPLAYERS; j++) {
			if (playerAverageArray[j].average > currentMaxNum && playerAverageArray[j].average < lastMaxNum) {
				currentMaxNum = playerAverageArray[j].average;
				currentName = playerAverageArray[j].name;
			}
		}

		sortedPlayerAverages[i].average = currentMaxNum;
		sortedPlayerAverages[i].name = currentName;
		lastMaxNum = currentMaxNum;
	}

	return sortedPlayerAverages;
}


string* sortLineup(player sortedPlayerArray[], string playerLineup[][NUMOFINNINGS + 1]) {
	srand((unsigned) time(NULL));
	int column = 0;
	int row = 0;
	int occupiedNums[NUMOFPLAYERS][NUMOFINNINGS];

	for (int i = row; i < NUMOFPLAYERS; i++) {
		playerLineup[i][column] = sortedPlayerArray[i].name;
	}// Inputs the players names in order into the first column of the lineup (2D array)


	for (int i = column + 1; i < NUMOFINNINGS + 1; i++) {

		for (int j = row; j < NUMOFPLAYERS; j++) {
			bool exists;
			int random = rand() % 12; //random number that will be generated between 0 and 12

			exists = existsInColumn(occupiedNums, j, random);

			if (exists == true) {
				random = rand() % 12;
				exists = existsInColumn(occupiedNums, j, random);
			}
			else {
				occupiedNums[j][i] = random;
				playerLineup[j][i] = POSITIONS[random];
			}

		}

	} //populates the rows after the name row

	return *playerLineup;
};

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

/*string displayArray(string playersArray) {
	cout << "Game lineup and field positions:" << endl;
	cout << "________________________________" << endl;
	cout << "Name \t Inning 1 \t Inning 2 \t Inning 3 \t Inning 4 \t Inning 5" << endl;

} */