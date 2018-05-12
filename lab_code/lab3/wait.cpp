//test_wait.cpp
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
  pid_t pid;		//process id
  char *message;
  int n;
  int exit_code;

  cout << "fork program starting\n";
  pid = fork();
  switch ( pid ) {
  case -1:
    cout << "Fork failure!\n";
    return 1;
  case 0:
    message = "This is the child\n";
    n = 5;
    exit_code = 9;
    break;
  default:
    message = "This is the parent\n";
    n = 3;
    exit_code = 0;
    break;
  }
  for ( int i = 0; i < n; ++i ) {
    cout << message;
    sleep ( 1 );
  }

  sleep(1);
  
  //print all ids
  if ( pid != 0 ) {		//parent
    cout << "Parent process id: " << getpid() << endl ;

    pid_t grandchild_pid;
    grandchild_pid = fork();

    if(grandchild_pid != 0) {
	cout << "Child process id: " << getpid() << endl ;
  }
    else
    {
	    cout << "Grandchild process id: " << getpid() << endl ;
	}
  }
  exit ( exit_code );
}
