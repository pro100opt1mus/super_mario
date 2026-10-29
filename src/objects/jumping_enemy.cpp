#include "jumping_enemy.hpp"

using biv::JumpingEnemy;
JumpingEnemy::JumpingEnemy(const Coord& pos, int w, int h)
    : RectMapMovableAdapter(pos, w, h) {}
biv::Rect JumpingEnemy::get_rect() const noexcept { return {top_left, width, height}; }
biv::Speed JumpingEnemy::get_speed() const noexcept { return {vspeed, 0}; }
void JumpingEnemy::move_vertically() noexcept {
    if (grounded) {
        // This enemy has no horizontal motion; its static support scrolls with it.
        // Keep the landing speed at zero throughout the waiting interval.
        if (wait_frames-- > 0) return;
        jump();
        grounded = false;
    }
    Movable::move_vertically();
}
void JumpingEnemy::process_horizontal_static_collision(Rect*) noexcept {}
void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    if (vspeed > 0) {
        top_left.y = obj->get_y() - height;
        vspeed = 0;
        if (!grounded) { grounded = true; wait_frames = WAIT_FRAMES; }
    } else if (vspeed < 0) {
        top_left.y = obj->get_y() + obj->get_height();
        vspeed = 0;
        grounded = false; // A ceiling never starts the landing timer.
    }
}
void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    if (mario->crosses_top_of(*this)) kill();
    else mario->kill();
}
