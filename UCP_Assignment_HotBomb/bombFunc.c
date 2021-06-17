/* bombFunc.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bombHeader.h"

/* functions that creates various structs */

player_t* createPlayers()
{
	player_t* newPlayer = malloc(1*sizeof(player_t));
	return newPlayer;
}

bomb_t* createBomb()
{
	bomb_t* newBomb = malloc(1*sizeof(player_t));
	return newBomb;
}

move_t* createMove()
{
    move_t* newMove = calloc(1, sizeof(move_t));
    return newMove;
}

/* reads the settings file line by line, and assigns values for the structs, also used for loading a game */
void readSettings (FILE* myFile, player_t* playerOne, player_t* playerTwo, bomb_t* currentBomb)
{
	char player1Name[128] = "playerOneName";
    char player1HP[20] = "playerOneHealth";
    char player1MaxHP[20] = "playerOneMaxHealth";
    char player1SP[20] = "playerOneSpecial";
    char player1Counter[30] = "playerOneCounter";

    char player2Name[128] = "playerTwoName";
    char player2HP[20] = "playerTwoHealth";
    char player2MaxHP[20] = "playerTwoMaxHealth";
    char player2SP[20] = "playerTwoSpecial";
    char player2Counter[30] = "TwoCount";

    char bombHP[20] = "bombHealth";
    char bombMaxHP[20] = "bombMaxHealth";
    char bombDmg[20] = "bombDamage";
    char bombNormalDmg[20] = "bombNormalDamage";

    for (int i = 0; i < 14; i++)
    {
        char thisLine[50];
        fscanf (myFile, "%s\n", thisLine);

        if (strstr(thisLine, player1Name))
        {
            sscanf (thisLine, "playerOneName=%127s\n", playerOne->name);
        }

        else if (strstr(thisLine, player2Name))
        {
            sscanf (thisLine, "playerTwoName=%127s\n", playerTwo->name);
        }

        else if (strstr(thisLine, player1HP))
        {
            sscanf(thisLine, "playerOneHealth=%2d\n", &playerOne->health);
        }

        else if (strstr(thisLine, player1MaxHP))
        {
            sscanf(thisLine, "playerOneMaxHealth=%2d\n", &playerOne->maxHealth);
        }

        else if (strstr(thisLine, player2HP))
        {
            sscanf(thisLine, "playerTwoHealth=%2d\n", &playerTwo->health);
        }

        else if (strstr(thisLine, player2MaxHP))
        {
            sscanf(thisLine, "playerTwoMaxHealth=%2d\n", &playerTwo->maxHealth);
        }

        else if (strstr(thisLine, bombHP))
        {
            sscanf(thisLine, "bombHealth=%2d\n", &currentBomb->health);
        }

        else if (strstr(thisLine, bombMaxHP))
        {
            sscanf(thisLine, "bombMaxHealth=%2d\n", &currentBomb->maxHealth);
        }

        else if (strstr(thisLine, bombDmg))
        {
            sscanf(thisLine, "bombDamage=%2d\n", &currentBomb->damage);
        }

        else if (strstr(thisLine, bombNormalDmg))
        {
            sscanf(thisLine, "bombNormalDamage=%2d\n", &currentBomb->normalDamage);
        }

        else if (strstr(thisLine, player1SP))
    	{
            sscanf(thisLine, "playerOneSpecial=%9s\n", playerOne->specialMove);
        }
        
        else if (strstr(thisLine, player1Counter)) 
    	{
            sscanf(thisLine, "playerOneCounter=%d\n", &playerOne->specialCounter);
        }

        else if (strstr(thisLine, player2SP))
        {
            sscanf(thisLine, "playerTwoSpecial=%9s\n", playerTwo->specialMove);
        }

        else if (strstr(thisLine, player2Counter)) 
    	{
            sscanf(thisLine, "playerTwoCounter=%d\n", &playerTwo->specialCounter);
        }
        
		else
        {
            printf ("A problem occured when reading settings value:\n");
            printf ("%s\n\n", thisLine);
        }
    }
}

/* prints the settings for the user, can call changeSettings()*/
void displaySettings (player_t* playerOne, player_t* playerTwo, bomb_t* bomb, list_t* myList)
{
	printf ("Player 1 Name: %s\n", playerOne->name);
	printf ("Player 1 Max Health: %d\n", playerOne->maxHealth);
	printf ("Player 1 Special: %s\n\n", playerOne->specialMove);

	printf ("Player 2 Name: %s\n", playerTwo->name);
	printf ("Player 2 Max Health: %d\n", playerTwo->maxHealth);
	printf ("Player 2 Special: %s\n\n", playerTwo->specialMove);

	printf ("Bomb Max Health: %d\n", bomb->maxHealth);
	printf ("Bomb Damage: %d\n", bomb->normalDamage);

    #ifdef DEBUG

    printf ("Player 1 Actual Health: %d\n", playerOne->health);
    printf ("Player 2 Actual Health: %d\n", playerTwo->health);
    printf ("Bomb Actual Health: %d\n", bomb->health);
    printf ("Bomb Actual Damage: %d\n", bomb->damage);
    printf ("Player 1 Counter: %d\n", playerOne->specialCounter);
    printf ("Player 2 Counter: %d\n", playerTwo->specialCounter);

    #endif

	char input;
    printf ("Do you wish to change anything? (Y/N): ");
    scanf (" %c", &input);
    input = toupper(input);

    #ifdef DEBUG
    printf ("input = %c\n", input);
    #endif

	while (input != 'Y' && input != 'N')
    {
    	printf ("Invalid Input!\n\n");

        printf ("Do you wish to change anything? (Y/N): ");
        scanf (" %c", &input);
        input = toupper(input);
    }

    if (input == 'Y')
	{ 
        changeSettings(playerOne, playerTwo, bomb, myList);
    } 

    else if (input == 'N')
    {
    	printf ("Going back to Main Menu...\n\n");
        mainMenu(playerOne, playerTwo, bomb, myList);
    }
}

/* changes the settings by changing the value for the structs */
void changeSettings(player_t* playerOne, player_t* playerTwo, bomb_t* bomb, list_t* myList)
{
    printf ("\n\t### Change Settings ###\n\n");

	printf ("1. Player 1's name (currently %s)\n", playerOne->name);
    printf ("2. Player 1's Health (currently %d)\n", playerOne->maxHealth);
    printf ("3. Player 1 special ability (currently %s)\n\n", playerOne->specialMove);

    printf ("4. Player 2's name (currently %s)\n", playerTwo->name);
    printf ("5. Player 2's Health (currently %d)\n", playerTwo->maxHealth);
    printf ("6. Player 2's special ability (currently %s)\n\n", playerTwo->specialMove);

    printf ("7. Bomb's health (currently %d)\n", bomb->maxHealth);
    printf ("8. Bomb's Damage to Players (currently %d)\n\n", bomb->normalDamage);

    printf ("9. Go to Main Menu\n");
        
    int choice, newValue;
    printf ("\n\tEnter a task number to change its value: ");
    scanf ("%d", &choice);
	printf ("\n");

    while (choice < 1 || choice > 9)
    {
        printf ("Invalid Input, enter a number between 1 and 5.\n");

        printf ("\n\tEnter a task number to change its value: ");
        scanf ("%d", &choice);
	    printf ("\n");
    }
        
    if (choice == 1)
    {
        printf ("Enter a new name for player 1: ");
        scanf ("%127s", playerOne->name);
        printf ("Settings changed successfully...\n\n");
    }

    else if (choice == 2)
    {
        printf ("Enter new value for Player 1's Health (between 1 and 99): ");
        scanf ("%d", &newValue);

        while (newValue < 1 || newValue > 99)
        {
            printf ("Invalid Value, enter a number between 1 and 99.\n");

            printf ("\n\tEnter a new value: ");
            scanf ("%d", &newValue);
	        printf ("\n");
        }

        playerOne->maxHealth = newValue;
        printf ("Settings changed successfully...\n\n");
    }

	else if (choice == 3)
	{
		char newSpec[10];
		printf ("Enter a new special ability for player 1: ");
		scanf ("%9s", newSpec);

		for (int i = 0; i < 9; i++)
		{
			if (newSpec[i] >= 'a' && newSpec[i] <= 'z')
			{
				newSpec[i] = newSpec[i] - 32;
			}
		}

		#ifdef DEBUG
		printf ("newSpec: %s\n", newSpec);
		#endif

		if (strcmp(newSpec, "RESET") == 0)
		{
			strcpy (playerOne->specialMove, "RESET");
		}

		else if (strcmp(newSpec, "DOUBLE") == 0)
		{
			strcpy (playerOne->specialMove, "DOUBLE");
		}

		else if (strcmp(newSpec, "HEAL") == 0)
		{
			strcpy (playerOne->specialMove, "HEAL");
		}

		else if (strcmp(newSpec, "SKIP") == 0)
		{
			strcpy (playerOne->specialMove, "SKIP");
		}
			
		else 
		{
			printf ("\nERROR: INVALID SPECIAL ABILITY.\n\n");
		}

		#ifdef DEBUG
		printf ("p1SP: %s\n", playerOne->specialMove);
		#endif

		printf ("Settings changed successfully...\n\n");
	}

    else if (choice == 4)
    {
        printf ("Enter a new name for player 2: ");
        scanf ("%127s", playerTwo->name);
        printf ("Settings changed successfully...\n\n");
    }

    else if (choice == 5)
    {
        printf ("Enter new value for Player 2's Health (between 1 and 99): ");
        scanf ("%d", &newValue);

        while (newValue < 1 || newValue > 99)
        {
            printf ("Invalid Value, enter a number between 1 and 99.\n");

            printf ("\n\tEnter a new value: ");
            scanf ("%d", &newValue);
	        printf ("\n");
        }

        playerTwo->maxHealth = newValue;
        printf ("Settings changed successfully...\n\n");
    }

	else if (choice == 6)
	{
		char newSpec[10];
		printf ("Enter a new special ability for player 2: ");
		scanf ("%9s", newSpec);

		for (int i = 0; i < 9; i++)
		{
			if (newSpec[i] >= 'a' && newSpec[i] <= 'z')
			{
				newSpec[i] = newSpec[i] - 32;
			}
		}

		#ifdef DEBUG
		printf ("newSpec: %s\n", newSpec);
		#endif

		if (strcmp(newSpec, "RESET") == 0)
		{
			strcpy (playerTwo->specialMove, "RESET");
		}

		else if (strcmp(newSpec, "DOUBLE") == 0)
		{
			strcpy (playerTwo->specialMove, "DOUBLE");
		}

		else if (strcmp(newSpec, "HEAL") == 0)
		{
			strcpy (playerTwo->specialMove, "HEAL");
		}

		else if (strcmp(newSpec, "SKIP") == 0)
		{
			strcpy (playerTwo->specialMove, "SKIP");
		}
			
		else 
		{
			printf ("\nERROR: INVALID SPECIAL ABILITY.\n\n");
		}

		#ifdef DEBUG
		printf ("p1SP: %s\n", playerTwo->specialMove);
		#endif

		printf ("Settings changed successfully...\n\n");
	}

    else if (choice == 7)
    {
        printf ("Enter new value for Bomb's Time to Detonate (between 1 and 99): ");
        scanf ("%d", &newValue);

        while (newValue < 1 || newValue > 99)
        {
        	printf ("Invalid Value, enter a number between 1 and 99.\n");

        	printf ("\n\tEnter a new value: ");
        	scanf ("%d", &newValue);
	    	printf ("\n");
        }

        bomb->maxHealth = newValue;
        printf ("Settings changed successfully...\n\n");
    }

	else if (choice == 8)
	{
		printf ("Enter new value for Bomb's Damage to Players (between 1 and 99): ");
		scanf ("%d", &newValue);

		while (newValue < 1 || newValue > 99)
		{
			printf ("Invalid Value, enter a number between 1 and 99.\n");

			printf ("\n\tEnter a new value: ");
			scanf ("%d", &newValue);
			printf ("\n");
        }
		bomb->normalDamage = newValue;
		printf ("Settings changed successfully...\n\n");
	}

	else if (choice == 9)
	{
		printf ("Going back to MainMenu...\n");
	}

    displaySettings(playerOne, playerTwo, bomb, myList);

}

/* takes a file as parameter and then print the settinsg to the file (opens the file provided by the user in the command line arg) */
void writeNewSettings(FILE* newFile, player_t* playerOne, player_t* playerTwo, bomb_t* bomb)
{
	fprintf (newFile, "playerOneName=%s\n", playerOne->name);
    fprintf (newFile, "playerOneMaxHealth=%d\n", playerOne->maxHealth);
    fprintf (newFile, "playerOneHealth=%d\n", playerOne->health);
    fprintf (newFile, "playerOneSpecial=%s\n", playerOne->specialMove);
    fprintf (newFile, "playerOneCounter=%d\n", playerOne->specialCounter);

    fprintf (newFile, "playerTwoName=%s\n", playerTwo->name);
    fprintf (newFile, "playerTwoMaxHealth=%d\n", playerTwo->maxHealth);
    fprintf (newFile, "playerTwoHealth=%d\n", playerTwo->health);
    fprintf (newFile, "playerTwoSpecial=%s\n", playerTwo->specialMove);
    fprintf (newFile, "playerTwoCounter=%d\n", playerTwo->specialCounter);

    fprintf (newFile, "bombMaxHealth=%d\n", bomb->maxHealth);
    fprintf (newFile, "bombHealth=%d\n", bomb->health);
    fprintf (newFile, "bombNormalDamage=%d\n", bomb->normalDamage);
    fprintf (newFile, "bombDamage=%d\n", bomb->damage);
}

/* this function is called each moves for a player to make a move */
int playersTurn (bomb_t* currentBomb, player_t* currentPlayer, player_t* otherPlayer, int* savePointer, list_t* myList)
{
    /* current player's turn */

    move_t* currentMove = createMove();

    printf ("================================================\n");
    do
    {
    	printf ("1. To make a move, type \"1\". \n");
        printf ("2. To use special ability, type \"2\". \n");
        printf ("3. To save current game state, type \"3\". \n\n");

        printf ("%s's health is: %d\n", currentPlayer->name, currentPlayer->health);
        printf ("Bomb damage is currently: %d\n\n", currentBomb->damage);

        printf("%s 's turn, enter a task you wish to do (1-3): ", currentPlayer->name);
        scanf ("%d", &currentMove->userInput);

        if (currentMove->userInput == 1)
        {
            do 
            {
        	    printf("Enter holding time (between 1-5 sec): \n");
                scanf ("%d", &currentMove->holdTime);
            } while (currentMove->holdTime < 1 || currentMove->holdTime > 5);

        }

        else if (currentMove->userInput == 2)
        {
            if (currentPlayer->specialCounter < 2)
            {              
                if (strcmp(currentPlayer->specialMove, "RESET") == 0 )
                {
                    printf ("\n# Using Special Ability: RESET #\n\n");
                    doSpecialMove (currentPlayer, currentBomb, (pointerFunction)ResetSP);
                }

                else if (strcmp(currentPlayer->specialMove, "DOUBLE") == 0 )
                {
                    printf ("\n# Using Special Ability: DOUBLE #\n\n");
                    doSpecialMove (currentPlayer, currentBomb, (pointerFunction)DoubleSP);

                    /* prompt the player to play */
                    do 
                    {
        	            printf("Enter holding time (between 1-5 sec): \n");
                        scanf ("%d", &currentMove->holdTime);
                    } while (currentMove->holdTime < 1 || currentMove->holdTime > 5);
                }
                
                else if (strcmp(currentPlayer->specialMove, "HEAL") == 0 )
                {
                    printf ("\n# Using Special Ability: HEAL #\n\n");
                    doSpecialMove (currentPlayer, currentBomb, (pointerFunction)HealSP);
                }

                else if (strcmp(currentPlayer->specialMove, "SKIP") == 0 )
                {
                    printf ("\n# Using Special Ability: SKIP #\n\n");
                    doSpecialMove (currentPlayer, currentBomb, (pointerFunction)SkipSP);
                }

                else
                {
                    currentMove->userInput = 0; /* just to avoid a crash if something goes wrong */
                }
            }

            else 
            {
                printf ("\n# You have used all of your special abilities.#\n\n");
                currentMove->userInput = 0; /*makes the program prompt the user again */
            }
        }

        else if (currentMove->userInput == 3)
        {
            char fileName[128];
            printf ("Enter the name of your save file (max. 127 characters.): ");
            scanf ("%127s", fileName);

            FILE* saveFile = fopen(fileName, "w");

            writeNewSettings(saveFile, currentPlayer, otherPlayer, currentBomb);
            
            printList (myList, saveFile, (printFunction_t)printMove);

            *savePointer = 1; /* savePointer is used to prevent the other player plays after the game's saved */
            fclose (saveFile);
            printf ("\n Game Saved.\n");

            appendToList (myList, currentMove);

            return 0;
        }

    } while (currentMove->userInput < 1 || currentMove->userInput > 3);

    appendToList (myList, currentMove);

    #ifdef DEBUG
	printf ("%s's health is: %d\n\n", currentPlayer->name, currentPlayer->health);
    printf ("Remainig time for bomb fuze is: %d\n", currentBomb->health);
    printf ("Bomb damage is currently: %d\n\n", currentBomb->damage);
	#endif

	currentBomb->health = currentBomb->health - currentMove->holdTime;

	if ( currentBomb->health <= 0)
	{
    	printf ("\nWMWMWMWMWMWMWMWMWMWMWMWMWMWM\n");
        printf ("BOOM!!! %s got hit!\n", currentPlayer->name);
        printf ("WMWMWMWMWMWMWMWMWMWMWMWMWMWM\n\n");

		currentPlayer->health = currentPlayer->health - currentBomb->damage;
		
        if (currentPlayer->health < 1)
		{
			printf ("\n%s has held the bomb for too long.\n", currentPlayer->name);
			printf ("\n\t\t %s WINS!!!\n\n", otherPlayer->name);
            return 0;
		}

		#ifdef DEBUG
		printf ("%s's health is: %d\n", currentPlayer->name, currentPlayer->health);
		#endif 
	}

    return 0;
}

/* set up a new game */
int startGame (player_t* playerOne, player_t* playerTwo, bomb_t* bomb, int* savePointer, list_t* myList)
{
    do
    {
        /* player 1's turn */
        if (*savePointer == 0)
        {
            playersTurn (bomb, playerOne, playerTwo, savePointer, myList);
            if (playerOne->health < 1) { return 0; } /* interrupts the program if one of the players health < 1 */
        }
        else if (*savePointer == 1)
        {
            return 0;
        }

        /* check if the bomb's still going */
        checkBomb(bomb);

        /* player 2's turn */
        if (*savePointer == 0)
        {
            playersTurn (bomb, playerTwo, playerOne, savePointer, myList);
            if (playerTwo->health < 1) { return 0; }
        }
        else if (*savePointer == 1)
        {
            return 0;
        }

        checkBomb(bomb);
        
	} while (playerOne->health >= 0 && playerTwo->health >= 0);

    setHealth(playerOne, playerTwo, bomb);

    return 0;
}

/* checks the bomb, and reset its values if necessary */
void checkBomb (bomb_t* bomb)
{
    if (bomb->health <= 0)
    {
        bomb->health = bomb->maxHealth;
        /* in case a player used DOUBLE, this will reset the damag to normal */
        /* which means the damage of the bomb is doubled until it explodes */
        bomb->damage = bomb->normalDamage;
    }

    
}

/* set the struct values to be ready for a new game */
void setHealth (player_t* playerOne, player_t* playerTwo, bomb_t* bomb)
{
	playerOne->health = playerOne->maxHealth;
	playerOne->specialCounter = 0;

    playerTwo->health = playerTwo->maxHealth;
    playerTwo->specialCounter = 0;

	bomb->health = bomb->maxHealth;
    bomb->damage = bomb->normalDamage;
}


/* ##### SPECIAL MOVE RELATED FUNCTIONS ##### */

/* function pointer used for special moves */
void doSpecialMove (player_t* currentPlayer, bomb_t* bomb, pointerFunction specialAbility)
{
    specialAbility(currentPlayer, bomb);
}

/* special move functions:  */
void HealSP (player_t* currentPlayer, bomb_t* bomb)
{
    printf ("\n%s USED SPECIAL ABILITY: HEAL\n", currentPlayer->name);
    currentPlayer->health = currentPlayer->maxHealth;
    currentPlayer->specialCounter = currentPlayer->specialCounter + 1;
    printf ("Their health has been restored to max.\n\n");
}

void ResetSP (player_t* currentPlayer, bomb_t* bomb)
{
    printf ("\n%s USED SPECIAL ABILITY: HEAL\n", currentPlayer->name);
    bomb->health = bomb->maxHealth;
    currentPlayer->specialCounter = currentPlayer->specialCounter + 1;
    printf ("Bomb's health has been restored to max.\n\n");
}

void SkipSP (player_t* currentPlayer, bomb_t* bomb)
{
    printf ("%s used special ability: SKIP\n", currentPlayer->name);
    currentPlayer->specialCounter = currentPlayer->specialCounter + 1;
}

void DoubleSP (player_t* currentPlayer, bomb_t* bomb)
{
    printf ("%s used special ability: DOUBLE\n", currentPlayer->name);
    currentPlayer->specialCounter = currentPlayer->specialCounter + 1;
    bomb->damage = bomb->damage * 2;
}


void printMove (move_t* myMove, FILE* myFile) //
{
    fprintf (myFile, "%d %d\n", myMove->userInput, myMove->holdTime);
}