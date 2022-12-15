#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void printme();

void reset();
bool spotSelect();
bool checkWin();
bool checkTie();
void displayBoard();
char getSymbol();
void askRestart();

bool playerTurn();
void computerTurn();

int game(int gameTypeIn);