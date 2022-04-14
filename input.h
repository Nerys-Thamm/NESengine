#ifndef CE089E89_4247_4545_86EE_8663E20BE181
#define CE089E89_4247_4545_86EE_8663E20BE181
#include "types.h"
namespace NES
{
    class Input
    {
        public:
        enum BTN {
            A = 0b00000001,
            B = 0b00000010,
            SL = 0b00000100,
            ST = 0b00001000,
            UP = 0b00010000,
            DN = 0b00100000,
            LT = 0b01000000,
            RT = 0b10000000
        };
        static byte GetJoypadState(int joypadIndex);
        static bool GetBtnState(byte data, BTN btn) { return (data & (int)btn); }
    };
}

#endif /* CE089E89_4247_4545_86EE_8663E20BE181 */
