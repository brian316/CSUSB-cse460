#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {

char input[50];
strcpy(input, argv[1]);

for(int i = 2; i <=(argc-1); i++){
    strcat(input, " ");
    strcat(input, argv[i]);
}

FILE *fpi;				//for reading a pipe

  char buffer[BUFSIZ+1];		//BUFSIZ defined in <stdio.h>

  int chars_read;
  memset ( buffer, 0,sizeof(buffer));	//clear buffer
  fpi = popen (input, "r" );	//pipe to command "ps -auxw"
  if ( fpi != NULL ) {
    //read data from pipe into buffer
    chars_read = fread(buffer, sizeof(char), BUFSIZ, fpi );
    if ( chars_read > 0 )
     cout << "Output from pipe: " << buffer << endl;
    pclose ( fpi ); 			//close the pipe
    return 0;
  }

  return 1;

} //END
