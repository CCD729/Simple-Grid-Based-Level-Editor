#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
//Namespaces
using namespace sf;

//Global Variables
Texture tileTexture;
Sprite tileSprite;
bool saveRelease = true;

//Prototypes (we should have a load asset function)
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

int main()
{
    RenderWindow window(VideoMode(840, 700), "Level Editor");
    //Sprite
    if (!tileTexture.loadFromFile("Tileset\\Platformer\\70x70\\Platformer-0.png")) {
        return -1;
    }

    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(0, 0);

    //window event and ordered functions
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event);
        }
        update(window);
        render(window);
    }
    return 0;
}

// Input handling
void handleInput(RenderWindow& window, Event& e) {
    if (e.type == Event::Closed)
        window.close();
    if (Mouse::isButtonPressed(Mouse::Left)) {
    }
    if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == sf::Keyboard::S)
        {
            saveRelease = true;
        }
    }
    // Ctrl+S saves a screenshot
    if (saveRelease && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        saveRelease = false;
        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        if (texture.copyToImage().saveToFile("Mylevel.png")) {
            std::cout << "Screenshot saved to Mylevel.png" << std::endl;
        }
    }
}
void update(RenderWindow& window) {

}
void render(RenderWindow& window) {
    window.clear();
    window.draw(tileSprite);
    window.display();
}