#include "stringComparison.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

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

	std::ifstream myfile(fileName);
	std::string searchWord;
	std::string line;

	if (myfile.is_open()) {
		std::vector <std::string> allstrings;
		while (std::getline(myfile, line)) {
			allstrings.push_back(line);
		}

		while (true) {
			std::cout << "Enter a string to find similar to it in file:" << std::endl;
			getline(std::cin, searchWord);
			std::cout << std::endl;
			std::unordered_map <std::string, bool> cache;
			cache.clear();

			auto start = std::chrono::high_resolution_clock::now();

			for (auto i : allstrings) {
				if (!cache.empty()) {
					auto CachedLine = cache.find(i);
					if (CachedLine != cache.end()) {
						if (CachedLine->second) {
							std::cout << i << std::endl;
							continue;
						}
						else if (!CachedLine->second) {
							continue;
						}
					}
				}
				if (similarWord(searchWord, i)) {
					cache.emplace(i, true);
					std::cout << i << std::endl;
				}
				else {
					cache.emplace(i, false);
				}
			}

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast <std::chrono::milliseconds> (stop - start).count();
			auto sec = duration / 1000;
			std::cout << std::endl << "took " << sec << "."
				<< std::setw(3) << std::setfill('0')
				<< duration - sec * 1000 << " seconds" << std::endl;
		}
	}

	std::cout << "wrong name or something, restart program" << std::endl;
	return 0;
}