#ifndef E59C2D33_8846_4DA8_90A6_4FF698D10F2E
#define E59C2D33_8846_4DA8_90A6_4FF698D10F2E

#include "resources.h"
#include "graphics.h"
#include "input.h"
#include "physics.h"
#include "audio.h"
#include "level.h"

namespace NES
{
//Core System Class
//This class is the core of the system.
class System
{
private:
    /* data */
public:
    System(/* args */);
    ~System();

    //Initialize the system
    void init();

    //Update the system
    void update();

    //Shutdown the system
    void shutdown();

    //Get the instance of the system
    static System& getInstance();

    //Get the instance of the resource manager
    ResourceManager& getResourceManager();

    




};
};



#endif /* E59C2D33_8846_4DA8_90A6_4FF698D10F2E */
