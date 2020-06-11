#pragma once

#include <string>
#include <array>

enum class Tile : int {
    VOID = 0,
    WALL = 1,
    PIT = 2,
    PLAYER = 3,
    YELLOW_AI = 4,
    YELLOWP_AI = 5,
    BLUE_AI = 6,
    BLUEP_AI = 7,
    RED_AI = 8,
    REDP_AI = 9,
    PURPLE_AI = 10,
    PURPLEP_AI = 11,
    SPAWNER = 12,
    SPAWNERP = 13,
    DARK = 14,
    DARKP = 15
};

int encode_neighbours(std::array<std::array<Tile,25>,40> &map, int i, int j);
std::string get_type(const std::string &obs_type, int code);

std::string tile_to_bodyfile(const Tile& type);
std::string tile_to_canonfile(const Tile& type);