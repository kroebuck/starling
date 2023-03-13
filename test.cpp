#include <iostream>
#include <string>

// read files
#include <fstream>
//#include <sstream>

// sleep
#include <chrono>
#include <thread>

int main()
{
	// std::ifstream infile("initial_data.txt");
	// std::string line;
	// while (std::getline(infile, line))
	// {
	// 	std::cout << line << std::endl;
	// }

	for (int i = 0; i < 100000; i++) {
		std::cout << i << '\n';//std::endl;
		if (i % 10 == 0) std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}