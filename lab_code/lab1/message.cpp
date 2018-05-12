#include <iostream>
#include "message.h"

using namespace std;

void display_message(){

	string input;
	cout << "message: ";
	getline(cin, input);
	cout << endl << "OUTPUT: "<< input << endl;
}
