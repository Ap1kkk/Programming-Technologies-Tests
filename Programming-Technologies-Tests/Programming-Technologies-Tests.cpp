#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "../../../Users/Egor/source/repos/Programming-Technologies-1-4/Programming-Technologies/PT-1-4.h"

using namespace std;

const std::string TESTS_1_4_INPUT = "../tests_1_4_input.txt";
const std::string TESTS_1_4_OUTPUT = "tests_1_4_output.txt";

const std::string TEST_FLAG = "-TEST";
const std::string CORRECT_FLAG = "-CORRECT";

void print_vector(vector<int> vect)
{
	for (size_t i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << " ";
	}
	cout << "\n";
}

#define TEST_1_4

void tests_1_4()
{
	ifstream inputFile(TESTS_1_4_INPUT);

	if (!inputFile.is_open())
	{
		cout << "ERROR:  Cannot open file: " << TESTS_1_4_INPUT << "\n";
		return;
	}

	int testsMade = 0;
	int testsPassed = 0;
	bool isCorrectLine = false;

	string line;
	bool isSizeGot = false;

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

				cout << "------------------------------------------\n";
				cout << "Processing TEST: " << (testsMade) << "\n";

				cout << "\n>> Input: \n";
				print_vector(currentVector);

				currentVector = swap_to_closet_max(currentVector);

				cout << "\n>> Output: \n";
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

				cout << "\n>> Expected output: \n";
				print_vector(currentVector);

				if (currentVector == correctVector)
				{
					cout << "\nTEST PASSED\n";
					++testsPassed;
				}
				else
				{
					cout << "\nTEST FAILED\n";
				}

				cout << "------------------------------------------\n";
			}

		}
		
	}

	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	cout << "Tests made: " << testsMade << "\n";
	cout << "Tests passed: " << testsPassed << "\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	inputFile.close();
}


int main()
{
    cout << ">>>>>> TEST STAND BY AP1KKK <<<<<<\n";

#ifdef TEST_1_4
	tests_1_4();
#endif // TEST_1_4


}