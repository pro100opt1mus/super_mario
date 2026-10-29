#include "game.hpp"

#include <algorithm>
#include <cmath>

using biv::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
	collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
	map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
	mario = obj;
}

void Game::add_movable(Movable* obj) {
	movable_objs.push_back(obj);
}

void Game::add_static_obj(Rect* obj) {
	static_objs.push_back(obj);
}

void Game::check_horizontally_static_collisions() noexcept {
	for (Collisionable* obj: collisionable_objs) {
        if (!obj->is_active()) continue;
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_horizontal_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::check_mario_collision() {
    if (!mario || !mario->is_active()) return;
    // FullBox may append Money. An index and a fixed count avoid invalidating
    // an iterator; newly created objects enter collision checks next frame.
    const auto count = collisionable_objs.size();
    for (std::size_t i = 0; i < count; ++i) {
        Collisionable* obj = collisionable_objs[i];
        if (obj == mario || !obj->is_active()) continue;
        if (obj->has_collision(mario) || mario->crosses_top_of(*obj)) {
            obj->process_mario_collision(mario);
            if (!mario->is_active()) break;
        }
    }
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
	for (Rect* static_obj: static_objs) {
		if (obj->has_collision(static_obj)) {
			return true;
		}
	}
	return false;
}

void Game::check_vertically_static_collisions() noexcept {
    is_level_end_ = mario && mario->is_active() && exit_ship
        && mario->has_collision(exit_ship);
	
	for (Collisionable* obj: collisionable_objs) {
        if (!obj->is_active()) continue;
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_vertical_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::finish() noexcept {
	is_finished_ = true;
}

bool Game::is_finished() const noexcept {
	return is_finished_;
}

bool Game::is_level_end() const noexcept {
	return is_level_end_;
}

void Game::move_map_left() noexcept {
    move_map_offset(-MapMovable::MAP_STEP);
}

void Game::move_map_right() noexcept {
    move_map_offset(MapMovable::MAP_STEP);
}

void Game::move_objs_horizontally() noexcept {
    // This pointer exists only during this phase, never across frames/cleanup.
    MovingSupport* support = nullptr;
    if (mario && mario->is_active() && mario->get_vspeed() == 0) {
        for (MovingSupport* candidate : moving_supports) {
            const Rect r = candidate->get_support_rect();
            if (std::abs(mario->get_y() + mario->get_height() - r.get_y()) < 0.001f
                && mario->get_x() + mario->get_width() > r.get_x()
                && mario->get_x() < r.get_x() + r.get_width()) {
                support = candidate;
                break;
            }
        }
    }
    for (Movable* obj : movable_objs) obj->move_horizontally();
    if (support) move_map_offset(-safe_carry_delta(support->get_delta_x()));
}

void Game::move_objs_vertically() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_vertically();
	}
}

void Game::remove_collisionable(Collisionable* obj) {
	remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
	remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
	mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
	remove_obj(movable_objs, obj);
}

void Game::remove_objs() {
	collisionable_objs.clear();
	map_movable_objs.clear();
	movable_objs.clear();
	static_objs.clear();
    moving_supports.clear();
    exit_ship = nullptr;
    is_level_end_ = false;
	remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
    if (exit_ship == obj) { exit_ship = nullptr; is_level_end_ = false; }
	remove_obj(static_objs, obj);
}

void Game::start_level() noexcept {
	is_level_end_ = false;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
	container.erase(
		std::remove(
			container.begin(), container.end(), obj
		), 
		container.end()
	);
}

void Game::begin_frame() noexcept {
    for (Collisionable* obj : collisionable_objs) obj->remember_position();
    for (MovingSupport* obj : moving_supports) obj->remember_support_position();
}
void Game::add_moving_support(MovingSupport* obj) { moving_supports.push_back(obj); }
void Game::remove_moving_support(MovingSupport* obj) { remove_obj(moving_supports, obj); }
void Game::set_exit(Rect* obj) noexcept { exit_ship = obj; is_level_end_ = false; }
void Game::move_map_offset(float dx) noexcept {
    for (MapMovable* obj : map_movable_objs) obj->move_map_offset(dx);
}
float Game::safe_carry_delta(float dx) const noexcept {
    const float left = mario->get_x();
    const float right = left + mario->get_width();
    for (Rect* wall : static_objs) {
        if (mario->get_y() + mario->get_height() <= wall->get_y()
            || mario->get_y() >= wall->get_y() + wall->get_height()) continue;
        // Original keyboard collision uses rounded edges. If it left a small
        // float overlap, carrying must not deepen that overlap.
        if (wall->get_x() < right && wall->get_x() + wall->get_width() > left)
            return 0;
        if (dx > 0 && wall->get_x() >= right)
            dx = std::min(dx, wall->get_x() - right);
        else if (dx < 0 && wall->get_x() + wall->get_width() <= left)
            dx = std::max(dx, wall->get_x() + wall->get_width() - left);
    }
    return dx;
}
void Game::land_on_moving_support() noexcept {
    if (!mario || !mario->is_active() || mario->get_vspeed() < 0) return;
    MovingSupport* first = nullptr;
    float first_time = 2;
    for (MovingSupport* support : moving_supports) {
        const Rect now = support->get_support_rect();
        const float t = Collisionable::top_crossing(mario->get_previous_rect(), mario->get_rect(),
            support->get_previous_support_rect(), now);
        // Crossing alone is insufficient if the player has already walked off.
        if (t >= 0 && t < first_time && mario->get_x() + mario->get_width() > now.get_x()
            && mario->get_x() < now.get_x() + now.get_width()) {
            first_time = t;
            first = support;
        }
    }
    if (first) mario->land_on(first->get_support_rect().get_y());
}
