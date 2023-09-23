#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

enum class ConsoleColor
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};

void print_vector(vector<int> vect)
{
	for (size_t i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << " ";
	}
	cout << "\n";
}

void print_vector(vector<vector<int>> vect)
{
	for (size_t i = 0; i < vect.size(); i++)
	{
		string line = "";
		for (size_t j = 0; j < vect[0].size(); j++)
		{
			line += to_string(vect[i][j]) + " ";
		}
		cout << line << "\n";
	}
}

void print_owner()
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::LIGHT_RED);
	cout << ">>>>>> TESTS MADE BY AP1KKK <<<<<<\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}

void print_processing_test(int testIndex)
{
	cout << "------------------------------------------\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::LIGHT_YELLOW);
	cout << "Processing TEST: " << (testIndex) << "\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}

void print_input()
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::CYAN);
	cout << "\n>> Input: \n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}

void print_output()
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::CYAN);
	cout << "\n>> Output: \n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}

void print_expected_output()
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::CYAN);
	cout << "\n>> Expected output: \n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}

void print_test_passed()
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::GREEN);
	cout << "\nTEST PASSED\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
	cout << "------------------------------------------\n";
}

void print_test_failed()
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::RED);
	cout << "\nTEST FAILED\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
	cout << "------------------------------------------\n";
}

void print_tests_result(int testsMade, int testsPassed)
{
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::LIGHT_BLUE);
	cout << "Tests made: " << testsMade << "\n";
	ConsoleColor testPassedColor;
	if (testsMade == testsPassed)
	{
		testPassedColor = ConsoleColor::LIGHT_GREEN;
	}
	else
	{
		testPassedColor = ConsoleColor::LIGHT_RED;
	}
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)testPassedColor);
	cout << "Tests passed: " << testsPassed << "\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
}

void print_cannot_open_file(string filename)
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::RED);
	cout << "ERROR:  Cannot open file: " << filename << "\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}

void print_error(string errorMessage)
{
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::RED);
	cout << "ERROR: " << errorMessage << "\n";
	SetConsoleTextAttribute(CONSOLE_HANDLE, (int)ConsoleColor::WHITE);
}
