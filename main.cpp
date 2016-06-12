#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "game.h"
#include "entity.h"

using namespace sf;
using namespace std;

int GetInput()
{
	int choice;
	cin >> choice;
	return choice;
}

void DisplayMainMenu()
{
	cout << "Main Menu\n";
	cout << "Please make your selection\n";
	cout << "1 - Start game\n";
	cout << "2 - Options\n";
	cout << "3 - Quit\n";
	cout << "Selection: ";
}

void DisplayOptionsMenu()
{
	cout << "Options Menu\n";
	cout << "Please make your selection\n";
	cout << "1 - Difficulty\n";
	cout << "2 - Sound\n";
	cout << "3 - Back\n";
	cout << "Selection: ";
}

void Options()
{
	int choice = 0;
	do
	{
		system("cls");
		DisplayOptionsMenu();
		choice = GetInput();
		switch (choice)
		{
		case 1:
			cout << "difficulty stuff";
			break;
		case 2:
			cout << "sound stuff";
			break;
		case 3:
			break;
		default:
			break;
		}
	} while (choice != 3);
}

int main()
{
	Game game;
	game.menuChoice();
	/*
	int choice = 0;
	do
	{
		system("cls");
		DisplayMainMenu();
		choice = GetInput();
		switch (choice) {
		case 1:
			cout << "Pew pew!\n";
			break;
		case 2:
			Options();
			break;
		case 3:
			cout << "Goodbye!";
			break;

		default:
			break;
		}
	} while (choice != 3);
	system("PAUSE");*/
	return 0;
}
