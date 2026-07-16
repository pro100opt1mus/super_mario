/**
	Передвигающаяся платформа: курсирует по горизонтали над морем
	в пределах заданного маршрута. Марио может запрыгнуть на неё,
	и платформа перевезёт его по карте.

	Платформа одновременно:
	- статический объект (на неё можно встать, как на корабль);
	- движущийся объект (сама передвигается по маршруту);
	- collisionable (чтобы узнавать, что Марио стоит на ней, и везти его).
*/

#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class MovingPlatform : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			float min_x;
			float max_x;

			Collisionable* rider = nullptr;

		public:
			MovingPlatform(
				const Coord& top_left,
				const int width, const int height,
				const float travel_range
			);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void move_map_left() noexcept override;
			void move_map_right() noexcept override;

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;

		private:
			bool is_riding(Collisionable*) const noexcept;
	};
}
