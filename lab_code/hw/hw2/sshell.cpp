//NOT FINISHED
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int main(){
    string command,parameters;
    while ( 1 ) {                 //repeat forever
    cout << "\nCommand: ";              //display prompt on screen
    cin >> command;
    cout << "\nParameters ";
    cin >> parameters;
    
    if (afork = fork() != 0 )          // parent
      if();            //wait for child
    else{
      execve ( commamd, parameters, 0 ); // execute command
    }
  }
}
