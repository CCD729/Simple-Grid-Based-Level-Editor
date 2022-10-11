#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>
#include<sstream>
#include <map>


// Namespaces
using namespace sf;
using namespace std;


//Global variables
Image tileset;
Texture tileTexture;
Sprite displaySprite;
map<int, Sprite*>renderSprites;
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
int LineToIntArrayParser(string s, int i, int buffer[10][12], bool goodParse);

int main()
{
    // Setup and load assets
    setup();

    // Create the window
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(tileWidth * 12, tileHeight*10), "My Level Editor", Style::Default, settings);
    window.setFramerateLimit(60);

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

    // Get file input and load texture tile set
    cout << "Setup: Please enter the path/file name of the tileset file(Example. \"Tileset/Platformer-Tileset-70x70.png\"):" << endl;
    string filePath;
    getline(cin, filePath);
    cout << "Please provide tile width in positive integer of pixels:" << endl;
    cin >> tileWidth;
    cout << "Please provide tile height in positive integer of pixels:" << endl;
    cin >> tileHeight;
    if (tileWidth < 1 || tileHeight <1) {
        cerr << "Error: Invalid input";
        exit(-1);
    }

    // Load a texture tile set
    if (!tileTexture.loadFromFile(filePath)) {
        cerr << "Error: Failed to load tile set file";
        exit(-1);
    }

    // Determine dimension of texture
    if (tileTexture.getSize().x % tileWidth != 0 || tileTexture.getSize().y % tileHeight != 0) {
        cerr << "Error: Tileset size not divisible by tile Size";
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
                Sprite* savedSprite = new Sprite(tileTexture, IntRect(currentTile / tilesetRow * tileWidth, currentTile % tilesetRow * tileHeight, tileWidth, tileHeight));
                (*savedSprite).setPosition(float(Mouse::getPosition(window).x / tileWidth * tileWidth), float(Mouse::getPosition(window).y / tileHeight * tileHeight));
                // Store location data to do garbage collection while replacing vectors
                if (renderSprites.count(currentPos.x * 10 + currentPos.y)) {
                    delete renderSprites[currentPos.x * 10 + currentPos.y];
                    renderSprites.erase(currentPos.x * 10 + currentPos.y);
                }
                renderSprites.insert({ currentPos.x * 10 + currentPos.y, savedSprite });
                currentLevel[Mouse::getPosition(window).y / tileHeight][Mouse::getPosition(window).x / tileWidth] = currentTile;
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
                if (renderSprites.count(currentPos.x * 10 + currentPos.y)) {
                    delete renderSprites[currentPos.x * 10 + currentPos.y];
                    renderSprites.erase(currentPos.x * 10 + currentPos.y);
                }
                currentLevel[Mouse::getPosition(window).y / tileHeight][Mouse::getPosition(window).x / tileWidth] = -1;
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
            cout << "Screenshot saved to Mylevel.png" << endl;
        }
    }

    // S key saves level to a txt file
    else if (levelSaveRelease && Keyboard::isKeyPressed(Keyboard::S)) {
        levelSaveRelease = false;
        cout << "Save: Please enter the path/file name of the level txt file. (Example. \"Saves/level.txt\" or \"myLevel.txt\".) Note that if trying to access a directory that does not exist, no files would be saved:" << endl;
        string filePath;
        getline(cin, filePath);
        ofstream levelOut;
        levelOut.open(filePath, ofstream::out | ofstream::trunc);
        for (unsigned int i = 0; i < 10; i++) {
            for (unsigned int j = 0; j < 12; j++) {
                levelOut << currentLevel[i][j];
                if (j < 11)
                    levelOut << " ";
            }
            if(i<9)
                levelOut << endl;
        }
        levelOut.close();
        cout << "Saving level to " << filePath << " if the directory of the file exists." << endl;
    }
    
    // L key loads level from a txt file
    else if (levelLoadRelease && Keyboard::isKeyPressed(Keyboard::L)) {
        levelLoadRelease = false;
        cout << "Load: Please enter the path/file name of the level txt file:" << endl;
        string filePath;
        getline(cin, filePath);
        ifstream levelIn(filePath);
        if (!levelIn) {
            cerr << "Error: Failed to load level.txt"<<endl;
        }
        else {
            unsigned int i = 0;
            auto buffer = new int[10][12]();
            bool successParse = true;
            for (string line; getline(levelIn, line); i++) {
                if (LineToIntArrayParser(line, i, buffer, successParse) == -1) {
                    delete[] buffer;
                    break;
                }
            }
            // No error parsing file
            if (successParse) {
                // Initialize Level
                for (unsigned int i = 0; i < 10; i++) {
                    for (unsigned int j = 0; j < 12; j++) {
                        currentLevel[i][j] = buffer[i][j];
                        // Replace & add level tiles
                        if (currentLevel[i][j] != -1) {
                            Sprite* savedSprite = new Sprite(tileTexture, IntRect(currentLevel[i][j] / tilesetRow * tileWidth, currentLevel[i][j] % tilesetRow * tileHeight, tileWidth, tileHeight));
                            (*savedSprite).setPosition(float(j * tileWidth), float(i * tileHeight));
                            // Store location data to do garbage collection while replacing vectors
                            if (renderSprites.count(j * 10 + i)) {
                                delete renderSprites[j * 10 + i];
                                renderSprites.erase(j * 10 + i);
                            }
                            renderSprites.insert({ j * 10 + i, savedSprite });
                        }
                        else {
                            if (renderSprites.count(j * 10 + i)) {
                                delete renderSprites[j * 10 + i];
                                renderSprites.erase(j * 10 + i);
                            }
                        }
                    }
                }
                cout << "Loading level from " << filePath << endl;
            }
        }
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
        displaySprite.setPosition(float(Mouse::getPosition(window).x / tileWidth * tileWidth), float(Mouse::getPosition(window).y / tileHeight * tileHeight));
    }
}
// What happens in the game frame
void update(RenderWindow& window) {

}
// What to render on screen
void render(RenderWindow& window) {
    window.clear();
    for (auto const& s : renderSprites){
        window.draw(*s.second);
    }
    window.draw(displaySprite);
    window.display();
}

// Level file Input parser
int LineToIntArrayParser(string s, int row, int buffer[10][12], bool goodParse) {
    stringstream ss(s);
    try {
        for (unsigned int j = 0; j < 12; j++) {
            ss >> buffer[row][j];
        }
    }
    catch(...) {
        cerr<<"Error: level.txt content format wrong! Loading failed."<< endl;
        goodParse = false;
        return -1;
    }
    return 0;
}

