#include "flying_enemy.hpp"

#include <cmath>

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
	const Coord& top_left,
	const int width, const int height,
	const float flight_range
) : RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.3;
	min_x = top_left.x;
	max_x = top_left.x + flight_range;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::move_map_left() noexcept {
	RectMapMovableAdapter::move_map_left();
	// Границы полёта заданы в координатах карты,
	// поэтому двигаются вместе с ней.
	min_x -= MapMovable::MAP_STEP;
	max_x -= MapMovable::MAP_STEP;
}

void FlyingEnemy::move_map_right() noexcept {
	RectMapMovableAdapter::move_map_right();
	min_x += MapMovable::MAP_STEP;
	max_x += MapMovable::MAP_STEP;
}

void FlyingEnemy::move_horizontally() noexcept {
	top_left.x += hspeed;

	// Разворот на границах дальности полёта.
	if (top_left.x <= min_x) {
		hspeed = std::abs(hspeed);
	} else if (top_left.x + width >= max_x) {
		hspeed = -std::abs(hspeed);
	}
}

void FlyingEnemy::move_vertically() noexcept {
	// Враг летает: гравитация на него не действует.
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	top_left.x += hspeed;
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	// Враг не падает, поэтому вертикальные коллизии не обрабатываются.
}
