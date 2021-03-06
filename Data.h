// Graphics by Lanea Zimmerman
// https://opengameart.org/content/tiny-86-basic
// Licensed under CC-BY 3.0, https://creativecommons.org/licenses/by/3.0/

#include "Pokitto.h"
#include "Tilemap.hpp"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


namespace Data {
    
    const uint8_t worldMap[] = {
        0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x10, 0x00,
        0x48, 0x88, 0x88, 0x88, 0x88, 0x84, 0x11, 0x00,
        0x48, 0x44, 0x48, 0x84, 0x44, 0x84, 0x21, 0x00,
        0x48, 0x48, 0x88, 0x88, 0x84, 0x84, 0x21, 0x00,
        
        0x48, 0x48, 0x88, 0x88, 0x84, 0x84, 0x11, 0x00,
        0x48, 0x88, 0x44, 0x44, 0x88, 0x84, 0x21, 0x00,
        0x48, 0x88, 0x48, 0x74, 0x88, 0x84, 0x11, 0x00,
        0x48, 0x48, 0x88, 0x88, 0x84, 0x85, 0x11, 0x11,
    
        0x48, 0x48, 0x88, 0x88, 0x84, 0x84, 0x11, 0x00,
        0x48, 0x88, 0x48, 0x84, 0x88, 0x84, 0x21, 0x00,
        0x48, 0x88, 0x44, 0x44, 0x88, 0x84, 0x11, 0x00,
        0x48, 0x48, 0x88, 0x88, 0x84, 0x84, 0x11, 0x00,
    
        0x48, 0x48, 0x88, 0x88, 0x84, 0x84, 0x21, 0x00,
        0x48, 0x44, 0x48, 0x84, 0x44, 0x84, 0x21, 0x00,
        0x48, 0x88, 0x88, 0x88, 0x88, 0x84, 0x11, 0x00,
        0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x10, 0x00,
    };
    

};