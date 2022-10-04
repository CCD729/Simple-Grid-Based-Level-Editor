#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

//Namespaces
using namespace sf;

//Global Variables
Texture tileTexture;
Sprite tileSprite;

//Prototypes (we should have a load asset function)
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    //Sprite
    if (!tileTexture.loadFromFile("Tileset\\Platformer\\70x70\\Platformer-0.png")) {
        return -1;
    }

    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(365, 530);

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

void handleInput(RenderWindow& window, Event& e) {
    if (e.type == Event::Closed)
        window.close();
    if (Mouse::isButtonPressed(Mouse::Left)) {
        //Input for
    }
}
void update(RenderWindow& window) {

}
void render(RenderWindow& window) {
    window.clear();
    window.draw(tileSprite);
    window.display();
}