#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP



namespace agario{

namespace shapes{

const float eps = 0.01;
}//namespace shapes
//graphics
const float WINDOW_WIDTH = 1000;
const float WINDOW_HEIGHT = 1000;


//physics
const float PI = 3.14159265359;
const float GRAVITY_CONST = 6;
const float OUT_FORCE_VALUE = 20;
const float MIN_PLAYER_RADIUS = 10;
const float W_RADIUS = 7;
const float MINI_RADIUS = 2;
const float BOMB_RADIUS = 25;
const float DIVIDE_FORCE = 40;

const int MAX_MINIS_ON_MAP = 10000;
const int MAX_BOMB_ON_MAP = 20;

}//namespace agario

#endif