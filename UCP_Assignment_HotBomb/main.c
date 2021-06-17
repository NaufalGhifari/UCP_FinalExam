/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bombHeader.h"
#include "linkedList.h"

int main(int argc, char* argv[])
{
	/* prevent the program to run if argc is not 2 */
	if (argc < 2 || argc > 2)
	{
		printf ("Command line argument error!\n");
		return 0;
	}

	/* linked list for the save feature */
	list_t* saveList = createList ();

	bomb_t* bomb = createBomb();
	player_t* player1 = createPlayers();
	player_t* player2 = createPlayers();

	FILE* settingsFile = fopen(argv[1], "r");

	/* setting the value for each players from settings.txt */
	readSettings (settingsFile, player1, player2, bomb);

	fclose(settingsFile);

	/* open settings.txt to be written to */
	FILE* newSettingsFile = fopen(argv[1], "w");

	mainMenu(player1, player2, bomb, saveList);

	/* re write values to settings.txt */
	setHealth (player1, player2, bomb);
	writeNewSettings (newSettingsFile, player1, player2, bomb);
	fclose (newSettingsFile);

	/* cleanups */
	freeList(saveList);
	free (saveList);
	
	free (bomb);
	free (player1);
	free (player2);

	return 0;
}