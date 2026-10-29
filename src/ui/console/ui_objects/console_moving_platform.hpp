#pragma once
#include "moving_platform.hpp"
#include "console_ui_obj_rect_adapter.hpp"
namespace biv {
    class ConsoleMovingPlatform : public MovingPlatform, public ConsoleUIObjectRectAdapter {
    public:
        ConsoleMovingPlatform(const Coord&, int width, int height, float travel, float speed);
        char get_brush() const noexcept override;
    };
}
