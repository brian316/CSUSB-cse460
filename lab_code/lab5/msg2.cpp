//msg2.cpp
/* The sender program is very similar to msg1.cpp. In the main set up, delete the
 msg_to_receive declaration and replace it with buffer[BUFSIZ], remove the message
 queue delete and make the following changes to the running loop.
 We now have a call to msgsnd to send the entered text to the queue. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

struct my_msg_recieved {
    long int my_msg_type;
    char some_text[BUFSIZ];
};

int main()
{
    int running = 1;
    struct my_msg_st some_data;
    int msgid, msgid2;
    char buffer[BUFSIZ];
    
    int sar = fork();  //fork for sending and recieving
    if(sar !=0){
    msgid = msgget((key_t)2345, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    }

    while(running && sar != 0) {  //parent fork sends
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        some_data.my_msg_type = 1;
        strcpy(some_data.some_text, buffer);

        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            kill(sar, SIGKILL);
        }
        if (strncmp(buffer, "end", 3) == 0) {
            kill(sar, SIGKILL);
	    running = 0;
        }
    }

    struct my_msg_recieved some_data2;
    long int msg_to_recieve = 0;
    
    if(sar == 0) {
	msgid2 = msgget((key_t)7777, 0777 | IPC_CREAT);
        
	if (msgid2 == -1) {
                fprintf(stderr, "msgget failed with error: %d\n", errno);
                exit(EXIT_FAILURE);
            }
	
	
	while(running){
            if (msgrcv(msgid2, (void *)&some_data2, BUFSIZ,
                   msg_to_recieve, 0) == -1) {
                fprintf(stderr, "msgrcv failed with error: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            printf("\nThem: %s", some_data2.some_text);
            if (strncmp(some_data2.some_text, "end", 3) == 0) {
		kill(sar, SIGKILL);
                running = 0;
            }
        }

	if (msgctl(msgid2, IPC_RMID, 0) == -1) {
            fprintf(stderr, "msgctl(IPC_RMID) failed\n");
            exit(EXIT_FAILURE);
        }
    }	

    exit(EXIT_SUCCESS);
}
