#pragma once

#include <vector>
#include "bloc.hpp"

std::vector<std::vector<Bloc>> initializeMap();
int countWallNeighbors(const std::vector<std::vector<Bloc>>& map, int x, int y);
std::vector<std::vector<Bloc>> applyCellularAutomata(const std::vector<std::vector<Bloc>>& map);
void populateMap(std::vector<std::vector<Bloc>>& map);
std::vector<std::vector<Bloc>> generateMap();