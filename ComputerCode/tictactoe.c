//Tic Tac Toe game between 2 players or playervscomputer
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int grid[3][3]; 
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

int main(){

    srand(time(0));

    reset();


    //prompt user for game they wish to play (vs human or vs computer)
    printf("Please choose the type of game (input number):\n\t1 - human vs human\n\t2 - human vs computer\n\t3 - computer vs computer\n");

    int gameType;
    scanf("%d", &gameType);
    if (gameType == 2){
        vsComputer = true;
    } else if (gameType == 3){
        while (!gameOver){
            computerTurn(1);
            checkWin(1);
            checkTie();
            if (!gameOver){
                computerTurn(2);
                checkWin(2);
                checkTie();
            }
        }
    }
    
    //need while loop for game working
    while (!gameOver){
        playerTurn(1);
        checkWin(1);
        checkTie();
        if (vsComputer && !gameOver){
            computerTurn(2);
            checkWin(2);
            checkTie();
        } else if (!gameOver){
            playerTurn(2);
            checkWin(2);
            checkTie();
        }

    }
    

    askRestart();

    return 0;
}

void askRestart(){
    printf("Play again? (y/n)\n");
        char restart;
        scanf(" %c", &restart);

        if(restart == 'y'){
            main();
        } else if (restart == 'n') {
            
        } else {
            askRestart();
        }
}

void reset (){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            grid[i][j] = 0;
        }
    }
    gameOver = false;
    vsComputer = false;
}

bool spotSelect(int row, int column, int player){
    if (0 <= row && row < 3 && 0 <= column && column < 3){
        if (grid[row][column] == 0){
            grid[row][column] = player;
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
    for (int i=0; i<3; i++){
        printf("+-----+\n");
        printf("|");
        for (int j=0; j<3; j++){
            printf("%c", getSymbol(grid[i][j]));
            printf("|");
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
    printf(", please choose where to place your piece. (row 1-3, column 1-3)\n");
        int row;
        int column;
        scanf("%d", &row);
        scanf("%d", &column);
        return spotSelect(row-1, column-1, player);
}

void computerTurn(int player){
    displayBoard();
    bool validMove = false;
    while (!validMove){
        int row = (rand() %(3));
        int column = (rand() %(3));
        if (grid[row][column] == 0){
            grid[row][column] = player;
            printf("Computer has placed a piece.\n");
            validMove = true;
        }
    }
}

bool checkWin(int player){

    //check horizontal win (row)
    for (int i=0; i<3; i++){
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player){
            gameOver = true;
        }
    }

    //check vertical win (column)
    for (int i=0; i<3; i++){
        if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player){
            gameOver = true;
        }
    }

    //check diagonal win (top left to bottom right)
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player){
        gameOver = true;
    }

    //check diagonal win (bottom left to top right)
    if (grid[2][0] == player && grid[1][1] == player && grid[0][2] == player){
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
        for (int i=0; i<3; i++){
            for (int j=0; j<3; j++){
                if (grid[i][j] == 0){
                    allFull = false;
                }
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