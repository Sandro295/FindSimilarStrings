#pragma once

#ifndef STRINGCOMPARISON_H
#define STRINGCOMPARISON_H
#include <string>
#include <unordered_map>

bool similarWord(std::string & target, std::string & line, std::unordered_map <std::string, bool> & cache);

#endif // STRINGCOMPARISON_H