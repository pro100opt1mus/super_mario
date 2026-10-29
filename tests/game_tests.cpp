#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "console_ui_factory.hpp"
#include "first_level.hpp"
#include "second_level.hpp"
#include "third_level.hpp"
#include "flying_enemy.hpp"
#include "jumping_enemy.hpp"
#include "moving_platform.hpp"

using namespace biv;
static int checks = 0;
#define CHECK(expr) do { ++checks; if (!(expr)) throw std::runtime_error( \
    std::string(__func__) + ":" + std::to_string(__LINE__) + ": " + #expr); } while (false)
static bool near(float a, float b, float eps = 0.002f) { return std::abs(a-b) < eps; }

struct Scene {
    Game game;
    ConsoleUIFactory factory{&game};
    GameMap* map = factory.get_game_map(30, 200);
    void mario(float x, float y) { factory.create_mario({x,y},3,3); }
    Mario* player() { return factory.get_mario(); }
    void input(char key) {
        auto* m = player();
        if (key == 'd') {
            m->move_map_left();
            if (!game.check_static_collisions(m)) game.move_map_left();
            m->move_map_right();
        } else if (key == 'a') {
            m->move_map_right();
            if (!game.check_static_collisions(m)) game.move_map_right();
            m->move_map_left();
        } else if (key == 'j') m->jump();
    }
    void frame(char key = 's') {
        game.begin_frame();
        input(key);
        game.move_objs_horizontally();
        game.check_horizontally_static_collisions();
        game.move_objs_vertically();
        game.check_mario_collision();
        game.check_vertically_static_collisions();
        game.land_on_moving_support();
        factory.collect_inactive();
    }
    void support(MovingPlatform& p) {
        game.add_map_movable(&p); game.add_movable(&p); game.add_moving_support(&p);
    }
};

void flight() {
    FlyingEnemy f({0,10},3,2,1,0.3f);
    for (int i=0;i<4;++i) { f.move_horizontally(); f.move_vertically(); }
    CHECK(near(f.get_x(),1)); CHECK(near(f.get_y(),10)); CHECK(f.get_speed().h<0);
    f.move_map_left(); f.move_map_offset(-9.25f);
    for (int i=0;i<100;++i) {
        f.move_horizontally(); f.move_vertically();
        CHECK(f.get_x()>=-10.251f && f.get_x()<=-9.249f); CHECK(near(f.get_y(),10));
    }
    FlyingEnemy blocked({0,10},3,2,20,0.6f);
    Rect wall({3,8},3,6);
    blocked.move_horizontally(); CHECK(blocked.has_collision(&wall));
    blocked.process_horizontal_static_collision(&wall);
    CHECK(near(blocked.get_x(),0)); CHECK(blocked.get_speed().h<0);
}

void jumping() {
    JumpingEnemy j({0,3},3,2); Rect floor({-10,10},40,2);
    int landings=0, takeoffs=0; bool was_rising=false;
    for (int i=0;i<300;++i) {
        j.remember_position(); j.move_horizontally(); j.move_vertically();
        if (j.has_collision(&floor)) { if (j.get_vspeed()>0.1f) ++landings; j.process_vertical_static_collision(&floor); }
        if (!was_rising && j.get_vspeed()<0) ++takeoffs;
        was_rising=j.get_vspeed()<0;
        CHECK(near(j.get_x(),0));
    }
    CHECK(landings>=3); CHECK(takeoffs>=3);
    j.move_map_offset(-12.5f); CHECK(near(j.get_x(),-12.5f));
    // Ceiling response must not count as a landing or launch a timed air jump.
    JumpingEnemy ceiling({0,8},3,2); ceiling.jump(); ceiling.move_vertically();
    Rect roof({-5,5},10,2); ceiling.process_vertical_static_collision(&roof);
    CHECK(near(ceiling.get_vspeed(),0)); CHECK(near(ceiling.get_y(),7));
    ceiling.move_vertically(); CHECK(ceiling.get_vspeed()>0);
    for(int i=0;i<30;++i) ceiling.move_vertically();
    CHECK(ceiling.get_vspeed()>0);
}

template<class E> void contacts(E& enemy) {
    Mario above({10,4},3,3);
    above.remember_position(); enemy.remember_position();
    above.move_vertical_offset(4); // Fast fall crosses the entire top edge.
    enemy.process_mario_collision(&above);
    CHECK(!enemy.is_active()); CHECK(above.is_active());
}
void enemy_contacts() {
    Enemy e({10,10},3,2); contacts(e);
    FlyingEnemy f({10,10},3,2,20); contacts(f);
    JumpingEnemy j({10,10},3,2); contacts(j);
    FlyingEnemy side({10,10},3,2,20); Mario m({9,9},3,3);
    side.remember_position(); m.remember_position(); m.move_vertical_offset(0.5f);
    side.process_mario_collision(&m); CHECK(!m.is_active()); CHECK(side.is_active());
    JumpingEnemy below({10,10},3,2); Mario under({10,12},3,3);
    under.remember_position(); below.remember_position(); under.move_vertical_offset(-1);
    below.process_mario_collision(&under); CHECK(!under.is_active()); CHECK(below.is_active());
    Rect p0({10,4},3,3), p1({10,8},3,3), e0({10,9},3,2), e1({10,7},3,2);
    CHECK(Collisionable::top_crossing(p0,p1,e0,e1)>=0);
    CHECK(Collisionable::top_crossing(p0,p1,Rect({20,9},3,2),Rect({20,7},3,2))<0);
    CHECK(Collisionable::top_crossing(Rect({0,8},3,3),Rect({0,9},3,3),e0,e1)<0);
}

void platform_motion() {
    MovingPlatform p({0,10},8,2,1,0.3f);
    float last=p.get_x();
    for(int i=0;i<4;++i) { p.move_horizontally(); CHECK(near(p.get_delta_x(),p.get_x()-last)); last=p.get_x(); }
    CHECK(near(p.get_x(),1)); CHECK(near(p.get_delta_x(),0.1f));
    for(int i=0;i<4;++i) p.move_horizontally();
    CHECK(near(p.get_x(),0)); CHECK(near(p.get_delta_x(),-0.1f));
    p.move_map_offset(-12.75f);
    for(int i=0;i<50;++i) { p.move_horizontally(); CHECK(p.get_x()>=-12.751f && p.get_x()<=-11.749f); }
    CHECK(near(p.get_y(),10));
}
void platform_riding() {
    Scene s; s.mario(10,17); MovingPlatform p({8,20},8,2,80,0.3f); s.support(p);
    for(int i=0;i<150;++i) { s.frame(); CHECK(near(s.player()->get_y(),17)); CHECK(near(p.get_x(),8)); }
    CHECK(near(s.player()->get_x(),10));
    s.frame('j'); CHECK(s.player()->get_vspeed()<0); CHECK(near(p.get_x(),8.3f));
    s.frame(); CHECK(near(p.get_x(),8.6f)); // No stored velocity impulse on Mario.
    CHECK(near(s.player()->get_x(),10));

    Scene walk; walk.mario(10,17); MovingPlatform p2({8,20},8,2,80,0.3f); walk.support(p2);
    for(int i=0;i<10;++i) walk.frame('d');
    CHECK(walk.player()->get_vspeed()>0); CHECK(walk.player()->get_y()>17);
    Scene left; left.mario(10,17); MovingPlatform p3({8,20},8,2,80,0.3f); left.support(p3);
    left.frame('a'); CHECK(near(p3.get_x(),9)); CHECK(near(left.player()->get_vspeed(),0));
}
void one_way_and_walls() {
    Scene landing; landing.mario(10,10); MovingPlatform p({8,20},8,2,0,0); landing.support(p);
    for(int i=0;i<30;++i) landing.frame();
    CHECK(near(landing.player()->get_y(),17)); CHECK(near(landing.player()->get_vspeed(),0));
    Scene below; below.mario(10,21); MovingPlatform p2({8,20},8,2,0,0); below.support(p2);
    below.frame('j'); CHECK(below.player()->get_vspeed()<0); CHECK(below.player()->get_y()>17);
    Scene side; side.mario(6,19); MovingPlatform p3({8,20},8,2,0,0); side.support(p3);
    side.frame(); CHECK(side.player()->get_y()>19);
    Scene walls; walls.mario(10,17); MovingPlatform p4({8,20},8,2,80,0.7f); walls.support(p4);
    Ship wall({13.2f,10},5,10); walls.game.add_static_obj(&wall); walls.game.add_map_movable(&wall);
    walls.frame(); CHECK(near(wall.get_x(),13));
    for(int i=0;i<4;++i) { walls.frame(); CHECK(wall.get_x()>=12.999f); }
    Scene multiple; multiple.mario(10,17);
    MovingPlatform lower({8,21},8,2,20,0.8f), upper({8,20},8,2,20,0.2f);
    multiple.support(lower); multiple.support(upper);
    multiple.frame(); CHECK(near(upper.get_x(),8)); CHECK(near(lower.get_x(),8.6f));
    CHECK(near(multiple.player()->get_y(),17));
}

void exits_and_lifetime() {
    Scene s; s.mario(10,7); s.factory.create_ship({0,10},30,2);
    for(int i=0;i<10;++i)s.frame(); CHECK(!s.game.is_level_end());
    s.factory.create_exit_ship({0,10},30,2);
    s.factory.create_ship({40,10},10,2); // Exit must not depend on creation order.
    for(int i=0;i<10&&!s.game.is_level_end();++i)s.frame(); CHECK(s.game.is_level_end());
    s.player()->kill(); s.game.check_vertically_static_collisions(); CHECK(!s.game.is_level_end());
    s.factory.clear_data(); CHECK(!s.game.is_level_end()); s.game.check_vertically_static_collisions();
    s.mario(10,7); s.frame(); CHECK(!s.game.is_level_end());
    for(int i=0;i<100;++i) {
        FirstLevel first(&s.factory);
        auto* second=first.get_next(); auto* third=second->get_next();
        CHECK(!first.is_final()); CHECK(!second->is_final()); CHECK(third->is_final()); CHECK(!third->get_next());
        s.player()->kill(); third->restart(); CHECK(s.player()->is_active()); CHECK(!s.game.is_level_end());
        s.frame(); s.map->refresh(); s.factory.clear_data();
    }
    // Open a FullBox, collect its Money, then verify the box remains solid.
    s.mario(10,12); s.factory.create_full_box({10,10},5,3); s.player()->jump();
    s.game.begin_frame(); s.game.check_mario_collision(); s.factory.collect_inactive();
    s.map->refresh(); CHECK(s.game.check_static_collisions(s.player()));
    for(int i=0;i<20;++i)s.frame();
    s.factory.clear_data();
}

void cleanup_and_crossing_order() {
    Scene s;
    for (int kind=0;kind<4;++kind) {
        s.factory.clear_data(); s.mario(10,4);
        if (kind==0) s.factory.create_enemy({10,10},3,2);
        if (kind==1) s.factory.create_flying_enemy({10,10},3,2,10);
        if (kind==2) s.factory.create_jumping_enemy({10,10},3,2);
        if (kind==3) s.factory.create_money({10,10},3,2);
        s.game.begin_frame(); s.player()->move_vertical_offset(4);
        s.game.check_mario_collision();
        s.factory.collect_inactive();
        for(int i=0;i<5;++i) { s.frame('d'); s.map->refresh(); }
        CHECK(s.player()->is_active());
    }
    for(int i=0;i<50;++i) {
        s.factory.clear_data(); s.mario(10,17);
        s.factory.create_moving_platform({8,20},8,2,50);
        s.frame(); s.factory.clear_data(); s.map->refresh();
        s.mario(10,5); s.frame(); CHECK(!s.game.is_level_end());
    }
    Scene multiple; multiple.mario(10,5);
    MovingPlatform lower({8,20},8,2,0,0), upper({8,18},8,2,0,0);
    multiple.support(lower); multiple.support(upper);
    multiple.game.begin_frame(); multiple.player()->move_vertical_offset(15);
    multiple.game.land_on_moving_support(); CHECK(near(multiple.player()->get_y(),15));
    Scene overlap; overlap.mario(10,17);
    MovingPlatform p({8,20},8,2,10,0.3f); overlap.support(p);
    Ship wall({12.8f,10},5,10); overlap.game.add_static_obj(&wall); overlap.game.add_map_movable(&wall);
    overlap.game.begin_frame(); overlap.game.move_objs_horizontally();
    CHECK(near(wall.get_x(),12.8f));
}

void full_route(const std::string& dir) {
    Scene s; FirstLevel first(&s.factory); GameLevel* level=&first;
    for(int number=1;number<=3;++number) {
        std::ifstream inputs(dir+"/level"+std::to_string(number)+".inputs");
        CHECK(inputs.good()); char key; int count; bool completed=false;
        while(!completed && inputs>>key>>count) for(int i=0;i<count;++i) {
            s.frame(key);
            CHECK(s.player()->is_active()); CHECK(!s.map->is_below_map(s.player()->get_top()));
            if(s.game.is_level_end()) { completed=true; break; }
        }
        CHECK(completed); CHECK(level->is_final()==(number==3));
        if(number<3) {
            level=level->get_next(); s.game.start_level();
            CHECK(!s.game.is_level_end()); CHECK(s.player()->is_active());
        } else {
            s.game.finish(); CHECK(s.game.is_finished());
        }
    }
    std::cout<<"PASS: continuous 1 -> 2 -> 3, final exit and finish\n";
}

// Diagnostic playback uses the same input and update phases as main. The
// marker observes scrolling only; it cannot move Mario or finish a level.
int play(int level, const char* file) {
    Scene s; std::unique_ptr<GameLevel> root;
    if(level==1)root=std::make_unique<FirstLevel>(&s.factory);
    else if(level==2)root=std::make_unique<SecondLevel>(&s.factory);
    else root=std::make_unique<ThirdLevel>(&s.factory);
    RectMapMovableAdapter marker({0,0},1,1); s.game.add_map_movable(&marker);
    std::ifstream input(file); if(!input) return 3;
    int n, frame=0; char key;
    while(input>>key>>n) for(int i=0;i<n;++i) {
        s.frame(key); ++frame;
        if(frame%5==0 || key=='j' || s.game.is_level_end() || !s.player()->is_active())
            std::cout<<frame<<" x="<<s.player()->get_x()-marker.get_x()<<" y="<<s.player()->get_y()
                <<" v="<<s.player()->get_vspeed()<<" alive="<<s.player()->is_active()<<" exit="<<s.game.is_level_end()<<'\n';
        if(!s.player()->is_active() || s.map->is_below_map(s.player()->get_top())) return 2;
        if(s.game.is_level_end()) { std::cout<<"LEVEL "<<level<<" COMPLETE at frame "<<frame<<'\n'; return 0; }
    }
    return 1;
}
int main(int argc, char** argv) {
    if(argc==4 && std::string(argv[1])=="--play") return play(std::atoi(argv[2]),argv[3]);
    try {
        flight(); jumping(); enemy_contacts(); platform_motion(); platform_riding();
        one_way_and_walls(); exits_and_lifetime(); cleanup_and_crossing_order();
        full_route(REPLAY_DIR);
        std::cout<<"PASS: "<<checks<<" checks\n";
    } catch(const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
