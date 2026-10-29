#include "flying_enemy.hpp"
#include <algorithm>
#include <cmath>

using biv::FlyingEnemy;
FlyingEnemy::FlyingEnemy(const Coord& pos, int w, int h, float travel, float speed)
    : RectMapMovableAdapter(pos, w, h), patrol_left(pos.x),
      patrol_right(pos.x + std::max(0.0f, travel)), previous_x(pos.x) {
    hspeed = std::abs(speed);
}
biv::Rect FlyingEnemy::get_rect() const noexcept { return {top_left, width, height}; }
biv::Speed FlyingEnemy::get_speed() const noexcept { return {0, hspeed}; }
void FlyingEnemy::move_horizontally() noexcept {
    previous_x = top_left.x;
    top_left.x = std::max(patrol_left, std::min(patrol_right, top_left.x + hspeed));
    if (top_left.x >= patrol_right) hspeed = -std::abs(hspeed);
    else if (top_left.x <= patrol_left) hspeed = std::abs(hspeed);
}
void FlyingEnemy::move_vertically() noexcept {} // Constant altitude; no gravity.
void FlyingEnemy::move_map_offset(float dx) noexcept {
    RectMapMovableAdapter::move_map_offset(dx);
    patrol_left += dx;
    patrol_right += dx;
    previous_x += dx;
}
void FlyingEnemy::process_horizontal_static_collision(Rect*) noexcept {
    const float step = top_left.x - previous_x;
    top_left.x = previous_x;
    if (step > 0) hspeed = -std::abs(hspeed);
    else if (step < 0) hspeed = std::abs(hspeed);
}
void FlyingEnemy::process_vertical_static_collision(Rect*) noexcept {}
void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    if (mario->crosses_top_of(*this)) kill();
    else mario->kill();
}
