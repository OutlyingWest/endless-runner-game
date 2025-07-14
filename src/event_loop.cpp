#include "event_loop.h"


void EventLoop::addListener(EventListener* listener) {
    listeners.push_back(listener);
}

void EventLoop::processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        for (auto* listener : listeners) {
            listener->onEvent(event);
        }
    }
}