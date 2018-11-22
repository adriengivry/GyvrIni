#include <iostream>

#include <GyvrIni/GyvrIni.h>

int main()
{
	GyvrIni::Core::IniFile myFile("test.ini");

	std::cin.get();

	return EXIT_SUCCESS;
}