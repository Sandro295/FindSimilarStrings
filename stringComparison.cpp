#include "stringComparison.h"
#include <iostream>

bool similarWord(std::string & target, std::string & line, std::unordered_map <std::string, bool> & cache) 
{
	int sizeDifference = target.size() > line.size() ? target.size() - line.size() : line.size() - target.size();
	if (sizeDifference > 1) {
		return false;
	}

	auto CachedLine = cache.find(line);
	if (CachedLine != cache.end()) {
		return CachedLine->second;
	}

	if (sizeDifference == 1) {
		int mismatch = 0;
		std::string *shorter = target.size() <= line.size() ? &target : &line;
		std::string *longer = target.size() > line.size() ? &target : &line;
		int j = 0;
		bool shift = false;
		for (auto& i : *shorter) {
			if (i == longer->at(j)) {
				++j;
				continue;
			}
			else if (!shift && i == longer->at(++j)) {
				++j;
				shift = true;
				++mismatch;
				continue;
			}
			else {
				if (shift) {
					++j;
				}
				++mismatch;
				if (mismatch > 1) {
					cache.emplace(line, false);
					return false;
				}
				continue;
			}
		}
		if (!shift) {
			++mismatch;
		}
		if (mismatch < 2) {
			cache.emplace(line, true);
			return true;
		}
		cache.emplace(line, false);
		return false;
	}

	if (sizeDifference == 0) {
		int mismatch = 0;
		for (unsigned int i = 0; i < target.size(); ++i) {
			if (target[i] == line[i]) {
				continue;
			}
			else {
				++mismatch;
				if (mismatch > 1) {
					cache.emplace(line, false);
					return false;
				}
			}
		}
		if (mismatch < 2) {
			cache.emplace(line, true);
			return true;
		}
	}
	cache.emplace(line, false);
	return false;
}