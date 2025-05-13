#include "AnimatedSprite.h"

int main()
{
    sf::VideoMode vm(800, 800);
    sf::RenderWindow window(vm, "AnimatedSprite test");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::AnimatedSprite animSprite("assets/animated_sprite_test");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        animSprite.update();

        window.clear();
        window.draw(animSprite);
        window.display();
    }
}
