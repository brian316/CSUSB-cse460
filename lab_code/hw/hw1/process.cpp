//creates a chain of processes
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stack>

using namespace std;

int main()
{
  pid_t childpid;
  stack<pid_t> oldpid;	//old ids

  for ( int i = 0; i < 10; ++i ) {
    if ( childpid = fork() )
        break;	//parent
    oldpid.push ( getppid());	//parent pid
  }
  wait ( NULL );    //wait
  cout << "This is process " << getpid() << " with child " << childpid << 
	" and ancestors: ";
  while ( !oldpid.empty() ) {	//get (old id) ancestors
    cout << oldpid.top() << " ";    //print ancestors
    oldpid.pop();    //remove ancestor
  }
  cout <<  endl;
  return 0;
}    //END
