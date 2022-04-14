#ifndef BB13E06F_8516_4E0A_9C06_68F34193DB1F
#define BB13E06F_8516_4E0A_9C06_68F34193DB1F
#include <bitset>
#include "types.h"
namespace NES
{
    //PPU
    //Description:
    //  The PPU is the part of the NES that handles the graphics.
    //  It is responsible for rendering the screen, and for
    //  handling the rendering of sprites.
    //
    class PPU
    {
    public:
        PPU();
        void Reset();
        void Step();
        struct RGB {
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
        struct CHR {
            std::bitset<0x80> data;
            static CHR FromArr(int data[8][8])
            {
                CHR output;
                for (size_t i = 0; i < 8; i++)
                {
                    for (size_t j = 0; j < 8; j++)
                    {
                        output.data[i * 8 + j]=(bool)(data[i][j] & 0b1);
                        output.data[(i+8) * 8 + j]=(bool)(data[i][j] & 0b01);
                    }
                }
                return output;
            }
            uint8_t GetVal(int x, int y)
            {
                return data[x * 8 + y] | data[(x+8) * 8 + y];
            }
            void SetVal(int x, int y, uint8_t val)
            {
                data[x * 8 + y] = val & 0b1;
                data[(x+8) * 8 + y] = val & 0b01;
            }
        };
        struct Sprite {
            byte yCoord;
            byte patternIndex;
            byte attributes;
            enum class Attribute {
                flipY = 0b10000000,
                flipX = 0b01000000,
                priority = 0b00100000,
                color = 0b00000011,
            };
        };
        struct Palette
        {
            private:
            uint8_t colIndexes[0x10];
            public:
            RGB operator[](const int index) const
            {
                return SYS_PALATTE[index % 3 == 0 ? 0 : colIndexes[index]]; //First entry is background color, every fourth byte mirrors the first entry
            }
        };
        void SetSpritePalette(const Palette& palette);
        void SetImagePalette(const Palette& palette);
        void SetPatternTable(const CHR& table, const int index);
        void SetNameTable(const uint8_t& table, const int index);
        void SetAttrTable(const uint8_t& table, const int index);
        void BlitImage(int patternTable, int nameTable, int attrTable);
        void BlitImage(int patternTable, int attrTable, int firstNameTable, int secondNameTable, int scrollAmount, bool isVertical);
    private:
        Palette spritePalette, imagePalette;
        CHR patternTable1[0x100], patternTable2[0x100];
        uint8_t nameTable1[0x3C0], nameTable2[0x3C0], nameTable3[0x3C0], nameTable4[0x3C0];
        uint8_t attrTable1[0xF0], attrTable2[0xF0], attrTable3[0xF0], attrTable4[0xF0];
        Sprite sprRAM[0x40];
        uint8_t xScroll, yScroll;
    };

}
#endif /* BB13E06F_8516_4E0A_9C06_68F34193DB1F */
