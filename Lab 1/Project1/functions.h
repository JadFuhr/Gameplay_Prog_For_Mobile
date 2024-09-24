#pragma once


#pragma once
#include <iostream>
using namespace std;

bool isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

int Reversed(int testNumber)
{
	int reversed = 0; // Initialize the reversed number

	while (testNumber != 0)
	{
		int lastDigit = testNumber % 10; // Get the last digit

		reversed = reversed * 10 + lastDigit; // add the last digit to reversed

		testNumber /= 10; // Remove the last digit from the original number

	}

	return reversed;

}
bool isAPalindrome(int testNumber)
{

	if (testNumber < 0 || (testNumber % 10 == 0 && testNumber != 0))			// check for negative and multiples of 10 
	{
		return false; // Not a palindrome
	}

	int reversed = 0; // reversed number
	int original = testNumber; // the original 

	// Reverse the number

	while (testNumber > 0)
	{
		reversed = reversed * 10 + testNumber % 10; // Get the last digit and build the reversed number

		testNumber /= 10; // Remove the last digit from the original number

	}

	// Compare the reversed with original

	if (reversed == original) // Return true if they are the same
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool isAPrimeNumber(int numbertoTest)
{

	// Check for numbers less than 2

	if (numbertoTest < 2) 
	{
		return false;
	}

	// Check for factors from 2 to the square root of num

	for (int i = 2; i * i <= numbertoTest; ++i) 
	{
		if (numbertoTest % i == 0) 
		{
			return false; // Not prime if divisible by i
		}
	}
	return true; // Prime if no factors were found

}

int input5CharsConvertToInt()
{
	int returnInt = 0; 
	char inputChar;

	for (int i = 0; i < 5; i++)
	{
		std::cin >> inputChar; 

		// Check if the character is a digit

		if (inputChar < '0' || inputChar > '9')
		{
			return 0; // Return 0 if any character is not a digit
		}

		// Convert character to integer 

		returnInt = returnInt * 10 + (inputChar - '0');				// subtract the ASCII value of '0' from any digit character you effectively get the integer
																	// returnInt * 10 shifts it up a decimal place
	}

	return returnInt;
}
int convertBinarytoDecimal(int binaryNumber)
{
	return 0;
}
void drawRightAngledTriangle()
{
	int rows = 4; // Number of rows to print

	for (int i = 1; i <= rows; ++i)
	{
		// Inner loop for printing 'A'

		for (int j = 1; j <= i; ++j)
		{
			std::cout << "A"; // Print 'A'
		}
		std::cout << std::endl; // Move to the next line after each row
	}
}
void drawIsocelesTriangle()
{
	int rows = 4; // Number of rows in the upper part

	// Outer loop for each row

	for (int i = 1; i <= 7; ++i)
	{
		int numA; // Variable to hold the number of 'A's to print

		// Determine the number of 'A's to print based on the row

		if (i <= rows)
		{
			numA = i; // For the first 4 rows
		}
		else
		{
			numA = 8 - i; // For the last 3 rows
		}

		// Inner loop to print 'A' numA times

		for (int j = 0; j < numA; ++j)
		{
			std::cout << "A"; // Print 'A'
		}
		std::cout << std::endl; // Move to the next line after each row
	}
}
void drawIsocelesTriangle2()
{
	int rows = 4; // Number of rows in the top half

	// Outer loop for the total number of rows

	for (int i = 1; i <= 2 * rows - 1; ++i)
	{
		// Determine the number of 'A's to print

		int numA = (i <= rows) ? i : (2 * rows - i);

		// Inner loop to print 'A' numA times

		for (int j = 0; j < numA; ++j) 
		{
			std::cout << "A"; // Print 'A'
		}
		std::cout << std::endl; // Move to the next line after each row
	}
}

int find(int size, int arr[], int toFind)
{
	return -1;
}
int find2ndLargest(int size, int arr[])
{
	if (size < 2)
	{
		return -1; // Not enough elements for a second largest
	}

	int largest = -1;    // Initialize largest to -1
	int secondLargest = -1; // Initialize second largest to -1

	for (int i = 0; i < size; ++i)
	{
		if (arr[i] > largest)
		{
			// Update second largest before largest

			secondLargest = largest;

			largest = arr[i]; // Update largest
		}
		else if (arr[i] > secondLargest && arr[i] < largest)
		{
			secondLargest = arr[i]; // Update second largest
		}
	}

	return secondLargest; // Return second largest, or -1 if it wasn't updated
}
void copyArraytoArray(int size, int arr1[], int arr2[])
{
	for (int i = 0; i < size; ++i)
	{
		arr2[i] = arr1[i]; // Copying element
	};
}
bool insertElement(int& size, int& count, int arr[], int elementToInsert, int insertIndex)
{

	return false;
}
bool deleteElement(int& size, int& count, int arr[], int deleteIndex)
{

	return true;
}
int frequencyCount(int size, int arr[], int value)
{

	return 0;
}
int countDuplicates(int size, int arr[])
{

	return 0;
	}
void reverse(int size, int arr[])
{
	return;
}
int rotateLeft(int size, int arr[])
{
	return -1;
}
bool twoMovies(int flightLength, int movieLengths[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			// If the sum of two different movies equals the flight length

			if (movieLengths[i] + movieLengths[j] == flightLength)
			{
				return true; // Found a valid pair
			}
		}
	}
	return false; // No valid pair found
}
int wordCounter(int size, char characters[])
{
	int wordCount = 0;   // To hold the total number of words
	bool inWord = false; // To track if we are currently inside a word

	for (int i = 0; i < size; ++i) 
	{
		// Check if the current character is an alphabetic character

		if ((characters[i] >= 'A' && characters[i] <= 'Z') || (characters[i] >= 'a' && characters[i] <= 'z'))
		{
			if (!inWord)
			{
				// found a new word

				inWord = true;
				wordCount++;
			}
		}
		else
		{
			// If we encounter a space we are not in a word

			inWord = false;
		}
	}

	return wordCount;
}