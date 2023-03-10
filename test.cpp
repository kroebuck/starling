#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
	std::ifstream infile("initial_data.txt");
	std::string line;
	while (std::getline(infile, line))
	{
		std::cout << line << std::endl;
	}

	return 0;
}