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
				cluster++;								// increase cluster 

				for (int i = 0; i < repeatCount; i++)	
				{
					array[row][col - i] = -1;				// replace the value of the item at array[row][col] with -1
				}

				repeatCount = 1;			//set repeat back to 1
			}

			
		}	

		repeatCount = 1;			// set repeat back to 1

	}

	std::cout << "The largest cluster is: " << cluster << " items" << std::endl;


	return 0;
}
void FallDownAndReplace(int array[4][6])
{

}
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