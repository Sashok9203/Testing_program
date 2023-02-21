
#include <iostream>
#include "Testing.h"
#include  <windows.h> 



int main()
{
	system("chcp 1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Testing testing;
	testing.start();
}


