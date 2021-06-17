/* bombMainMenu.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bombHeader.h"

void mainMenu(player_t* playerOne, player_t* playerTwo, bomb_t* currentBomb, list_t* myList)
{
    int choice;

    /* gameSaved acts as "boolean" to stop the game when saved, 0 = continue, 1 = stop*/
    int gameSaved = 0;

    /* printing out main menu */
    printf ("\n\t\t\t! H O T  B O M B !\n");
    printf ("\n\t### MAIN MENU ###\n\n");

    printf ("\t1. Start A Game\n");
    printf ("\t2. View / Change Settings\n");
    printf ("\t3. Load A Game From A File\n");
    printf ("\t4. Exit\n");

    printf ("\n\tEnter a task to perform: ");
    scanf ("%d", &choice);
	printf ("\n");

    while (choice < 1 || choice > 4)
    {
        printf ("Invalid Input, enter a number between 1 and 4.\n");

        printf ("\n\tEnter a task to perform: ");
        scanf ("%d", &choice);
	    printf ("\n");
    }

    /* processing user input */
    if (choice == 1)
    {
        printf ("Starting a new game...\n");

        startGame(playerOne, playerTwo, currentBomb, &gameSaved, myList);

        /* reset players and bomb health after the game ends */
        setHealth(playerOne, playerTwo, currentBomb);
        
        printf ("\nGoing back to main menu...\n");
        mainMenu(playerOne, playerTwo, currentBomb, myList);
    }

    else if (choice == 2)
    {
        printf ("Opening setttings...\n\n");

        displaySettings(playerOne, playerTwo, currentBomb, myList);
    }

    else if (choice == 3)
    {
        printf ("Loading a game...\n");
        
        char fileName[128];
        printf ("Enter the name of your existing save file to load from (max. 127 characters.): ");
        scanf ("%127s", fileName);
        
        FILE* loadFile = fopen (fileName, "r");

        readSettings (loadFile, playerOne, playerTwo, currentBomb);

        startGame(playerOne, playerTwo, currentBomb, &gameSaved, myList);
        fclose (loadFile);
        
        mainMenu(playerOne, playerTwo, currentBomb, myList);
    }

	else if (choice == 4)
    {
        char exitChoice;
        printf ("Do you really wish to quit? (Y/N): ");
        scanf (" %c", &exitChoice);
        exitChoice = toupper(exitChoice);

        while (exitChoice != 'Y' && exitChoice != 'N')
        {
            printf ("Invalid Input!\n\n");
            printf ("Do you really wish to quit? (Y/N): ");
            scanf (" %c", &exitChoice);
            exitChoice = toupper(exitChoice);
        }

        if (exitChoice == 'N')
        {
            mainMenu(playerOne, playerTwo, currentBomb, myList);
        }

        else if (exitChoice == 'Y')
        {
            printf ("\n\tThank You, and stay safe!\n\n");
        }
    }
}