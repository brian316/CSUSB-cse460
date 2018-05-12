//pipe2.cpp
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
  FILE *fpo;				//for writing to a pipe
 
  char buffer[BUFSIZ+1];		//BUFSIZ defined in <stdio.h>
  
  //Write buffer a message
  sprintf(buffer, "Arnod said, 'If I am elected, ..', and the fairy tale begins");  

  fpo = popen ( "awk '{t=$1;$1=$3;$3=t} 1' ", "w" );	//pipe to command "od -c"
  
  if ( fpo != NULL ) {
    //send data from buffer to pipe 
    fwrite(buffer, sizeof(char), strlen(buffer), fpo );  
    pclose ( fpo ); 			//close the pipe
    return 0; 
  }
  return 1;
}
