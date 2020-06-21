#pragma once

#include "common/grid.hpp"

#include <anax/Entity.hpp>
#include <string>

int encode_neighbours(Grid<anax::Entity> &map, int i, int j);
std::string get_type(const std::string &obs_type, int code);