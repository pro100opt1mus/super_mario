/**
	Летающий враг: парит в воздухе (гравитация на него не действует)
	и патрулирует участок карты в пределах заданной дальности полёта.

	Не наследуется от Enemy, т.к. Enemy - это ходячий враг: его конструктор
	и обработка коллизий жёстко задают поведение "ходьбы по кораблю".
*/

#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			float min_x;
			float max_x;

		public:
			FlyingEnemy(
				const Coord& top_left,
				const int width, const int height,
				const float flight_range
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
	};
}
