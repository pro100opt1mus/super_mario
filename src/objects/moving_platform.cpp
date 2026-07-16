#include "moving_platform.hpp"

#include <cmath>

#include "map_movable.hpp"

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
	const Coord& top_left,
	const int width, const int height,
	const float travel_range
) : RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.3;
	min_x = top_left.x;
	max_x = top_left.x + travel_range;
}

biv::Rect MovingPlatform::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed MovingPlatform::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void MovingPlatform::move_map_left() noexcept {
	RectMapMovableAdapter::move_map_left();
	// Маршрут задан в координатах карты, поэтому двигается вместе с ней.
	min_x -= MapMovable::MAP_STEP;
	max_x -= MapMovable::MAP_STEP;
}

void MovingPlatform::move_map_right() noexcept {
	RectMapMovableAdapter::move_map_right();
	min_x += MapMovable::MAP_STEP;
	max_x += MapMovable::MAP_STEP;
}

void MovingPlatform::move_horizontally() noexcept {
	top_left.x += hspeed;

	if (rider) {
		if (is_riding(rider)) {
			// Марио стоит на платформе - едет вместе с ней.
			Movable* movable_rider = dynamic_cast<Movable*>(rider);
			if (movable_rider) {
				movable_rider->move_horizontal_offset(hspeed);
			}
		} else {
			rider = nullptr;
		}
	}

	// Разворот на границах маршрута.
	if (top_left.x <= min_x) {
		hspeed = std::abs(hspeed);
	} else if (top_left.x + width >= max_x) {
		hspeed = -std::abs(hspeed);
	}
}

void MovingPlatform::move_vertically() noexcept {
	// Платформа висит в воздухе: гравитация на неё не действует.
}

void MovingPlatform::process_horizontal_static_collision(Rect* obj) noexcept {
	// Маршрут платформы ограничен min_x/max_x,
	// столкновения со статикой (в т.ч. с самой собой) не обрабатываются.
}

void MovingPlatform::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v >= 0) {
		// Марио приземлился на платформу сверху.
		rider = mario;
	}
}

void MovingPlatform::process_vertical_static_collision(Rect* obj) noexcept {
	// Платформа не падает, поэтому вертикальные коллизии не обрабатываются.
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
bool MovingPlatform::is_riding(Collisionable* obj) const noexcept {
	Rect obj_rect = obj->get_rect();
	return (
		obj_rect.get_right() > get_left() &&
		obj_rect.get_left() < get_right() &&
		obj_rect.get_bottom() >= get_top() - 1 &&
		obj_rect.get_bottom() <= get_top() + 2
	);
}
