#pragma once
#include <iostream>
// dont use cout in any of the functions apart from PrintArray();
int ReplaceWithMinusOne(int array[4][6])
{
	int cluster = 0;
	int repeatCount = 1;
	int previousValue{ -1 };

	for (int row = 0; row < 4; row++)			// iterate through the rows
	{
		for (int col = 0; col < 6; col++)		// iterate through the columns 
		{
			if (array[row][col] == previousValue)		// if the value at array[row][col] = the previous value 
			{
				repeatCount++;							// increase the repeat counter 
			}
			else
			{
				previousValue = array[row][col];		// else previous value = the value at current array[row][col]

				repeatCount = 1;						// repeat count = 1 as we have just gotten to a new value and are seeing it for the first time 
			}

			if (repeatCount == 4)						// if a value is repeated 4 times
			{
											// increase cluster 

				for (int i = 0; i < repeatCount; i++)	
				{
					array[row][col - i] = -1;				// replace the value of the item at array[row][col] with -1

					cluster += 2;				// two points per number found 
				}

				repeatCount = 1;			//set repeat back to 1
			}

			
		}	

		repeatCount = 1;			// set repeat back to 1

	}

	std::cout << "Score is: " << cluster << std::endl;


	return 0;
}

// could not get FallDownAndReplace working

//void FallDownAndReplace(int array[4][6])
//{
//	for (int col = 0; col < 6; col++)
//	{
//		int writeRow = 3; // Start writing from the bottom of the column
//
//		// Shift values down
//
//		for (int row = 3; row >= 0; row--) 
//		{
//			if (array[row][col] != -1)
//			{
//				array[writeRow--][col] = array[row][col]; // Shift valid values down
//			}
//		}
//
//		// Fill remaining cells below the last written row with -1
//
//		while (writeRow >= 0)
//		{
//			array[writeRow--][col] = -1; // Fill with -1
//		}
//
//		int filledRows = 3 - writeRow; // Correctly count how many rows were filled with valid data
//
//
//		for (int i = 0; i < filledRows; i++)
//		{
//			array[i][col] = -2; // Fill with -2 at the top
//		}
//	}
//}


void PrintArray(int array[4][6])
{

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 6; col++)
		{
			std::cout << array[row][col] << " ";
		}

		std::cout << "" << std::endl;

	}

}