#include "stringComparison.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <list>

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
		std::vector <std::string> allstrings;
		std::cout << "Opening "<< fileName << std::endl;
		while (std::getline(myfile, line)) {
			allstrings.emplace_back(line);
		}

		while (true) {
			std::unordered_map <std::string, bool> cache;
			cache.clear();
			cache.max_load_factor(0.5);
			cache.reserve(allstrings.size()/1000);
			std::list <std::string> fittingStrings;

			std::cout << "Enter a string to find similar to it in file:" << std::endl;
			getline(std::cin, searchWord);
			std::cout << std::endl;

			auto start = std::chrono::high_resolution_clock::now();
			
			for (auto& i : allstrings) {
				if (similarWord(searchWord, i, cache)) 
				{
					fittingStrings.emplace_back(i);
				}
			}

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast <std::chrono::milliseconds> (stop - start).count();
			auto sec = duration / 1000;
			
			for (auto i = fittingStrings.begin(); i != fittingStrings.end(); ++i) {
				std::cout << *i << std::endl;
			}

			std::cout << std::endl << "Search took " << sec << "."
				<< std::setw(3) << std::setfill('0')
				<< duration - sec * 1000 << " seconds" << std::endl;
		}
	}
	
	std::cout << "wrong name or something, restart program" << std::endl;
	return 0;
}