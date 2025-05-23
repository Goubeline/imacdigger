#pragma once

#include "bloc.hpp"

#include <vector>

bool inbound(int x, int y);
float calculateAngle(std::vector<float> vec1, std::vector<float> vec2);
void find_flow(std::vector<std::vector<int>>& distances, std::vector<std::vector<Bloc>>& map, std::pair<int, int> start, std::pair<int, int> current);
std::vector<std::vector<int>> dist_vec(std::vector<std::vector<Bloc>>& map, int start_x, int start_y);
void flow_field(std::vector<std::vector<int>>& distances, std::vector<std::vector<Bloc>>& map, std::pair<int, int> start);
void bfs_flow_field(std::vector<std::vector<Bloc>>& map, int start_x, int start_y);