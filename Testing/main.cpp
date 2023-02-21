
#include <iostream>
#include "Testing.h"
#include  <windows.h> 



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		Testing testing;
		testing.start();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}
	
}


