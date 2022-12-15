#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/finalLib.h"

#include <mosquitto.h>

const char outtopic[] = "ong_tictactoe";
const char intopic[] = "ong_arduino";



char *inputMSG;
bool msgProcessed;
bool newMessage;

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

    newMessage = true;
    char *inputMSG = (char *)msg->payload;

    if(strcmp(inputMSG, "reset") == 0){
        printme();
        //msgProcessed = true;
        //game(3);
    }

    
}

int main(){
    msgProcessed = true;
    newMessage = false;


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


        mosquitto_loop_start(mosq);
        int i=0;
        while(i < 3){
            if(newMessage){
                printf("%s", inputMSG);
                newMessage = false;
                i++;
            }
        }
        

        
        printf("Press Enter to send message...\n");
        getchar();
        mosquitto_publish(mosq, NULL, outtopic, 6, "Hello!", 0, false);

        printf("Press Enter to quit...\n");
        getchar();
        
        mosquitto_loop_stop(mosq, true);

    

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}





