#pragma once
#include <SFML/Graphics.hpp>

class EventListener {
public:
    virtual void onEvent(const sf::Event& event) = 0;
    // Virtual destructor ensures proper cleanup of derived classes when deleting via base pointer.
    virtual ~EventListener() = default;
};

class EventLoop {
private:
    std::vector<EventListener*> listeners;

public:
    void addListener(EventListener* listener);
    void processEvents(sf::RenderWindow& window);
};



