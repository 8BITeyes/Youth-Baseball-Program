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
const int NUMOFCOLUMNS = 6;
const int MIN = 0;
const string POSITIONS[NUMOFPLAYERS] = { "P", "C", "1B", "2B", "SS", "3B", "RF", "LF", "RCF", "LCF", "OUT", "OUT"};

//Function declarations
player* sortPlayers(player playersArray[], player sortedPlayerAverages[]);
void sortLineup(player sortedPlayerArray[], string playerLineup[][NUMOFCOLUMNS]);
bool existsInColumn(int positionOccupiedArray[][NUMOFCOLUMNS], int rowNum, int randomNum);
bool existsInRow(int positionOccupiedArray[][NUMOFCOLUMNS], int columnNum, int randomNum);
//string displayArray(string playersArray);

int main() {
	//declarations
	player players[NUMOFPLAYERS];
	player sortedPlayers[NUMOFPLAYERS];
	string playerLineup[NUMOFPLAYERS][NUMOFCOLUMNS];

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


void sortLineup(player sortedPlayerArray[], string playerLineup[][NUMOFCOLUMNS]) {
	srand((unsigned)time(NULL));
	int column = 0;
	int row = 0;
	int occupiedNums[NUMOFPLAYERS][NUMOFCOLUMNS];

	for (int i = row; i < NUMOFPLAYERS; i++) {
		playerLineup[i][column] = sortedPlayerArray[i].name;
	}// Inputs the players names in order into the first column of the lineup (2D array)


	for (int i = column + 1; i < NUMOFCOLUMNS; i++) {

		for (int j = row; j < NUMOFPLAYERS; j++) {
			bool exists = false;
			int random = rand() % 12;

			while (existsInColumn(occupiedNums, i, random) || existsInRow(occupiedNums, row, random))
			{
				random = rand() % 12;
			}

			if (exists == false) {
				occupiedNums[j][i] = random;
				playerLineup[j][i] = POSITIONS[random];
			}
		}
	} //populates the rows after the name row

}

bool existsInColumn(int positionOccupiedArray[][NUMOFCOLUMNS], int columnNum, int randomNum) {
	bool exists = false;

	for (int row = 0; row < NUMOFPLAYERS; row++) {
		if (positionOccupiedArray[row][columnNum] == randomNum) {
			exists = true;
			break;
		}
	}

	return exists;
}

bool existsInRow(int positionOccupiedArray[][NUMOFCOLUMNS], int rowNum, int randomNum) {
	bool exists = false;

	for (int column = 1; column < NUMOFCOLUMNS; column++) {
		if (randomNum == 10 || randomNum == 11) {
			if (positionOccupiedArray[rowNum][column] == 10 || positionOccupiedArray[rowNum][column] == 11) {
				exists = true;
			}
			break;
		}

		if (positionOccupiedArray[rowNum][column] == randomNum) {
			exists = true;
			break;
		}
	}

	return exists;
}

/*string displayArray(string playersArray) {
	cout << "Game lineup and field positions:" << endl;
	cout << "________________________________" << endl;
	cout << "Name \t Inning 1 \t Inning 2 \t Inning 3 \t Inning 4 \t Inning 5" << endl;

} */