#include "Tiles.hpp"

int encode_neighbours(std::array<std::array<Tile,25>,40> &map, int i, int j) {
    const int n = 40;
    const int m = 25;
    const Tile type = map[i][j];

    /* code is 4 bits :  Up | Right | Down | Left */
    int code = 0;
    const int UP = 3;
    const int RIGHT = 2;
    const int DOWN = 1;
    const int LEFT = 0;

    if (j == 0) { // Top border
        if (i == 0) { // Upper-left corner
            code += map[i + 1][j]==type ? 1 << RIGHT : 0; // Right
            code += map[i][j + 1 ]==type ? 1 << DOWN : 0; // Down
        }
        else if (i == n-1) { // Upper-right
            code += map[i][j - 1]==type ? 1 << LEFT : 0;
            code += map[i - 1][j]==type ? 1 << DOWN : 0;
        }
        else {
            code += map[i - 1][j]==type ? 1<<LEFT : 0;
            code += map[i + 1][j]==type ? 1<<RIGHT : 0;
            code += map[i][j + 1]==type ? 1<<DOWN : 0;
        }
    } else if (j == m-1) { // Bottom border
        if (i == 0) {     // Bottom-left corner
            code += map[i + 1][j]==type ? 1 << RIGHT : 0;
            code += map[i][j - 1]==type ? 1 << UP : 0;
        }
        else if (i == n-1) {  // Bottom-right corner
            code += map[i - 1][j]==type ? 1<<LEFT : 0;
            code += map[i][j - 1]==type ? 1<<UP : 0;
        }
        else {
            code += map[i - 1][j]==type ? 1<<LEFT : 0;
            code += map[i + 1][j]==type ? 1<<RIGHT : 0;
            code += map[i][j - 1]==type ? 1<<UP : 0;
        }
    } else {
        if (i == 0) { // Left border
            code += map[i + 1][j]==type ? 1<<RIGHT : 0;
            code += map[i][j - 1]==type ? 1<<UP : 0;
            code += map[i][j + 1]==type ? 1<<DOWN : 0;
        }
        else if (i == n-1){ // Right border
            code += map[i - 1][j]==type ? 1<<LEFT : 0;
            code += map[i][j - 1]==type ? 1<<UP : 0;
            code += map[i][j + 1]==type ? 1<<DOWN : 0;
        }
        else { // General case
            code += map[i][j - 1]==type ? 1<<UP : 0;
            code += map[i + 1][j]==type ? 1<<RIGHT : 0;
            code += map[i][j + 1]==type ? 1<<DOWN : 0;
            code += map[i - 1][j]==type ? 1<<LEFT : 0;
        }
    }
    return code;
}


std::string get_type(const std::string &obs_type, int code) {
    switch (code) {
        case 0:
            return obs_type+"_square.png";
        case 1:
            return obs_type+"_edge_L.png";
        case 2:
            return obs_type+"_edge_T.png";
        case 3:
            return obs_type+"_cornerBL.png";
        case 4:
            return obs_type+"_edge_R.png";
        case 5:
            return obs_type+"_horizontal.png";
        case 6:
            return obs_type+"_cornerBR.png";
        case 7:
            return obs_type+"_T_T.png";
        case 8:
            return obs_type+"_edge_B.png";
        case 9:
            return obs_type+"_cornerTL.png";
        case 10:
            return obs_type+"_vertical.png";
        case 11:
            return obs_type+"_T_R.png";
        case 12:
            return obs_type+"_cornerTR.png";
        case 13:
            return obs_type+"_T_B.png";
        case 14:
            return obs_type+"_T_L.png";
        case 15:
            return obs_type+"_X.png";
        default:
            return "not found";
    }
}