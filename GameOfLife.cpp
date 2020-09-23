// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL.h>
#include "GameOfLife.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
		(TCHAR)' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coordScreen,     // Coordinates of first cell 
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coordScreen,      // Coordinates of first cell 
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
}


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

//int main()
//{
//	setInterval();
//	return 0;
//}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP("Images/background.bmp");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			//Update the surface
			SDL_UpdateWindowSurface(gWindow);
			//Wait two seconds
			SDL_Delay(2000);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}


