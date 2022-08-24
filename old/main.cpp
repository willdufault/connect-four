#include <cstdlib>
#include <iostream>
#include "production.hpp"

using namespace std;

int main()
{
	// tests would go here
	Production* prod = new Production();
	prod->runProduction();
	delete prod;
	return EXIT_SUCCESS;
}