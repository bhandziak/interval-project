#include "Klasa.h"
#include <iostream>
#include <random>

void Klasa::test() {
	std::cout << "Dziala" << std::endl;
}

std::vector<std::vector<int>> Klasa::readFile(const std::string& filename)
{
    std::vector<std::vector<int>> result;

    try {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Nie można otworzyć pliku: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            std::stringstream ss(line);
            std::string number;
            while (std::getline(ss, number, ';')) {
                if (!number.empty()) {
                    row.push_back(std::stoi(number));
                }
            }
            result.push_back(row);
        }

        file.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Wystąpił błąd: " << e.what() << std::endl;
    }

    return result;
}

int Klasa::randInt(int from, int to)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(from, to);
    return distr(gen);
}

std::vector<std::pair<int, int>> Klasa::createGameIntervals(int rounds)
{
    int from = 0;
    int to = 12;
    int startKey = 24;


    std::vector<std::pair<int, int>> mainTable;

    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < 2; j++) {

            std::pair<int, int> row = { startKey, startKey + randInt(from, to) };
            mainTable.push_back(row);
        }

        startKey = 24 + randInt(from, to);
    }

    return mainTable;
}

