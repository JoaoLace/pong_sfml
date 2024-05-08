#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define window_width 800
#define window_height 600
#define window_size sf::VideoMode(window_width,window_height)
#define window_name "Pong SFML"
#define window_pos sf::Vector2i(600,300)
#define player_size sf::Vector2f(100,20)
#define player_initial_pos sf::Vector2f(window_width/2,450)

class Game
{
private:
    sf::RenderWindow *window;
    sf::RectangleShape *player;
    sf::CircleShape *ball;
    sf::SoundBuffer sound_bufferLose;
    sf::SoundBuffer sound_bufferPong;
    sf::Sound sound_lose;
    sf::Sound sound_pong;
    sf::Text score;
    sf::Text points;
    sf::Text end;
    sf::Font font;
    std::vector<sf::RectangleShape> *objects;
    float ball_speedY;
    float ball_speedX;
    int player_dir;
    int points_int;
    float player_acceleration;
    bool game_running;
    void render();
    void render_player();
    void render_objects();
    void render_ball();
    void render_text();
    void render_end();
    void update();
    void update_player();
    void update_events();
    void update_score();
    void update_ball();
    void init_vars();
    void init_player();
    void init_window();
    void init_text();
    void init_objects();
    void init_ball();
    void init_sounds();
    sf::Vector2f get_player_pos();
    sf::Text create_text(sf::Vector2f Position, std::string String, sf::Color Color, int size);
public:
    void run();

    Game();
    ~Game();
};
