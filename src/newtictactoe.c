//Tic Tac Toe game between 2 players or playervscomputer
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/finalLib.h"

int grid[9]; 
bool gameOver = false;
bool vsComputer = false;

void reset();
bool spotSelect();
bool checkWin();
bool checkTie();
void displayBoard();
char getSymbol();
void askRestart();

bool playerTurn();
void computerTurn();

int game(){

    srand(time(0));

    reset();


    //prompt user for game they wish to play (vs human or vs computer)
    //printf("Please choose the type of game (input number):\n\t1 - human vs human\n\t2 - human vs computer\n\t3 - computer vs computer\n");

    int gameType;
    scanf("%d", &gameType);
    printf("input recieved");
    

    //askRestart();

    return 0;
}

void askRestart(){
    printf("Play again? (y/n)\n");
        char restart;
        scanf(" %c", &restart);

        if(restart == 'y'){
            game(3);
        } else if (restart == 'n') {
            
        } else {
            askRestart();
        }
}

void reset (){
    for (int i=0; i<9; i++){
        grid[i]=0;
    }
    gameOver = false;
    vsComputer = false;
}

bool spotSelect(int spot, int player){
    if (0 <= spot < 9){
        if (grid[spot] == 0){
            grid[spot] = player;
            return true;
        } else {
            printf("Place already taken. Please choose another place.\n");
            playerTurn(player);
        }
    } else {
        printf("Place out of bounds. Please choose another place.\n");
            playerTurn(player);
    }
}

void displayBoard(){
    int k=0;
    for (int i=0; i<3; i++){
        printf("+-----+\n");
        printf("|");
        for (int j=0; j<3; j++){
            printf("%c", getSymbol(grid[k]));
            printf("|");
            k++;
        }
        printf("\n");
    }
    printf("+-----+\n");
}

char getSymbol(int player){
        if (player == 0){
            return ' ';
        } else if (player == 1){
            return 'X';
        } else if (player == 2){
            return 'O';
        }
}

bool playerTurn(int player){
    displayBoard();
    printf("Player %d", player);
    printf(", please choose where to place your piece. (spot 1-9)\n");
    return true;
}

void computerTurn(int player){
    displayBoard();
    bool validMove = false;
    while (!validMove){
        int spot = (rand() %(9));
        if (grid[spot] == 0){
            grid[spot] = player;
            printf("Computer has placed a piece.\n");
            validMove = true;
        }
    }
}

bool checkWin(int player){

    //check horizontal win (row)
    for (int i=0; i<7; i+=3){
        if (grid[i] == player && grid[i+1] == player && grid[i+2] == player){
            gameOver = true;
        }
    }

    //check vertical win (column)
    for (int i=0; i<3; i++){
        if (grid[i] == player && grid[i+3] == player && grid[i+6] == player){
            gameOver = true;
        }
    }

    //check diagonal win (top left to bottom right)
    if (grid[0] == player && grid[4] == player && grid[8] == player){
        gameOver = true;
    }

    //check diagonal win (bottom left to top right)
    if (grid[6] == player && grid[4] == player && grid[2] == player){
        gameOver = true;
    }

    if (gameOver){
        if (vsComputer && player == 2){
            printf("Game over! Result: Joshua wins!\n");
            displayBoard();
        } else {
            printf("Game over! Result: Player %d wins!\n", player);
            displayBoard();
        }
    }
    return gameOver;
}

bool checkTie(){
    bool allFull = false;
    if (!gameOver){
        allFull = true;
        for (int i=0; i<9; i++){
            if (grid[i] == 0){
                allFull = false;
            }
        }
    }
    if (allFull){
        printf("Game over! Result: Tie!\n");
        gameOver = true;
    }
    return allFull;
}

//Written with love by Remi/Jeremy Ong