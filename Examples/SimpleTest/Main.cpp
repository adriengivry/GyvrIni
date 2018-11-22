#include <iostream>
#include <GyvrIni/GyvrIni.h>

int main()
{
	GyvrIni::Core::IniFile myFile("user.ini");

	myFile.Set<std::string>("Hello", "MDdR");
	myFile.SaveChanges();
	std::cin.get();

	return EXIT_SUCCESS;
}