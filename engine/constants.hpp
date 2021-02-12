#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP



namespace agario{

namespace shapes{

const float eps = 0.01;
}//namespace shapes
//graphics
const float WINDOW_WIDTH = 1000;
const float WINDOW_HEIGHT = 1000;

//colors
const unsigned int WHITE = 0xffffffff;
const unsigned int RED = 0xff0000ff;
const unsigned int GRAY = 0x808080ff;
const unsigned int YELLOW = 0xffff00ff;
const unsigned int ORANGE = 0xff8000ff;
const unsigned int PINK = 0xff007fff;
const unsigned int BLUE = 0x0000ffff;
const unsigned int GREEN = 0x00ff00ff;
const unsigned int MAGENTA = 0xff00ffff;
const unsigned int PURPLE = 0x800080ff;
const unsigned int MAROON = 0x800000ff;

const unsigned int n_colors = 11;

const unsigned int AGARIO_COLORS[n_colors] = {
    WHITE, RED, PURPLE, YELLOW, ORANGE, PINK, BLUE, GREEN, MAGENTA, GRAY, MAROON
};
//physics

const float PLUS_INFINITY = 10e9;
const float MINUS_INFINITY = -10e9;
const float PI = 3.14159265359;
const float GRAVITY_CONST = 6;
const float OUT_FORCE_VALUE = 20;
const float MIN_PLAYER_RADIUS = 5;
const float W_RADIUS = 7;
const float MINI_RADIUS = 1.0f;
const float BOMB_RADIUS = 25;
const float DIVIDE_FORCE = 40;

const int MAX_MINIS_ON_MAP = 300;
const int MAX_MISSING_MINIS = 50;
const int MAX_BOMB_ON_MAP = 20;
const float MINI_WIDTH = 50.0f;

const int DEFAULT_MAP_WIDTH = 300;
const int DEFAULT_MAP_HEIGHT = 300;

const int MAX_PLAYERS_IN_GAME = 5;

}//namespace agario

#endif