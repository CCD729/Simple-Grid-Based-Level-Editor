#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>
#include <map>

// Namespaces
using namespace sf;
using namespace std;


//Global variables
Image tileset;
Texture tileTexture;
Sprite displaySprite;
map<int, Sprite>renderSprites;
int currentLevel[10][12];
int currentTile = 0;
Vector2i currentPos = {0,0};
int tileHeight = 70;
int tileWidth = 70;
int tilesetRow, tilesetColumn = 0;
bool saveShotRelease = true;
bool levelSaveRelease = true;
bool levelLoadRelease = true;
bool addDone = true;
bool removeDone = true;

// Prototypes
void setup();
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

    // Setup and load assets
    setup();

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

void setup() {

    // Initialize Level
    for (unsigned int i = 0; i < 10; i++) {
        for (unsigned int j = 0; j < 12; j++) {
            currentLevel[i][j] = -1;
        }
    }

    // Load the tileset (Legacy)
   /* if (!tileset.loadFromFile("Tileset\\Platformer-Tileset-70x70.png")) {
        std::cerr << "Error: Failed to load tileset";
        exit(-1);
    }*/

    // Load a texture tile set
    if (!tileTexture.loadFromFile("Tileset\\Platformer-Tileset-70x70.png")) {
        std::cerr << "Error: Failed to load tile set";
        exit(-1);
    }

    // Determine dimension of texture
    if (tileTexture.getSize().x % tileWidth != 0 || tileTexture.getSize().y % tileHeight != 0) {
        std::cerr << "Error: Tileset size not divisible by tile Size";
        exit(-1);
    }
    else {
        tilesetColumn = tileTexture.getSize().x / tileWidth;
        tilesetRow = tileTexture.getSize().y / tileHeight;
    }

    //Sprite (Legacy)
    /*if (!tileTexture.loadFromFile("Tileset\\Platformer-0.png")) {
        std::cerr << "Error: Failed to load texture file";
        exit(-1);
    }*/

    // Setup the sprite for display
    displaySprite.setTexture(tileTexture);
    displaySprite.setTextureRect(IntRect(currentTile / tilesetColumn * tileWidth, currentTile * tileHeight, tileWidth, tileHeight));
    displaySprite.setPosition(0, 0);
}

// Input handling
void handleInput(RenderWindow& window, Event& e) {
    // Window close Handler
    if (e.type == Event::Closed)
        window.close();

    // Left Mouse Click puts a sprite into the map
    if (addDone && Mouse::isButtonPressed(Mouse::Left)) {
        addDone = false;
        currentPos.x = Mouse::getPosition(window).x / tileWidth;
        currentPos.y = Mouse::getPosition(window).y / tileHeight;
        if (0 <= (currentPos.x * 10 + currentPos.y) && (currentPos.x * 10 + currentPos.y) <= 119) {
            if (currentLevel[Mouse::getPosition(window).y / tileHeight][Mouse::getPosition(window).x / tileWidth] != currentTile) {
                currentLevel[Mouse::getPosition(window).y / tileHeight][Mouse::getPosition(window).x / tileWidth] = currentTile;
                Sprite savedSprite = *new Sprite(tileTexture, IntRect(currentTile / tilesetRow * tileWidth, currentTile % tilesetRow * tileHeight, tileWidth, tileHeight));
                savedSprite.setPosition(Mouse::getPosition(window).x / tileWidth * tileWidth, Mouse::getPosition(window).y / tileHeight * tileHeight);
                // Store location data to do garbage collection while replacing vectors
                if (renderSprites.count(currentPos.x * 10 + currentPos.y)) {
                    renderSprites.erase(currentPos.x * 10 + currentPos.y);
                }
                renderSprites.insert({ currentPos.x * 10 + currentPos.y, savedSprite });
            }
        }
        addDone = true;
    }
    // Right Mouse Click erases a sprite
    else if (removeDone && Mouse::isButtonPressed(Mouse::Right)) {
        removeDone = false;
        currentPos.x = Mouse::getPosition(window).x / tileWidth;
        currentPos.y = Mouse::getPosition(window).y / tileHeight;
        if (0 <= (currentPos.x * 10 + currentPos.y) && (currentPos.x * 10 + currentPos.y) <= 119) {
            if (currentLevel[Mouse::getPosition(window).y / tileHeight][Mouse::getPosition(window).x / tileWidth] != -1) {
                currentLevel[Mouse::getPosition(window).y / tileHeight][Mouse::getPosition(window).x / tileWidth] = -1;
                if (renderSprites.count(currentPos.x * 10 + currentPos.y)) {
                    renderSprites.erase(currentPos.x * 10 + currentPos.y);
                }
            }
        }
        removeDone = true;
    }
    // F2 key saves a screenshot.
    else if (saveShotRelease && Keyboard::isKeyPressed(Keyboard::F2)) {
        saveShotRelease = false;
        Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        Uint8 tempAlpha = displaySprite.getColor().a;
        displaySprite.setColor(Color(displaySprite.getColor().r, displaySprite.getColor().g, displaySprite.getColor().b, Uint8(0)));
        texture.update(window);
        displaySprite.setColor(Color(displaySprite.getColor().r, displaySprite.getColor().g, displaySprite.getColor().b, tempAlpha));
        if (texture.copyToImage().saveToFile("Mylevel.png")) {
            std::cout << "Screenshot saved to Mylevel.png" << std::endl;
        }
    }

    // S key saves level to a txt file
    else if (levelSaveRelease && Keyboard::isKeyPressed(Keyboard::S)) {

    }
    
    // L key loads level from a txt file
    else if (levelSaveRelease && Keyboard::isKeyPressed(Keyboard::L)) {

    }

    // Left or Right arrow key changes tile
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (currentTile > 0)
            currentTile--;
        else
            currentTile = tilesetColumn * tilesetRow - 1;
        displaySprite.setTextureRect(IntRect(currentTile / tilesetRow * tileWidth, currentTile % tilesetRow * tileHeight, tileWidth, tileHeight));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (currentTile < tilesetColumn * tilesetRow - 1)
            currentTile++;
        else
            currentTile = 0;
        displaySprite.setTextureRect(IntRect(currentTile / tilesetRow * tileWidth, currentTile % tilesetRow * tileHeight, tileWidth, tileHeight));
        //cout << currentTile / tilesetRow * tileWidth << " " << currentTile % tilesetRow * tileHeight << endl;
    }

    // Avoid multiple triggers while holding
    if (e.type == Event::KeyReleased) {
        if (e.key.code == Keyboard::F2)
        {
            saveShotRelease = true;
        }
        else if (e.key.code == Keyboard::S)
        {
            levelSaveRelease = true;
        }
        else if (e.key.code == Keyboard::L)
        {
            levelLoadRelease = true;
        }
    }
    // Display current tile location following mouse
    if (e.type == Event::MouseMoved) {
        displaySprite.setPosition(Mouse::getPosition(window).x / tileWidth * tileWidth, Mouse::getPosition(window).y / tileHeight * tileHeight);
    }
}
// What happens in the game frame
void update(RenderWindow& window) {

}
// What to render on screen
void render(RenderWindow& window) {
    window.clear();
    for (auto const& s : renderSprites){
        window.draw(s.second);
    }
    window.draw(displaySprite);
    window.display();
}