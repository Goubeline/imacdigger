#pragma once

#include "bloc.hpp"

#include <vector>

void bfs_flow_field(std::vector<std::vector<Bloc>>& map, int start_x, int start_y);
bool inbound(int x, int y);