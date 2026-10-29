/**
	- Какому паттерну проектирования соответствует UIFactory?
	- В каких случаях используется этот паттернн проектирования?
*/

#pragma once

#include "game.hpp"
#include "game_map.hpp"
#include "mario.hpp"

namespace biv {
	class UIFactory {
		protected:
			Game* game = nullptr;
			
		protected:
			UIFactory(Game* game) : game(game) {}

		public:
			virtual ~UIFactory() = default;
            virtual void clear_data() = 0;
            virtual void collect_inactive() = 0;
            virtual void create_flying_enemy(const Coord&, int width, int height,
                float travel, float speed = 0.3f) = 0;
            virtual void create_jumping_enemy(const Coord&, int width, int height) = 0;
            virtual void create_moving_platform(const Coord&, int width, int height,
                float travel, float speed = 0.4f) = 0;
            virtual void create_exit_ship(const Coord&, int width, int height) = 0;
			virtual void create_box(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_enemy(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_full_box(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_mario(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_money(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_ship(
				const Coord& top_left, const int width, const int height) = 0;
			virtual GameMap* get_game_map(const int height, const int width) = 0;
			virtual Mario* get_mario() = 0;
	};
}
