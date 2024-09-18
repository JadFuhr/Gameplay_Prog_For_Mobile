#pragma once
#include <iostream>
// dont use cout in any of the functions apart from PrintArray();
int ReplaceWithMinusOne(int array[4][6])
{
	int cluster = 0;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 6; col++)
		{
			
		}	

	}



	std::cout << cluster << std::endl;
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