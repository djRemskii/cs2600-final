#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/finalLib.h"

#include <mosquitto.h>

const char outtopic[] = "ong_tictactoe";
const char intopic[] = "ong_arduino";

//FOR TICTACTOE

int grid[9]; 
bool gameStart = false;
bool gameOver = false;
bool vsComputer = false;

void reset();
bool spotSelect();
bool checkWin();
bool checkTie();
void displayBoard();
char getSymbol();
void askRestart();
int game();

bool playerTurn();
void computerTurn();

//END

char *inputMSG;
bool msgProcessed;

void on_connect(struct mosquitto *mosq, void *obj, int rc){
    printf("ID: %d\n", * (int *) obj);
    if(rc) {
        printf("Error with result code: %d\n", rc);
        exit (-1);
    }
    mosquitto_subscribe(mosq, NULL, intopic, 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg){
    printf("New message with topic %s: %s\n", msg->topic, (char *) msg->payload);

    if(strcmp(inputMSG, "reset") == 0){
        reset();
        printme();
        gameStart = true;
        //msgProcessed = true;
        //game(3);
    }

    inputMSG = (char *)msg->payload;
    msgProcessed = false;

    
}

int main(){
    msgProcessed = true;

    int rc, id=12;

    mosquitto_lib_init();

    struct mosquitto *mosq;
    
    mosq = mosquitto_new("subscribe-test", true, &id);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, "test.mosquitto.org", 1883, 10);
    if(rc){
        printf("Could not connect to Broker with return code %d\n", rc);
        return -1;
    }

    while(true){
        mosquitto_loop_start(mosq);
        while(!gameStart){
        
        }
        mosquitto_loop_stop(mosq, true);
        printf("hello");
        gameStart = false;
        

        /*
        printf("Press Enter to send message...\n");
        getchar();
        mosquitto_publish(mosq, NULL, outtopic, 6, "Hello!", 0, false);

        printf("Press Enter to quit...\n");
        getchar();
        */
    }
    

    

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}





//TIC TAC TOE CODE
//Tic Tac Toe game between 2 players or playervscomputer



int game(int gameTypeIn){

    srand(time(0));

    reset();


    //prompt user for game they wish to play (vs human or vs computer)
    //printf("Please choose the type of game (input number):\n\t1 - human vs human\n\t2 - human vs computer\n\t3 - computer vs computer\n");
    while(msgProcessed != false){}
    int gameType = gameTypeIn;
    printf("input recieved\n");
    printf("%s", inputMSG);
    

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