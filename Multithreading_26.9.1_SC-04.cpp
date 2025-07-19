#include "threading.h"

#include <iostream>

extern const char* outFile{ "result.data" };

int main()
{
	std::cout << "Threading summation.\n";
	std::cout << "Hello!\nWe are testing the summation time of array elements\n"
		<< "with a different number of threads.\n";
	Array array;
	return 0;
}
