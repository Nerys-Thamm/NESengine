#ifndef CE089E89_4247_4545_86EE_8663E20BE181
#define CE089E89_4247_4545_86EE_8663E20BE181
#include "types.h"
namespace NES
{
    //Input class
    class Input
    {
        public:
        enum BTN { // buttons:
            A = 0b00000001,  // A         [A]
            B = 0b00000010,  // B         [B]
            SL = 0b00000100, // Select    (Select)
            ST = 0b00001000, // Start     (Start)
            UP = 0b00010000, // Up        [^]
            DN = 0b00100000, // Down      [v]
            LT = 0b01000000, // Left      [<]
            RT = 0b10000000  // Right     [>]
        };

        // Get the current state of the buttons for the joypad of the provided index.
        static byte GetJoypadState(int joypadIndex);

        // Get the state of a specific button from joypad state data
        static bool GetBtnState(byte data, BTN btn) { return (data & (int)btn); }
    };
}

#endif /* CE089E89_4247_4545_86EE_8663E20BE181 */
