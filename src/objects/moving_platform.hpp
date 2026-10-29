#pragma once
#include "ship.hpp"
#include "movable.hpp"
#include "moving_support.hpp"

namespace biv {
    class MovingPlatform : public Ship, public Movable, public MovingSupport {
        float route_left;
        float route_right;
        float delta_x = 0;
        Rect previous;
    public:
        MovingPlatform(const Coord&, int width, int height, float travel, float speed = 0.4f);
        void move_horizontally() noexcept override;
        void move_vertically() noexcept override;
        void move_map_offset(float dx) noexcept override;
        void remember_support_position() noexcept override;
        Rect get_previous_support_rect() const noexcept override;
        Rect get_support_rect() const noexcept override;
        float get_delta_x() const noexcept override;
    };
}
