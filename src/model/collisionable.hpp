#pragma once

#include "rect.hpp"
#include "speed.hpp"

namespace biv {
	class Collisionable {
		protected:
			bool is_active_ = true;
			Rect previous_rect{{0, 0}, 0, 0};
			bool has_previous_rect = false;

		public:
			void remember_position() noexcept;
            Rect get_previous_rect() const noexcept;
            bool crosses_top_of(const Collisionable& other) const noexcept;
            // Returns time of the first top crossing in [0,1], or -1.
            static float top_crossing(const Rect& before, const Rect& after,
                const Rect& support_before, const Rect& support_after) noexcept;
            bool has_collision(Rect*) const noexcept;
			bool is_active() const noexcept;
			void kill() noexcept;

			virtual Rect get_rect() const noexcept = 0;
			virtual Speed get_speed() const noexcept = 0;

			virtual void process_horizontal_static_collision(Rect*) noexcept = 0;
			virtual void process_mario_collision(Collisionable*) noexcept = 0;
			virtual void process_vertical_static_collision(Rect*) noexcept = 0;
	};
}
