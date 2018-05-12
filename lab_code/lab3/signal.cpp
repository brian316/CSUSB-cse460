//test_signal.cpp
#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void func ( int sig )
{
  cout << "Oops! -- I got a signal " << sig << endl;
}

int main()
{
  (void) signal ( SIGKILL, func ); //SIGKILL

  while ( 1 ) {
    cout << "CSUSB CS 460 lab on signals" << endl;
    sleep ( 1 ); 
  }
  return 0;
}
