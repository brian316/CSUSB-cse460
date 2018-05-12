//pipe4.cpp  (data producer)
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char user[100];
    strcpy(user, argv[1]);

    for(int i=2; i <= (argc-1); i++){
        strcat(user, " ");
	strcat(user, argv[i]);
    }

    int data_processed;
    int file_pipes[2];
    //const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    memset(buffer, '\0', sizeof(buffer));

    if (pipe(file_pipes) == 0) {   //creates pipe
        fork_result = fork();
        if (fork_result == (pid_t)-1) {  //fork fails
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0) {    //child
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe5", "pipe5", buffer, (char *)0);
            exit(EXIT_FAILURE);
        }
        else {                     //parent
            data_processed = write(file_pipes[1], user,
                                   strlen(user));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
        }
    }
    sleep(1);
    exit(EXIT_SUCCESS);
}
