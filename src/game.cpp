#include "../lib/game.hpp"
void Game::init_text()
{
    if (!font.loadFromFile("./assets/JetBrainsMono-Bold-Italic.ttf"))
    {
        std::cout << "ERROR: Could not load font from ../assets/JetBrainsMono-Bold-Italic.ttf";
    }

    score = create_text(sf::Vector2f(650, 550), "Score: ", sf::Color::White, 24);
    points = create_text(sf::Vector2f(750, 550), std::to_string(points_int), sf::Color::White, 24);
    end = create_text(sf::Vector2f(300, window_height / 2), "GAME OVER", sf::Color::Red, 32);
}
void Game::init_sounds()
{
    if (!sound_bufferLose.loadFromFile("./assets/lose.wav"))
    {
        std::cout << "ERROR: Could not load audio from: ../assests/lose.wav";
    }
    if (!sound_bufferPong.loadFromFile("./assets/pong.wav"))
    {
        std::cout << "ERROR: Could not load audio from: ../assests/pong.wav";
    }
    sound_lose.setBuffer(sound_bufferLose);
    sound_pong.setBuffer(sound_bufferPong);
}
void Game::init_ball()
{
    ball = new sf::CircleShape(5);
    ball->setPosition(window_width / 2, window_height / 2);
}
void Game::init_objects()
{
    objects = new std::vector<sf::RectangleShape>();

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            sf::RectangleShape *temp = new sf::RectangleShape(player_size);
            temp->setPosition(i * 160 + 30, j * 50);
            objects->push_back(*temp);
        }
    }
}
void Game::init_window()
{
    window = new sf::RenderWindow(window_size, window_name, sf::Style::Titlebar);
    window->setPosition(window_pos);
    window->setFramerateLimit(30);
}
void Game::init_player()
{
    player = new sf::RectangleShape(player_size);
    player->setPosition(player_initial_pos);
}
void Game::init_vars()
{
    game_running = true;
    ball_speedY = 6;
    ball_speedX = 0;
    player_acceleration = 1;
    player_dir = 0;
    points_int = 0;
}
void Game::update()
{
    update_events();
    update_ball();
    update_player();
    update_score();
}
void Game::update_events()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            game_running = !game_running;
        }
    }
}
void Game::update_score()
{
    points.setString(std::to_string(points_int));
}
void Game::update_ball()
{
    ball->move(ball_speedX, ball_speedY);
    if (ball->getGlobalBounds().intersects(player->getGlobalBounds()))
    {
        ball_speedY = ball_speedY * -1;
        ball_speedX *= player_dir;
        ball_speedX += 2;
        ball_speedY += 2;
        sound_pong.play();
    }
    unsigned counter = 0;
    for (auto &x : *objects)
    {
        if (ball->getGlobalBounds().intersects(x.getGlobalBounds()))
        {
            sound_pong.play();
            ball_speedY = ball_speedY * -1;
            ball_speedX += 2;
            ball_speedY += 2;
            objects->erase(objects->begin() + counter);
            points_int += 5;
        }
        ++counter;
    }
    if (ball->getPosition().x >= window_width - 3)
    {
        ball_speedX += 2;
        ball_speedX *= -1;
        sound_pong.play();
    }
    if (ball->getPosition().x <= 0)
    {
        ball_speedX += 2;
        ball_speedX *= -1;
        sound_pong.play();
    }
    if (ball->getPosition().y >= window_height)
    {
        sound_lose.play();
        game_running = false;
    }
    if (ball->getPosition().y <= 0)
    {
        ball_speedY *= -1;
        ball_speedY += 2;
        sound_pong.play();
    }
}
void Game::update_player()
{
    player_acceleration = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        player_acceleration += 0.5f;
        player->move(-6.f * player_acceleration, 0);
        player_dir = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        player_acceleration += 0.5f;
        player->move(6.f * player_acceleration, 0);
        player_dir = 1;
    }
    if (player->getPosition().x >= window_width - player_size.x)
    {
        player->setPosition(window_width - player_size.x, player_initial_pos.y);
    }
    else if (player->getPosition().x <= 0)
    {
        player->setPosition(0, player_initial_pos.y);
    }
}
void Game::render()
{
    window->clear();
    render_player();
    render_objects();
    render_ball();
    render_text();
    window->display();
}
void Game::render_text()
{
    window->draw(score);
    window->draw(points);
}
void Game::render_ball()
{
    window->draw(*ball);
}
void Game::render_player()
{
    window->draw(*player);
}
void Game::render_objects()
{
    for (auto &x : *objects)
    {
        window->draw(x);
    }
}
void Game::render_end()
{
    window->draw(end);
    window->display();
}
void Game::run()
{
    while (game_running)
    {
        update();
        render();
    }
    if (!game_running)
    {
        while (true)
        {
            update_events();
            render_end();
        }
    }
}
sf::Vector2f Game::get_player_pos()
{
    return player->getPosition();
}
Game::Game()
{
    init_vars();
    init_window();
    init_text();
    init_player();
    init_ball();
    init_sounds();
    init_objects();
}

Game::~Game()
{
    delete window;
    delete player;
    delete objects;
    delete ball;
}
sf::Text Game::create_text(sf::Vector2f Position, std::string String, sf::Color Color, int size)
{
    sf::Text temp;
    temp.setFont(font);
    temp.setPosition(Position);
    temp.setString(String);
    temp.setFillColor(Color);
    temp.setCharacterSize(size);
    return temp;
}