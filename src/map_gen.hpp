#pragma once

#include <vector>
#include "bloc.hpp"

std::vector<std::vector<Bloc>> initializeMap();
int countWallNeighbors(const std::vector<std::vector<Bloc>>& map, int x, int y, int radius);
std::vector<std::vector<Bloc>> applyCellularAutomata(const std::vector<std::vector<Bloc>>& map, int minWallsRadius1, int minWallsRadius2);
void populateMap(std::vector<std::vector<Bloc>>& map);
std::pair<int, int> findValidStart(const std::vector<std::vector<Bloc>>& map);
std::vector<std::vector<Bloc>> generateMap();