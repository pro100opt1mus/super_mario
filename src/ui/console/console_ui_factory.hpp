#pragma once
#include <memory>
#include "console_flying_enemy.hpp"
#include "console_jumping_enemy.hpp"
#include "console_moving_platform.hpp"
#include "console_exit_ship.hpp"

#include "console_box.hpp"
#include "console_enemy.hpp"
#include "console_full_box.hpp"
#include "console_game_map.hpp"
#include "console_mario.hpp"
#include "console_money.hpp"
#include "console_ship.hpp"
#include "ui_factory.hpp"

namespace biv {
	class ConsoleUIFactory : public UIFactory {
		private:
			std::unique_ptr<ConsoleGameMap> game_map;
			std::vector<std::unique_ptr<ConsoleBox>> boxes;
			std::vector<std::unique_ptr<ConsoleFullBox>> full_boxes;
			std::vector<std::unique_ptr<ConsoleShip>> ships;
			std::unique_ptr<ConsoleMario> mario;
			std::vector<std::unique_ptr<ConsoleEnemy>> enemies;
			std::vector<std::unique_ptr<ConsoleMoney>> moneys;

		    std::vector<std::unique_ptr<ConsoleFlyingEnemy>> flying_enemies;
            std::vector<std::unique_ptr<ConsoleJumpingEnemy>> jumping_enemies;
            std::vector<std::unique_ptr<ConsoleMovingPlatform>> platforms;
            std::vector<std::unique_ptr<ConsoleExitShip>> exits;
            template<class T> void collect(std::vector<std::unique_ptr<T>>& objects);

        public:
            ~ConsoleUIFactory() override;
            void collect_inactive() override;
            void create_flying_enemy(const Coord&, int, int, float, float = 0.3f) override;
            void create_jumping_enemy(const Coord&, int, int) override;
            void create_moving_platform(const Coord&, int, int, float, float = 0.4f) override;
            void create_exit_ship(const Coord&, int, int) override;
            ConsoleUIFactory(Game* game);
			
			void clear_data() override;
			void create_box(
				const Coord& top_left, const int width, const int height
			) override;
			void create_enemy(
				const Coord& top_left, const int width, const int height
			) override;
			void create_full_box(
				const Coord& top_left, const int width, const int height
			) override;
			void create_mario(
				const Coord& top_left, const int width, const int height
			) override;
			void create_money(
				const Coord& top_left, const int width, const int height
			) override;
			void create_ship(
				const Coord& top_left, const int width, const int height
			) override;
			GameMap* get_game_map(const int height, const int width) override;
			Mario* get_mario() override;
	};
}
