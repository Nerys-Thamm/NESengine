#ifndef BB13E06F_8516_4E0A_9C06_68F34193DB1F
#define BB13E06F_8516_4E0A_9C06_68F34193DB1F
#include <bitset>
#include <vector>
#include "types.h"
namespace NES
{
    //PPU
    //Description:
    //  The PPU is the part of the NES that handles the graphics.
    //  It is responsible for rendering the screen, and for
    //  handling the rendering of sprites.
    //  This class replicates its functionality, to provide graphics that are authentic.
    class PPU
    {
    public:
        PPU();
        void Reset();
        void Step();
        struct RGB { //RGB struct using a low bit depth to save memory
            unsigned int r : 3;
            unsigned int g : 3;
            unsigned int b : 3;
        };
        static constexpr RGB SYS_PALATTE[64] = { //NES System Color Palette
                            {3,3,3},{0,1,4},{0,0,6},{3,2,6},{4,0,3},{5,0,3},{5,1,0},{4,2,0},{3,2,0},{1,2,0},{0,3,1},{0,4,0},{0,2,2},{0,0,0},{0,0,0},{0,0,0},
                            {5,5,5},{0,3,6},{0,2,7},{4,0,7},{5,0,7},{7,0,4},{7,0,0},{6,3,0},{4,3,0},{1,4,0},{0,4,0},{0,5,3},{0,4,4},{0,0,0},{0,0,0},{0,0,0},
                            {7,7,7},{3,5,7},{4,4,7},{6,3,7},{7,0,7},{7,3,7},{7,4,0},{7,5,0},{6,6,0},{3,6,0},{0,7,0},{2,7,6},{0,7,7},{0,0,0},{0,0,0},{0,0,0},
                            {7,7,7},{5,6,7},{6,5,7},{7,5,7},{7,4,7},{7,5,5},{7,6,4},{7,7,2},{7,7,3},{5,7,2},{4,7,3},{2,7,6},{4,6,7},{0,0,0},{0,0,0},{0,0,0}
                                };
        struct CHR { //CHR is a format used to represent the pattern of a tile without color data in the NES
            std::bitset<0x80> data; //A CHR consists of two sequential blocks of memory, each coding for the same 8x8 tile with a bit depth of 1.
            static CHR FromArr(int data[8][8]) //Converts from 2d array to CHR format, for ease of development
            {
                CHR output;
                for (size_t i = 0; i < 8; i++)
                {
                    for (size_t j = 0; j < 8; j++)
                    {
                        //The two blocks of memory are used in tandem to represent a total bit depth of 2, allowing for values 0, 1, 2, and 3 to be represented
                        //Which allows a CHR to map each pixel to a colour in the currently loaded palette (NES Palettes could hold 4 colours at a time, including the background colour)
                        output.data[i * 8 + j]=(bool)(data[i][j] & 0b1); //The first block of memory holds the bit in the first position
                        output.data[(i+8) * 8 + j]=(bool)(data[i][j] & 0b01); //The second block of memory holds the bit in the second position
                        //So for example a the value 3 would encode 1 to the first block and 1 to the second block, to represent 0b11.
                    }
                }
                return output;
            }
            uint8_t GetVal(int x, int y) //Retrieves the Palette index value for the pixel at (x,y)
            {
                return data[x * 8 + y] | data[(x+8) * 8 + y];
            }
            void SetVal(int x, int y, uint8_t val) //Sets the Palette index value for the pixel at (x,y)
            {
                data[x * 8 + y] = val & 0b1;
                data[(x+8) * 8 + y] = val & 0b01;
            }
        };
        struct Sprite { //Sprite Data Structure
            //NES Sprite data was stored in an area of memory called Spr-RAM, and contained a reference to the area of the pattern table the CHR data for that sprite was stored, as well as some additional data.
            byte yCoord; //The y coordinate of the sprite
            byte patternIndex; //The index of the CHR data for the sprite within the pattern table
            byte attributes; //Additional data about the sprite
            enum class Attribute {
                flipY = 0b10000000, //This bit controls if the sprite is flipped vertically, this was used to help cheaply reuse sprite data
                flipX = 0b01000000, //This bit controls if the spriteis flipped horizontally, this was used to help cheaply reuse sprite data
                priority = 0b00100000, //This bit controls whether the sprite has priority over the background.
                color = 0b00000011, //These two bits store the index of the colour palette the CHR data of this sprite is meant to use
            };
        };
        struct Palette //Color palette data structure
        {
            //The NES had extremely limited VRAM, so as much reuse of colour data was needed as possible
            //To achieve this, instead of storing the colour data in the data for the art assets, it was stored as palettes
            //That could then be applied to multiple different tiles and sprites.
            //The NES was capable of using 4 palettes at a time, with each palette containing the background colour, and 3 other colours
            private:
            uint8_t colIndexes[0x10]; // Array of 16 colours, as indexed within the system palette.
            public:
            RGB operator[](const int index) const //Operator to streamline access to the colour data by grabbing colours directly from the system palette when needed for rendering
            {
                return SYS_PALATTE[index % 3 == 0 ? 0 : colIndexes[index]]; //First entry is background color, every fourth byte mirrors the first entry
            }
        };
        
        void SetSpritePalette(const Palette& palette); //Sets a palette to be used for drawing Sprites
        void SetImagePalette(const Palette& palette); //Sets a palette to be used for drawing Images
        void SetPatternTable(const CHR& table, const int index); //Places the provided data into the pattern table of the given index
        void SetNameTable(const uint8_t& table, const int index); //Places the provided data into the name table of the given index
        void SetAttrTable(const uint8_t& table, const int index); //Places the provided data into the attribute table of the given index
        void BlitImage(int patternTable, int nameTable, int attrTable); //Draws the image stored in the pattern table, name table, and attribute table to the screen
        void BlitImage(int patternTable, int attrTable, int firstNameTable, int secondNameTable, int scrollAmount, bool isVertical); //Draws the image stored in the pattern table, name table, and attribute table to the screen, but scrolls between two name tables by the given amount
    private:
        Palette spritePalette, imagePalette; //The palettes to be used for drawing Sprites and Images
        //Pattern tables hold CHR data for Tiles and Sprites
        CHR patternTable1[0x100], patternTable2[0x100]; //The pattern tables to be used for drawing Images
        //Name tables specify which tile is to be drawn for each position on the screen
        uint8_t nameTable1[0x3C0], nameTable2[0x3C0], nameTable3[0x3C0], nameTable4[0x3C0]; //The name tables to be used for drawing Images
        //Attribute tables specify which color palette is to be used for each block (area of 4x4 tiles) on the screen
        uint8_t attrTable1[0xF0], attrTable2[0xF0], attrTable3[0xF0], attrTable4[0xF0]; //The attribute tables to be used for drawing Images
        Sprite sprRAM[0x40]; //The sprite RAM to be used to hold sprite data
        uint8_t xScroll, yScroll; //The amount to scroll the image by
    };

    //Animator class, used to animate sprites
    class Animator {
    public:
        struct Animation { //Animation data structure
            PPU::Sprite* spritesheet;
            int frameCount;
            int frameDelay;
            int frameIndex;
        };
        void AddAnimation(const Animation& anim); //Adds an animation to the animator
        void Update(); //Updates the animator
    private:
        std::vector<Animation> animations; //The animations to be played
        void UpdatePPU(); //Updates the sprite stored in the PPU with the current sprite in the animation
    };







}
#endif /* BB13E06F_8516_4E0A_9C06_68F34193DB1F */
