#include "Pokitto.h"
#include "Tilemap.hpp"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


namespace Data {

    #include "Green.h"
    #include "Grass.h"
    #include "Tree.h"
    #include "Water.h"
    #include "Player.h"
    #include "Enemy.h"
    
    Tilemap::Tile green16 = { &Green[2], Green[0], Green[1] };
    Tilemap::Tile tree16 = { &Tree[2], Tree[0], Tree[1] };
    Tilemap::Tile grass16 = { &Grass[2], Grass[0], Grass[1] };
    Tilemap::Tile water16 = { &Water[2], Water[0], Water[1] };

}