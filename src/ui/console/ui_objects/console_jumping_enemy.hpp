#pragma once
#include "jumping_enemy.hpp"
#include "console_ui_obj_rect_adapter.hpp"
namespace biv {
    class ConsoleJumpingEnemy : public JumpingEnemy, public ConsoleUIObjectRectAdapter {
    public:
        ConsoleJumpingEnemy(const Coord&, int width, int height);
        char get_brush() const noexcept override;
    };
}
