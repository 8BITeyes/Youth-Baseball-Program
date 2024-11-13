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
void displayArray(string playersArray[][NUMOFCOLUMNS]);

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

	//calculations and output
	sortPlayers(players, sortedPlayers);
	sortLineup(sortedPlayers, playerLineup);
	displayArray(playerLineup);

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
		vector<int> numbersNeeded = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

		for (int j = row; j < NUMOFPLAYERS; j++) {
			bool exists = false;
			int sizeOfRemainingNumbers = numbersNeeded.size();
			int random = numbersNeeded[rand() % sizeOfRemainingNumbers];

 			while (existsInColumn(occupiedNums, i, random) || existsInRow(occupiedNums, j, random))
			{
				if ((sizeOfRemainingNumbers == 1 || sizeOfRemainingNumbers == 2 || sizeOfRemainingNumbers == 3) && existsInRow(occupiedNums, j, random)) {
					j = 0;
					numbersNeeded = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
					sizeOfRemainingNumbers = numbersNeeded.size();

					for (int q = 0; q < NUMOFPLAYERS - 1; q++) {
						occupiedNums[q][i] = 100;
					}
				}

				random = numbersNeeded[rand() % sizeOfRemainingNumbers];
			}

			if (exists == false) {
				numbersNeeded.erase(std::remove(numbersNeeded.begin(), numbersNeeded.end(), random), numbersNeeded.end());

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

	if (randomNum == 10 || randomNum == 11) {
		for (int column = 1; column < NUMOFCOLUMNS; column++) {
			if (positionOccupiedArray[rowNum][column] == 10 || positionOccupiedArray[rowNum][column] == 11) {
				return true;
			}
		}
	}

	for (int column = 1; column < NUMOFCOLUMNS; column++) {
		if (positionOccupiedArray[rowNum][column] == randomNum) {
			exists = true;
			break;
		}
	}

	return exists;
}

void displayArray(string playersArray[][NUMOFCOLUMNS]) {
	cout << "\nGame lineup and field positions:" << endl;
	cout << "________________________________" << endl;
	cout << "Name \t\tInning 1 \tInning 2 \tInning 3 \tInning 4 \tInning 5" << endl;

	for (int i = 0; i < NUMOFPLAYERS; i++) {
		for (int j = 0; j < NUMOFCOLUMNS; j++) {
			cout << playersArray[i][j] << "\t \t";
		}
		cout << endl;
	}

};