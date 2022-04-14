
namespace NES
{
class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    //Load resources
    void loadResources();
    void freeResources();

    //Load a level
    void loadLevel(int level);
    void freeLevel();

    //Stream audio data from file.
    //The audio data is stored in the audio buffer.
    //The audio buffer is then played by the sound output device.
    void loadAudio(std::string filename);
    void freeAudio();

    //Load a spritesheet.
    //The spritesheet is stored in the spritesheet buffer.
    //The spritesheet buffer is then played by the graphics device.
    void loadSpritesheet(std::string filename);

    //Load physics data from file.
    void loadPhysics(std::string filename);

    //Load a font.
    void loadFont(std::string filename);


    
};
};


