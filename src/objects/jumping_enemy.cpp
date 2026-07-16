#include "jumping_enemy.hpp"

#include "map_movable.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	// Враг не передвигается по горизонтали.
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		// Враг приземлился и тут же отталкивается для нового прыжка.
		top_left.y -= vspeed;
		vspeed = JUMP_SPEED;
	}
}
