#include <iostream>
#include <sys/types.h>
#include <unistd.h>


using namespace std;

int main()
{
	int i;

	for (i = 0; i < 3; ++i) {
		fork();
		cout << i << endl;
	}
	return 0;
}
