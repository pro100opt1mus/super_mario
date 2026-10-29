#pragma once
#include "ship.hpp"
#include "console_ui_obj_rect_adapter.hpp"
namespace biv {
    class ConsoleExitShip : public Ship, public ConsoleUIObjectRectAdapter {
    public:
        ConsoleExitShip(const Coord&, int width, int height);
        char get_brush() const noexcept override;
    };
}
