/* bombHeader.h */

#include "linkedList.h"

#ifndef BOMBHEADER
#define BOMBHEADER

typedef struct bomb
{
	int maxHealth;
	int health;
	int normalDamage;
	int damage;

} bomb_t;

typedef struct player
{
	char name[128];
	char specialMove[10];
	int maxHealth;
	int health;
	int specialCounter;

} player_t;

typedef struct move
{
	int userInput;
	int holdTime;

} move_t;

player_t* createPlayers();
bomb_t* createBomb();
move_t* createMove();

void readSettings (FILE* myFile, player_t* playerOne, player_t* playerTwo, bomb_t* currentBomb);
void displaySettings (player_t* playerOne, player_t* playerTwo, bomb_t* bomb, list_t* myList);
void writeNewSettings(FILE* newFile, player_t* playerOne, player_t* playerTwo, bomb_t* bomb);
void changeSettings(player_t* playerOne, player_t* playerTwo, bomb_t* bomb, list_t* myList);
void mainMenu(player_t* playerOne, player_t* playerTwo, bomb_t* currentBomb, list_t* myList);
int playersTurn (bomb_t* currentBomb, player_t* currentPlayer, player_t* otherPlayer, int* savePointer, list_t* myList);
void checkBomb (bomb_t* bomb);
int startGame (player_t* playerOne, player_t* playerTwo, bomb_t* bomb, int* savePointer, list_t* myList);
void setHealth (player_t* playerOne, player_t* playerTwo, bomb_t* bomb);

typedef void(*pointerFunction)(void* para1, void* para2);


void doSpecialMove (player_t* currentPlayer, bomb_t* bomb, pointerFunction specialAbility);

void HealSP (player_t* currentPlayer, bomb_t* bomb);
void ResetSP (player_t* currentPlayer, bomb_t* bomb);
void SkipSP (player_t* currentPlayer, bomb_t* bomb);
void DoubleSP (player_t* currentPlayer, bomb_t* bomb);

void savingState(player_t* playerOne, player_t* playerTwo, bomb_t* bomb, FILE* myFile);
void loadStats (player_t* playerOne, player_t* playerTwo, bomb_t* bomb, FILE* loadFile);

void printMove (move_t* myMove, FILE* myFile); //

#endif

/* The following is a template for settings.txt (just in case) */
/*
playerOneName=Player_Dos
playerOneMaxHealth=52
playerOneHealth=52
playerOneSpecial=DOUBLE
playerOneCounter=0
playerTwoName=Player_Uno
playerTwoMaxHealth=53
playerTwoHealth=53
playerTwoSpecial=HEAL
playerTwoCounter=0
bombMaxHealth=10
bombHealth=10
bombNormalDamage=25
bombDamage=25

*/