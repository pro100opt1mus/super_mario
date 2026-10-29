#include "console_moving_platform.hpp"
using biv::ConsoleMovingPlatform;
ConsoleMovingPlatform::ConsoleMovingPlatform(const Coord& pos, int w, int h, float travel, float speed) : MovingPlatform(pos, w, h, travel, speed) {}
char ConsoleMovingPlatform::get_brush() const noexcept { return '='; }
