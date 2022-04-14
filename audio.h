#ifndef E746EAB8_5409_42F4_9F66_40DA75BCC5FB
#define E746EAB8_5409_42F4_9F66_40DA75BCC5FB
#include "types.h"
namespace NES
{
    class APU
    {
        static void WriteToPCMRegister(byte data);
        static void WriteToDPCMRegister(byte data);
    };
}

#endif /* E746EAB8_5409_42F4_9F66_40DA75BCC5FB */
