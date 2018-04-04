#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//constants 
const int mapSize = 9;

//ifstream infile("/*name of the file for the map*/") 
// if( !infile) 
// cout error
// count unable to open file 
// else 
// nested for loop with values i and j that increment as long as i < map array size 
// infile >> mapArray[i][j]
void outputMap(int mapArray[mapSize][mapSize]);

int passMountain(int currentRow, int mapArray[mapSize][mapSize], int currentColumn);

void loadMap(int mapArray[mapSize][mapSize], int mapSelect);


int main()
{
	//variables
	int mapArray[mapSize][mapSize];							//array of mapsize by mapsize, used to copy numbers on the map(x).txt into
	int mapSelect;											//user inputs which number map they want, copies appropriate .txt file into the array 
	int interfaceSelect;									//user inputs which interface option they want
	int mountainPassSelect;									//user inputs whether that want to pass the mountain or not
	int currentRow;											//the current row that the mountain pass section has selected to be the lowest value, used to 
															//determine what is one up, one down and the same as the row that was previously selected
	int currentColumn;										//the current column that the mountain pass has to go through

	int nextNumber;											//value returned from the mountain pass function to determine which row to go onto next
	int startingPoint;										//user inputs where on the map to start 0-8
	bool mapLoaded = false;									//determines whether a map has been loaded so if the user asks a map to be displayed without
															//one loaded it will ask them to load one first
	do
	{
		//main interface
		system("cls");															//main interface used to select whether to open the map file loader
		cout << "Choose a map file and then display the map" << endl;			//display the current map that has been loaded or exit the program
		cout << "(1) Choose map file" << endl;
		cout << "(2) Display current map file" << endl;
		cout << "(3) Exit the program" << endl;
		cin >> interfaceSelect;

		while (interfaceSelect < 1 || interfaceSelect > 3)						//validation to make sure nothing over 3 or under 1 is typed 
		{
			cout << "please input a number between 1 and 3" << endl;
			cin >> interfaceSelect;
		}
		//start of interface select if 1 is pressed
		if (interfaceSelect == 1)												//next interface for selecting a map to load 
		{
			//map select interface 
			system("cls");
			cout << "map1.txt" << endl;
			cout << "map2.txt" << endl;
			cout << "map3.txt" << endl;
			cin >> mapSelect;

			loadMap(mapArray, mapSelect);										//plays loadMap function that loads the .txt file 

			mapLoaded = true;													//validation in case a map hasnt been loaded 								
		}
		//end of interface select if 1 is pressed
		//start of interface select if 2 is pressed
		else if (interfaceSelect == 2 && mapLoaded == true)
		{
			system("cls");
			outputMap(mapArray);												//outputs the map array using the outputMap function

			cout << endl;
			cout << "Do you want to pass the mountain?" << endl;				//Pass the mountain selection
			cout << "(1) Yes" << endl;
			cout << "(2) No" << endl;
			cin >> mountainPassSelect;

			if (mountainPassSelect == 1)
			{
				cout << "please input a starting location (0-8)" << endl;
				cin >> startingPoint;											//the co-ordinate to start at on the first column of the map

				while (startingPoint > 8 || startingPoint < 0)					//validation to make sure the user inputs a number within the array size
				{
					system("cls");
					cout << "please input a starting location (0-8)" << endl;
					cin >> startingPoint;
				}

				cout << mapArray[startingPoint][0] << ", ";						//outputs the users selected row

				currentRow = startingPoint;										//the current row should be the one the user selected to start

				for (int c = 1; c < mapSize; c++)								//plays the passMountain function to find the best route									
				{
					nextNumber = passMountain(currentRow, mapArray, c);
					currentRow = nextNumber;
					cout << mapArray[nextNumber][c] << ", ";					//displays each subsequent lowest number to get through the mountain
				}

				cout << endl;
				system("pause");
			}
		}
		//end of interface select if 2 is pressed
		else if (mapLoaded == false && interfaceSelect != 3)					//validation to make sure a map has been loaded before outputting the map
		{
			cout << "Please load a map first" << endl;
			system("pause");
		}
	}

	while (interfaceSelect != 3);												//ends the program if 3 is pressed on the interface screen
	{
		return 0;
	}


	system("pause");
}

void outputMap(int mapArray[mapSize][mapSize])
{
	for (int i = 0; i < mapSize; i++)
	{
		for (int k = 0; k < mapSize; k++)
		{
			cout << mapArray[i][k] << " ";										//outputs the map array 
		}
		cout << endl;
	}
}

int passMountain(int currentRow, int mapArray[mapSize][mapSize], int currentColumn)
{
	int yOneUp;												//the previously selected row +1 but one column over (this would actually be down on the map)
	int yOneUpVal;											//value of the previously selected row +1 but one column over (this would actually be down on the map)
	int ySamePos;											//the previously selected row but one column over
	int yOneDown;											//the previously selected row -1 but one column over (this would actually be up on the map)
	int ySamePosVal;										//value of the previously selected row but one column over
	int yOneDownVal;										//value of the previously selected row -1 but one column over (this would actually be up on the map)

	if (currentRow > mapSize - 2)										//if the user is on the final row there cant be a one up so it sets the one up
	{																	//value to be the same as the current 
		yOneUp = currentRow;
	}
	else
	{
		yOneUp = currentRow + 1;										//the value below would be a number 1 above on the array
	}
	yOneUpVal = mapArray[yOneUp][currentColumn];						//gets the value of the number that is 1 up and 1 row across from where the user is
																		//will be used to compare whether the value one up, one down and on the same row is smallest
	if (currentRow < 1)													//if the user is on the first row there cant be a one down, does the same as one up
	{
		yOneDown = currentRow;
	}
	else
	{
		yOneDown = currentRow - 1;										//the value above would be a number 1 below on the array
	}
	yOneDownVal = mapArray[yOneDown][currentColumn];					//does the same as one up except it is 1 down and 1 across from where the user is

	ySamePos = currentRow;
	ySamePosVal = mapArray[ySamePos][currentColumn];

	if (yOneUpVal == yOneDownVal || yOneUpVal == ySamePosVal)			//horrible ugly temporary fix botch job jesus help it
	{																	//just changes the yOneUpVal to be 1000 so it can never be equal 
		yOneUpVal = 1000;
	}

	if (yOneDownVal == yOneUpVal || yOneDownVal == ySamePosVal)			//and here with the yOneDownVal *vomits*
	{
		yOneDownVal = 1000;
	}


	if (yOneUpVal < yOneDownVal && yOneUpVal < ySamePosVal)				//this doesnt do well with numbers that are equal as when it gets to 
	{																	//row 8 the row up is being set to the same as ySamePos so they are equal
		currentRow = yOneUp;											//therefore it stays with the previous currentRow
	}																	//e.g. rowDown is > than same pos but same pos isnt lower than row up
	else if (yOneDownVal < yOneUpVal && yOneDownVal < ySamePosVal)		//as they have been set to the same so it sticks with the previous row
	{																	//and outputs nothing as each of the else ifs cant be true
		currentRow = yOneDown;											//disgusting botch job of a fix above and is probably buggy as it 
	}																	//wouldnt give the best outcome if predictive movement was implemented
	else if (ySamePosVal < yOneDownVal && ySamePosVal < yOneUpVal)
	{
		currentRow = ySamePos;
	}
	return(currentRow);
}

void loadMap(int mapArray[mapSize][mapSize], int mapSelect)
{
	if (mapSelect == 1)													//opens the selected map and inputs the data into the array, same for each if statement
	{
		ifstream infile("map1.txt");
		if (!infile)
		{
			cout << "error! Unable to open file" << endl;
		}
		else
		{
			for (int i = 0; i < mapSize; i++)
			{
				for (int k = 0; k < mapSize; k++)
				{
					infile >> mapArray[i][k];
				}
			}
		}
	}
	if (mapSelect == 2)
	{
		ifstream infile("map2.txt");
		if (!infile)
		{
			cout << "error! Unable to open file" << endl;
		}
		else
		{
			for (int i = 0; i < mapSize; i++)
			{
				for (int k = 0; k < mapSize; k++)
				{
					infile >> mapArray[i][k];
				}
			}
		}
	}
	if (mapSelect == 3)
	{
		ifstream infile("map3.txt");
		if (!infile)
		{
			cout << "error! Unable to open file" << endl;
		}
		else
		{
			for (int i = 0; i < mapSize; i++)
			{
				for (int k = 0; k < mapSize; k++)
				{
					infile >> mapArray[i][k];
				}
			}
		}
	}
}