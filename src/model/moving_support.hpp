#pragma once
#include "rect.hpp"

namespace biv {
    // A non-owning role: Game never retains a rider pointer across frames.
    class MovingSupport {
    public:
        virtual void remember_support_position() noexcept = 0;
        virtual Rect get_previous_support_rect() const noexcept = 0;
        virtual Rect get_support_rect() const noexcept = 0;
        virtual float get_delta_x() const noexcept = 0;
    };
}
