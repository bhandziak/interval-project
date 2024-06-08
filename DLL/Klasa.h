#pragma once
#include "API.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>

class EXPORT_API Klasa
{
public:
	void test();
	std::vector<std::vector<int>> readFile(const std::string& filename);
	int randInt(int from, int to);
	std::vector<std::pair<int, int>> createGameIntervals(int rounds);
};