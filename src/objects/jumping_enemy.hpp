#pragma once
#include "collisionable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {
    class JumpingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
        static constexpr int WAIT_FRAMES = 24;
        int wait_frames = 0;
        bool grounded = false;
    public:
        JumpingEnemy(const Coord&, int width, int height);
        Rect get_rect() const noexcept override;
        Speed get_speed() const noexcept override;
        void move_vertically() noexcept override;
        void process_horizontal_static_collision(Rect*) noexcept override;
        void process_vertical_static_collision(Rect*) noexcept override;
        void process_mario_collision(Collisionable*) noexcept override;
    };
}
