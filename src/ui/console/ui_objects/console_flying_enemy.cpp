#include "console_flying_enemy.hpp"
using biv::ConsoleFlyingEnemy;
ConsoleFlyingEnemy::ConsoleFlyingEnemy(const Coord& pos, int w, int h, float travel, float speed) : FlyingEnemy(pos, w, h, travel, speed) {}
char ConsoleFlyingEnemy::get_brush() const noexcept { return 'f'; }
