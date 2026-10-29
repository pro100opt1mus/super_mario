#include "console_ui_factory.hpp"

using biv::ConsoleUIFactory;

ConsoleUIFactory::ConsoleUIFactory(Game* game) : UIFactory(game) {}

void ConsoleUIFactory::clear_data() {
	game->remove_objs();
	if (game_map) game_map->remove_objs();
	mario.reset();
	boxes.clear();
	full_boxes.clear();
	ships.clear();
	enemies.clear();
	moneys.clear();
    flying_enemies.clear();
    jumping_enemies.clear();
    platforms.clear();
    exits.clear();
}

void ConsoleUIFactory::create_box(
	const Coord& top_left, const int width, const int height
) {
	ConsoleBox* box = new ConsoleBox(top_left, width, height);
	boxes.emplace_back(box);
	game->add_map_movable(box);
	game->add_static_obj(box);
	game_map->add_obj(box);
}

void ConsoleUIFactory::create_enemy(
	const Coord& top_left, const int width, const int height
) {
	ConsoleEnemy* enemy = new ConsoleEnemy(top_left, width, height);
	enemies.emplace_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void ConsoleUIFactory::create_full_box(
	const Coord& top_left, const int width, const int height
) {
	ConsoleFullBox* full_box = new ConsoleFullBox(top_left, width, height, this);
	full_boxes.emplace_back(full_box);
	game->add_collisionable(full_box);
	game->add_map_movable(full_box);
	game->add_static_obj(full_box);
	game_map->add_obj(full_box);
}

void ConsoleUIFactory::create_mario(
	const Coord& top_left, const int width, const int height
) {
	game->remove_collisionable(mario.get());
	game->remove_movable(mario.get());
	game->remove_mario();
	game_map->remove_obj(mario.get());
	mario.reset();
	
	mario = std::make_unique<ConsoleMario>(top_left, width, height);
	game->add_collisionable(mario.get());
	game->add_movable(mario.get());
	game->add_mario(mario.get());
	game_map->add_obj(mario.get());
}

void ConsoleUIFactory::create_money(
	const Coord& top_left, const int width, const int height
) {
	ConsoleMoney* money = new ConsoleMoney(top_left, width, height);
	moneys.emplace_back(money);
	game->add_map_movable(money);
	game->add_movable(money);
	game->add_collisionable(money);
	game_map->add_obj(money);
}

void ConsoleUIFactory::create_ship(
	const Coord& top_left, const int width, const int height
) {
	ConsoleShip* ship = new ConsoleShip(top_left, width, height);
	ships.emplace_back(ship);
	game->add_map_movable(ship);
	game->add_static_obj(ship);
	game_map->add_obj(ship);
}

biv::GameMap* ConsoleUIFactory::get_game_map(const int height, const int width) {
	if (game_map == nullptr) {
		game_map = std::make_unique<ConsoleGameMap>(height, width);
	}
	return game_map.get();
}

biv::Mario* ConsoleUIFactory::get_mario() {
	return mario.get();
}

ConsoleUIFactory::~ConsoleUIFactory() { clear_data(); }

template<class T>
void ConsoleUIFactory::collect(std::vector<std::unique_ptr<T>>& objects) {
    auto it = objects.begin();
    while (it != objects.end()) {
        T* obj = it->get();
        if (obj->is_active()) { ++it; continue; }
        game->remove_collisionable(obj);
        game->remove_map_movable(obj);
        game->remove_movable(obj);
        if (game_map) game_map->remove_obj(obj);
        it = objects.erase(it); // Destroy only after all registrations are gone.
    }
}
void ConsoleUIFactory::collect_inactive() {
    collect(enemies);
    collect(flying_enemies);
    collect(jumping_enemies);
    collect(moneys);
    // Opened FullBoxes stay owned, displayed and registered as solid blocks.
}

void ConsoleUIFactory::create_flying_enemy(const Coord& pos, int w, int h, float travel, float speed) {
    auto owner = std::make_unique<ConsoleFlyingEnemy>(pos, w, h, travel, speed);
    auto* obj = owner.get();
    flying_enemies.push_back(std::move(owner));
    game->add_map_movable(obj);
    game->add_movable(obj);
    game->add_collisionable(obj);
    game_map->add_obj(obj);
}

void ConsoleUIFactory::create_jumping_enemy(const Coord& pos, int w, int h) {
    auto owner = std::make_unique<ConsoleJumpingEnemy>(pos, w, h);
    auto* obj = owner.get();
    jumping_enemies.push_back(std::move(owner));
    game->add_map_movable(obj);
    game->add_movable(obj);
    game->add_collisionable(obj);
    game_map->add_obj(obj);
}

void ConsoleUIFactory::create_moving_platform(const Coord& pos, int w, int h, float travel, float speed) {
    auto owner = std::make_unique<ConsoleMovingPlatform>(pos, w, h, travel, speed);
    auto* obj = owner.get();
    platforms.push_back(std::move(owner));
    game->add_map_movable(obj);
    game->add_movable(obj);
    game->add_moving_support(obj);
    game_map->add_obj(obj);
}

void ConsoleUIFactory::create_exit_ship(const Coord& pos, int w, int h) {
    auto owner = std::make_unique<ConsoleExitShip>(pos, w, h);
    auto* obj = owner.get();
    exits.push_back(std::move(owner));
    game->add_map_movable(obj);
    game->add_static_obj(obj);
    game->set_exit(obj);
    game_map->add_obj(obj);
}
