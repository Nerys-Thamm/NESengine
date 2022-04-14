#include "graphics.h"
namespace NES
{
class Level {
public:
    Level();
    ~Level();

    struct LevelData {
        int width;
        int height;
        //Graphical Data for the level
        //Name tables specify which tile is to be drawn for each position on the screen
        uint8_t nameTable1[0x3C0], nameTable2[0x3C0], nameTable3[0x3C0], nameTable4[0x3C0]; //The name tables to be used for drawing Images
        //Attribute tables specify which color palette is to be used for each block (area of 4x4 tiles) on the screen
        uint8_t attrTable1[0xF0], attrTable2[0xF0], attrTable3[0xF0], attrTable4[0xF0]; //The attribute tables to be used for drawing Images

    };


};
};