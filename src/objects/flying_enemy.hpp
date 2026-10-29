#pragma once
#include "collisionable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {
    class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
        float patrol_left;
        float patrol_right;
        float previous_x;
    public:
        FlyingEnemy(const Coord&, int width, int height, float travel, float speed = 0.3f);
        Rect get_rect() const noexcept override;
        Speed get_speed() const noexcept override;
        void move_horizontally() noexcept override;
        void move_vertically() noexcept override;
        void move_map_offset(float dx) noexcept override;
        void process_horizontal_static_collision(Rect*) noexcept override;
        void process_vertical_static_collision(Rect*) noexcept override;
        void process_mario_collision(Collisionable*) noexcept override;
    };
}
