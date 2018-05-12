//fan of processes
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
	pid_t child;

	for (int i = 0; i < 10; ++i) {
		if ((child = fork()) <= 0)
			break;	//child
		sleep(1);	//pause/let process run
	}
	cout << "This is child " << getpid() << " with parent " << getppid() << endl;

	return 0;
}
