#include "moving_platform.hpp"
#include <algorithm>
#include <cmath>

using biv::MovingPlatform;
MovingPlatform::MovingPlatform(const Coord& pos, int w, int h, float travel, float speed)
    : Ship(pos, w, h), route_left(pos.x), route_right(pos.x + std::max(0.0f, travel)),
      previous(pos, w, h) { hspeed = std::abs(speed); }
void MovingPlatform::move_horizontally() noexcept {
    const float old_x = top_left.x;
    top_left.x = std::max(route_left, std::min(route_right, old_x + hspeed));
    delta_x = top_left.x - old_x;
    if (top_left.x >= route_right) hspeed = -std::abs(hspeed);
    else if (top_left.x <= route_left) hspeed = std::abs(hspeed);
}
void MovingPlatform::move_vertically() noexcept {}
void MovingPlatform::move_map_offset(float dx) noexcept {
    Ship::move_map_offset(dx);
    route_left += dx;
    route_right += dx;
}
void MovingPlatform::remember_support_position() noexcept { previous = get_support_rect(); }
biv::Rect MovingPlatform::get_previous_support_rect() const noexcept { return previous; }
biv::Rect MovingPlatform::get_support_rect() const noexcept { return {top_left, width, height}; }
float MovingPlatform::get_delta_x() const noexcept { return delta_x; }
