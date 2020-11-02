#include "stringComparison.h"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

int main(int argc, char* argv[])
{
	std::string fileName;
	if (argc == 1) {
		std::cout << "Enter .txt file name with extension:" << std::endl;
		getline(std::cin, fileName);
	}
	else {
		fileName = argv[1];
	}

	std::ifstream myfile (fileName);
	std::string searchWord;
	std::string line;

	if (myfile.is_open()) {
		while (true) {			
			myfile.seekg(0);

			std::cout << "Enter a string to find simular to it in file:" << std::endl;
			getline(std::cin, searchWord);
			std::cout << std::endl;

			auto start = std::chrono::high_resolution_clock::now();

			while (std::getline(myfile, line)) {
				if (simularWord(searchWord, line)) {
					std::cout << line << std::endl;
				}
			}

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast <std::chrono::milliseconds> (stop - start).count();

			std::cout << std::endl << "took " << duration/1000 << "." << duration%1000 << " seconds" << std::endl;
			myfile.clear(); // clear fail flag
		}
	}
	
	std::cout << "wrong name or something, restart program" << std::endl;
	return 0;
}