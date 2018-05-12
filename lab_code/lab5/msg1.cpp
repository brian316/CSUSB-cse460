//msg1.cpp
/* Here's the receiver program. */

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
    char some_text[BUFSIZ];
};
struct my_msg {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

int main()
{
    int running = 1;
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_receive = 0;

/* First, we set up the message queue. */

    int sar = fork();  //fork for sending and recieving
    if(sar ==0){
    msgid = msgget((key_t)2345, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    }
/* Then the messages are retrieved from the queue, until an end message is encountered.
 Lastly, the message queue is deleted. */


    while(running && sar == 0) {
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("\nThem: %s", some_data.some_text);
        if (strncmp(some_data.some_text, "end", 3) == 0) {
	    kill(sar, SIGKILL);
            running = 0;
        }
    }

    if(sar == 0){
        if (msgctl(msgid, IPC_RMID, 0) == -1 && sar == 0) {
            fprintf(stderr, "msgctl(IPC_RMID) failed\n");
            exit(EXIT_FAILURE);
        }
    }

    if(sar != 0){
        struct my_msg some_data2;
        int msgid2;
	char buffer[BUFSIZ];

	msgid2 = msgget((key_t)7777, 0777 | IPC_CREAT);
        
	if (msgid2 == -1) {
            fprintf(stderr, "msgget failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
	
        while(running) {
            printf("Enter some text: ");
            fgets(buffer, BUFSIZ, stdin);
            some_data2.my_msg_type = 1;
            strcpy(some_data2.some_text, buffer);

            if (msgsnd(msgid2, (void *)&some_data2, MAX_TEXT, 0) == -1) {
                fprintf(stderr, "msgsnd failed\n");
		kill(sar, SIGKILL);
            }
            if (strncmp(buffer, "end", 3) == 0) {
                running = 0;
		kill(sar, SIGKILL);
		exit(EXIT_SUCCESS);
            }
        }	
    }

    exit(EXIT_SUCCESS);
}
