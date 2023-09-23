﻿#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "Utils.h"

#include "PT-1-4.h"
#include "PT-2-4.h"

using namespace std;

const std::string TESTS_1_4_INPUT = "../tests_1_4_input.txt";
const std::string TESTS_2_4_INPUT = "../tests_2_4_input.txt";

const std::string TEST_FLAG = "-TEST";
const std::string CORRECT_FLAG = "-CORRECT";





void tests_1_4()
{
	ifstream inputFile(TESTS_1_4_INPUT);

	if (!inputFile.is_open())
	{
		print_cannot_open_file(TESTS_1_4_INPUT);
		return;
	}

	int testsMade = 0;
	int testsPassed = 0;
	bool isCorrectLine = false;

	string line;

	int currentSize;
	vector<int> currentVector;
	vector<int> correctVector;

	while (getline(inputFile, line))
	{
		if (line == TEST_FLAG)
		{
			++testsMade;
			isCorrectLine = false;
		}
		else if (line == CORRECT_FLAG)
		{
			isCorrectLine = true;
		}
		else
		{
			istringstream iss( line );

			if (!isCorrectLine)
			{
				currentVector.clear();

				int number;
				while (iss >> number)
				{
					currentVector.push_back(number);
				}

				print_processing_test(testsMade);
				print_input();
				print_vector(currentVector);

				currentVector = TASK_1_4::swap_to_closet_max(currentVector);

				print_output();
				print_vector(currentVector);
			}
			else
			{
				correctVector.clear();
				int number;
				while (iss >> number)
				{
					correctVector.push_back(number);
				}

				print_expected_output();
				print_vector(correctVector);

				if (currentVector == correctVector)
				{
					print_test_passed();
					++testsPassed;
				}
				else
				{
					print_test_failed();
				}
			}

		}
		
	}
	print_tests_result(testsMade, testsPassed);
	inputFile.close();
}

void tests_2_4()
{
	ifstream inputFile(TESTS_2_4_INPUT);

	if (!inputFile.is_open())
	{
		print_cannot_open_file(TESTS_2_4_INPUT);
		return;
	}

	int testsMade = 0;
	int testsPassed = 0;
	bool isCorrectLine = false;

	string line;

	int currentSize;
	vector<vector<int>> currentMatrix;
	vector<vector<int>> correctMatrix;

	while (getline(inputFile, line))
	{
		if (line == TEST_FLAG)
		{
			++testsMade;
			isCorrectLine = false;
			currentMatrix.clear();
		}
		else if (line == CORRECT_FLAG)
		{
			isCorrectLine = true;
			correctMatrix.clear();
		}
		else
		{
			vector<int> lineVector;
			lineVector.clear();

			istringstream iss(line);

			int number;
			while (iss >> number)
			{
				lineVector.push_back(number);
			}


			if (!isCorrectLine)
			{
				currentMatrix.push_back(lineVector);

				if (currentMatrix.size() == lineVector.size())
				{
					print_processing_test(testsMade);
					print_input();
					print_vector(currentMatrix);

					auto csMatrix = TASK_2_4::pack_to_CSMatrix_with_shift(currentMatrix);

					print_output();
					csMatrix->print();

					currentMatrix = csMatrix->to_vector();
					delete csMatrix;
				}
			}
			else
			{
				correctMatrix.push_back(lineVector);

				if (correctMatrix.size() == 3)
				{
					print_expected_output();
					print_vector(correctMatrix);

					if (currentMatrix == correctMatrix)
					{
						print_test_passed();
						++testsPassed;
					}
					else
					{
						print_test_failed();
					}
				}
			}
		}
	}
	print_tests_result(testsMade, testsPassed);
	inputFile.close();
}

//#define TEST_1_4
#define TEST_2_4

int main()
{
	print_owner();

#ifdef TEST_1_4
	tests_1_4();
#endif // TEST_1_4

#ifdef TEST_2_4
	tests_2_4();
#endif // TEST_2_4

	print_owner();
}