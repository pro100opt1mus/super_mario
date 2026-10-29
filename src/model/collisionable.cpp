#include "collisionable.hpp"

using biv::Collisionable;

bool Collisionable::has_collision(Rect* obj) const noexcept {
	Rect myself = get_rect();
	return (
		myself.get_right() > obj->get_left() &&
		myself.get_left() < obj->get_right() && 
		myself.get_bottom() > obj->get_top() && 
		myself.get_top() < obj->get_bottom()
	);
}

bool Collisionable::is_active() const noexcept {
	return is_active_;
}

void Collisionable::kill() noexcept {
	is_active_ = false;
}

void Collisionable::remember_position() noexcept {
    previous_rect = get_rect();
    has_previous_rect = true;
}

biv::Rect Collisionable::get_previous_rect() const noexcept {
    return has_previous_rect ? previous_rect : get_rect();
}

float Collisionable::top_crossing(const Rect& before, const Rect& after,
    const Rect& support_before, const Rect& support_after) noexcept {
    const float old_gap = before.get_y() + before.get_height() - support_before.get_y();
    const float new_gap = after.get_y() + after.get_height() - support_after.get_y();
    const float relative_fall = new_gap - old_gap;
    if (old_gap > 0.001f || new_gap < 0 || relative_fall <= 0) return -1;
    const float t = old_gap < 0 ? -old_gap / relative_fall : 0;
    const float left = before.get_x() + (after.get_x() - before.get_x()) * t;
    const float support_left = support_before.get_x()
        + (support_after.get_x() - support_before.get_x()) * t;
    if (left + before.get_width() <= support_left
        || left >= support_left + support_before.get_width()) return -1;
    return t;
}

bool Collisionable::crosses_top_of(const Collisionable& other) const noexcept {
    return top_crossing(get_previous_rect(), get_rect(),
        other.get_previous_rect(), other.get_rect()) >= 0;
}
