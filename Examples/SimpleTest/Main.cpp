#include <iostream>
#include <GyvrIni/GyvrIni.h>

int main()
{
	GyvrIni::Core::IniFile myFile("user.ini");

	bool result = myFile.Set<std::string>("Hello", "dsad");

	std::string test = myFile.Get<std::string>("Hello");

	for (const std::string& line : myFile.GetFormattedContent())
		std::cout << line << std::endl;

	myFile.Rewrite();

	std::cin.get();

	return EXIT_SUCCESS;
}