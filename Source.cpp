#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int mapSize = 9;

//ifstream infile("/*name of the file for the map*/") 
// if( !infile) 
// cout error
// count unable to open file 
// else 
// nested for loop with values i and j that increment as long as i < map array size 
// infile >> mapArray[i][j]

void loadMap(int mapArray[mapSize][mapSize], int mapSelect);


int main()
{
	//variables
	int mapArray[mapSize][mapSize];							//array of mapsize by mapsize
	int mapSelect;											//which map has been selected 
	int interfaceSelect;									//which number on the interface has been selected
	int lowestNumber;										//value of the lowest number, used to determine whether the number on the current column is 
															//higher or lower than any other row in the rest of the column
	int lowestNumberPosition;								// the position in the row of the array that the lowest number is on, used to determine 
															//which rows on the next column are possible to go to
	int mountainPassSelect;									//does the user want to pass the mountain?
	int currentRow;											//the current row that the mountain pass section has selected to be the lowest value, used to 
															//determine what is one up, one down and the same as the row that was previously selected
	int currentColumn;										//the current column that the mountain pass has to go through
	int yOneUp;												//the previously selected row +1 but one column over (this would actually be down on the map)
	int ySamePos;											//the previously selected row but one column over
	int yOneDown;											//the previously selected row -1 but one column over (this would actually be up on the map)
	int yOneUpVal;											//value of the previously selected row +1 but one column over (this would actually be down on the map)
	int ySamePosVal;										//value of the previously selected row but one column over
	int yOneDownVal;										//value of the previously selected row -1 but one column over (this would actually be up on the map)
	int startingPoint;										//where on the map to start
	int routeOneSum;										//the sum of all lowest values on the current lowest route. If two starting values are the same
															//used to compare the two routes to see which one is quicker by seeing which sum is lower
	int routeTwoSum;										//the sum of all lowest values on the route that has an equal starting value to the current lowest
	bool mapLoaded = false;									//determines whether a map has been loaded so if the user asks a map to be displayed without
															//one loaded it will ask them to load one first
	do
	{
		//main interface
		system("cls");														//main interface used to select whether to open the map file loader
		cout << "Choose a map file and then display the map" << endl;		//display the current map that has been loaded or exit the program
		cout << "(1) Choose map file" << endl;
		cout << "(2) Display current map file" << endl;
		cout << "(3) Exit the program" << endl;
		cin >> interfaceSelect;

		while (interfaceSelect < 1 || interfaceSelect > 3)					//validation to make sure nothing over 3 or under 1 is typed 
		{
			cout << "please input a number between 1 and 3" << endl;
			cin >> interfaceSelect;
		}
		//start of interface select if 1 is pressed
		if (interfaceSelect == 1)											//next interface for selecting a map to load 
		{
			//map select interface 
			system("cls");
			cout << "map1.txt" << endl;
			cout << "map2.txt" << endl;
			cout << "map3.txt" << endl;
			cin >> mapSelect;

			loadMap(mapArray, mapSelect);

			mapLoaded = true;
		}
		//end of interface select if 1 is pressed
		//start of interface select if 2 is pressed
		else if (interfaceSelect == 2 && mapLoaded == true)
		{
			system("cls");
			for (int i = 0; i < mapSize; i++)
			{
				for (int k = 0; k < mapSize; k++)
				{
					cout << mapArray[i][k] << " ";
				}
				cout << endl;
			}

			cout << endl;
			cout << "Do you want to pass the mountain?" << endl;							//Pass the mountain selection
			cout << "(1) Yes" << endl;
			cout << "(2) No" << endl;
			cin >> mountainPassSelect;

			if (mountainPassSelect == 1)
			{
				cout << "please input a starting location (0-8)" << endl;
				cin >> startingPoint;

				while (startingPoint > 8 || startingPoint < 0)
				{
					system("cls");
					cout << "please input a starting location (0-8)" << endl;
					cin >> startingPoint;
				}
				
				cout << mapArray[startingPoint][0] << ", ";								//outputs the users selected row

				currentColumn = 1;														//the current column should be the second one 

				currentRow = startingPoint;												//the current row should be the one the user selected to start

				for (int c = 1; c < mapSize; c++)								//column												
				{
					if (currentRow > mapSize - 2)
					{
						yOneUp = currentRow;
					}
					else
					{
						yOneUp = currentRow + 1;
					}
					yOneUpVal = mapArray[yOneUp][currentColumn];

					if (currentRow < 1)
					{
						yOneDown = currentRow;
					}
					else
					{
						yOneDown = currentRow - 1;
					}
					yOneDownVal = mapArray[yOneDown][currentColumn];

					ySamePos = currentRow;
					ySamePosVal = mapArray[ySamePos][currentColumn];

					if (yOneUpVal == yOneDownVal || yOneUpVal == ySamePosVal)			//horrible ugly temporary fix botch job jesus help it
					{																	//just changes the yOneUpVal to be 1000 so it cant ever be equal 
						yOneUpVal = 1000;
					}

					if (yOneDownVal == yOneUpVal || yOneDownVal == ySamePosVal)			//and here with the yOneDownVal *vomits*
					{
						yOneDownVal = 1000;
					}


					if (yOneUpVal < yOneDownVal && yOneUpVal < ySamePosVal)				//this doesnt do well with numbers that are equal as when it gets to 
					{																	//row 8 the row up is being set to the same as ySamePos so they are equal
						lowestNumberPosition = yOneUp;									//therefore it stays with the previous lowestNumberPosition and says "5"
					}																	//e.g. rowDown is > than same pos but same pos isnt lower than row up
					else if (yOneDownVal < yOneUpVal && yOneDownVal < ySamePosVal)		//as they have been set to the same so it sticks with the previous row
					{																	//and outputs a 5 as each of the else ifs cant be true
						lowestNumberPosition = yOneDown;								//disgusting botch job of a fix above but is probably buggy as it 
					}																	//wouldnt give the best outcome if predictive movement was implemented
					else if (ySamePosVal < yOneDownVal && ySamePosVal < yOneUpVal)
					{
						lowestNumberPosition = ySamePos;
					}
					else
					{
						cout << "5";													//testing
					}

					cout << mapArray[lowestNumberPosition][c] << ", ";					//Display the numbers for passing the mountain 
					currentColumn += 1;
					currentRow = lowestNumberPosition;									//half an hour of frustration went into this one line
				}
				cout << endl;
				system("pause");
			}
		}
		//end of interface select if 2 is pressed
		else if (mapLoaded == false && interfaceSelect != 3)
		{
			cout << "Please load a map first" << endl;
			system("pause");
		}
	}
	//ends the program if 3 is pressed on the interface screen
	while (interfaceSelect != 3);
	{
		return 0;
	}


	system("pause");
}


void loadMap(int mapArray[mapSize][mapSize], int mapSelect)
{
	if (mapSelect == 1)
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