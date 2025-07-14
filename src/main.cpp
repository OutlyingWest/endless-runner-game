#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "event_loop.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple SFML Game");
    window.setFramerateLimit(60);

    Player player;
    EventLoop loop;

    loop.addListener(&player);

    while (window.isOpen()) {
        loop.processEvents(window);

        player.move();

        window.clear();
        window.draw(player.shape);
        window.display();
    }

    return 0;
}