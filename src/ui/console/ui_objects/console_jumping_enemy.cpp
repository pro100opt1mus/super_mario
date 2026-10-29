#include "console_jumping_enemy.hpp"
using biv::ConsoleJumpingEnemy;
ConsoleJumpingEnemy::ConsoleJumpingEnemy(const Coord& pos, int w, int h) : JumpingEnemy(pos, w, h) {}
char ConsoleJumpingEnemy::get_brush() const noexcept { return 'j'; }
