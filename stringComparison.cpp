#include "stringComparison.h"

bool similarWord(std::string & target, std::string & line) {

	int sizeDifference = target.size() > line.size() ? target.size() - line.size() : line.size() - target.size();

	if (sizeDifference > 1) {
		return false;
	}
	int mismatch = 0;

	if (sizeDifference == 1) {
		std::string *shorter = target.size() <= line.size() ? &target : &line;
		std::string *longer = target.size() > line.size() ? &target : &line;
		int j = 0;
		bool shift = false;
		for (auto i : *shorter) {
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
				continue;
			}
		}

		if (!shift) {
			++mismatch;
		}

		if (mismatch < 2) {
			return true;
		}
		return false;
	}

	if (sizeDifference == 0) {
		for (int i = 0; i < target.size(); ++i) {
			if (target.at(i) == line.at(i)) {
				continue;
			}
			else {
				++mismatch;
				if (mismatch > 1) {
					return false;
				}
			}
		}
		if (mismatch < 2) {
			return true;
		}
	}
	return false;
}
