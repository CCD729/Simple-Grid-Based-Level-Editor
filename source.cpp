#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
// Namespaces
using namespace sf;


Texture tileTexture;
Sprite tileSprite;

bool saveRelease = true;

// Prototypes
void loadAsset();
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

int main()
{
    // Create the window
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(840, 700), "My Level Editor", Style::Default, settings);
    window.setFramerateLimit(60);

    // First load assets
    loadAsset();

    // Setup the sprite
    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(0,0);

    // Window event and ordered functions
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

void loadAsset() {
    //Sprite
    if (!tileTexture.loadFromFile("Tileset\\Platformer-0.png")) {
        std::cerr << "Error: Failed to load texture file";
        exit(-1);
    }
}

// Input handling
void handleInput(RenderWindow& window, Event& e) {
    // Window close Handler
    if (e.type == Event::Closed)
        window.close();

    // Mouse Click 
    if (Mouse::isButtonPressed(Mouse::Left)) {
    }

    // Avoid multiple triggers while holding
    if (e.type == Event::KeyReleased) {
        if (e.key.code == Keyboard::F2)
        {
            saveRelease = true;
        }
    }
    // Display current tile location following mouse
    else if (e.type == Event::MouseMoved) {
        tileSprite.setPosition(Mouse::getPosition(window).x / 70 * 70, Mouse::getPosition(window).y / 70 * 70);
    }

    // F2 key saves a screenshot. TODO: Maybe hide current cursor-following tile?
    if (saveRelease && Keyboard::isKeyPressed(Keyboard::F2)) {
        saveRelease = false;
        Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        if (texture.copyToImage().saveToFile("Mylevel.png")) {
            std::cout << "Screenshot saved to Mylevel.png" << std::endl;
        }
    }
}
// What happens in the game frame
void update(RenderWindow& window) {

}
// What to render on screen
void render(RenderWindow& window) {
    window.clear();
    window.draw(tileSprite);
    window.display();
}