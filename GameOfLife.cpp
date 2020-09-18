// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "GameOfLife.h"

using namespace std;



void drawLife() {
	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	cls(hStdout);
	srand(time(NULL));

	const int rows = 16;
	const int columns = 32;
	char field[rows][columns];

	int random_x = rand() % 32;
	int random_y = rand() % 32;

	cout << random_x << endl;
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			if (x == random_x && y == random_y)
			{
				int rand_life = rand() % 100 + 1;
				if (rand_life > 50)
				{
					cout << "*";
				}
				else {
					cout << "#";
				}
			}
			else {
				cout << "#";
			}
		}
		cout << "" << endl;
	}
}

const int NUM_SECONDS = 1;

void setInterval() {
	int count = 1;

	double time_counter = 0;

	clock_t this_time = clock();
	clock_t last_time = this_time;

	printf("Gran = %ld\n", NUM_SECONDS * CLOCKS_PER_SEC);

	while (true)
	{
		this_time = clock();

		time_counter += (double)(this_time - last_time);

		last_time = this_time;

		if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
		{
			time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
			printf("%d\n", count);
			count++;
			drawLife();
		}
		// printf("DebugTime = %f\n", time_counter);
	}
}

int main1()
{
	setInterval();
	return 0;
}

int main(int argc, char* argv[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	cin.get();
	return 0;
}


// [4][4] [5][4] [6][4] 
// [4][5] [5][5] [6][5]
// [4][6] [5][6] [6][6] 


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file



