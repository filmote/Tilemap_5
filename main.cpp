// Copyright (C) 2019 Hannu Viitala
// 
// The source code in this file is released under the MIT license.
// Go to http://opensource.org/licenses/MIT for the full license details.
// 
// Converted to C++ and extended by Filmote

// *** A TILEMAP DEMO FOR THE POKITTO ***

#include "Pokitto.h"
#include "Tilemap.hpp"
#include "Data.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

namespace Constants {
    
    const uint8_t tileWidth = 16;
    const uint8_t tileHeight = 16;
    
    const uint8_t mapTileWidth = 16;                            // Map width in tiles ..
    const uint8_t mapTileHeight = 16;                           // Map height in tiles ..
    
    const uint16_t mapWidth = mapTileWidth * tileWidth;         // 16 tiles of 16 pixels
    const uint16_t mapHeight = mapTileHeight * tileHeight;      // 16 tiles of 16 pixels
    
    const uint16_t screenCentreX = PD::width / 2; 
    const uint16_t screenCentreY = PD::height / 2;

    const uint16_t numberOfEnemies = 3;
    
}



// ---------------------------------------------------------------------------------------


enum TileType {
    
	Water = 0,
	Green = 1,
	Tree = 2,
	Grass = 3,
	
}; 


enum Direction {
    
	Up,
	Down,
	Left,
	Right
	
}; 


struct Entity {
    
    int16_t x;
    int16_t y;

    const uint8_t width = 12;
    const uint8_t height = 15;

};


struct Player : Entity {
    
    int16_t xOffset;
    int16_t yOffset;

    int16_t getPositionInWorldX() { return Constants::screenCentreX - x - xOffset; }
    int16_t getPositionInWorldY() { return Constants::screenCentreY - y - yOffset; }

};


struct Enemy : Entity {

};

// ---------------------------------------------------------------------------------------


Tilemap tilemap;
Player player;
Enemy enemies[Constants::numberOfEnemies];



// ---------------------------------------------------------------------------------------
//
//  Do the two entities overlap?
//
bool collide(Player player, Enemy enemy) {

    return !(enemy.x                >= player.getPositionInWorldX() + player.width  ||
             enemy.x + enemy.width  <= player.getPositionInWorldX()                 ||
             enemy.y                >= player.getPositionInWorldY() + player.height ||
             enemy.y + enemy.height <= player.getPositionInWorldY());

}
    



// ---------------------------------------------------------------------------------------
//
//  Check to see if the move the entity is about to make is into a green (empty) tile.  As 
//  the player and enemy tiles are 12 x 15 pixels and the tiles are bigger (16 x 16) its 
//  possible that the entity could be straddling two tiles in either direction ..
//
bool checkMovement(Entity &entity, int16_t x, int16_t y, Direction direction) {

    int8_t tileId1 = 0;
    int8_t tileId2 = 0;

    switch (direction) {
        
        case Direction::Left:
            tileId1 = tilemap.GetTileId(x, y, 16);
            tileId2 = tilemap.GetTileId(x, y + entity.height, 16);
            break;
        
        case Direction::Right:
            tileId1 = tilemap.GetTileId(x + entity.width, y, 16);
            tileId2 = tilemap.GetTileId(x + entity.width, y + entity.height, 16);
            break;

        case Direction::Up:
            tileId1 = tilemap.GetTileId(x, y, 16);
            tileId2 = tilemap.GetTileId(x + entity.width, y, 16);
            break;
        
        case Direction::Down:
            tileId1 = tilemap.GetTileId(x, y + player.height, 16);
            tileId2 = tilemap.GetTileId(x + entity.width, y + entity.height, 16);
            break;
            
    }
    


    // If either tile is not green, do not move.
    
    if (tileId1 != TileType::Green || tileId2 != TileType::Green) {
        return false;
        
    }

    return true;
        
}



// ---------------------------------------------------------------------------------------
//
//  Handle the player movements ..
//
void handlePlayerMovements() {

    int16_t positionInWorldX = player.getPositionInWorldX();
    int16_t positionInWorldY = player.getPositionInWorldY();

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1))    { 


        // Can we move to the left?
        
        if (checkMovement(player, positionInWorldX - 1, positionInWorldY, Direction::Left)) {

    
            // If we are already on the right hand side of the screen, come back to the centre ..

            if (player.xOffset < 0) {     
                
                player.xOffset++;
    
            }
            
            
            // Otherwise scroll the screen itself if we can ..
            
            else if (player.x < 0) {
                
                player.x++;

            }
            
            
            // If we cannot scroll the screen, move the player to the left ..
            
            else if (player.x <= (PD::width / 2)) {     
                
                player.xOffset++;

            }
            
        }

    }
    
    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1))   { 


        // Can we move to the right?
        
        if (checkMovement(player, positionInWorldX + 1, positionInWorldY, Direction::Right)) {
                
    
            // If we are already on the left hand side of the screen, come back to the centre ..
            
            if (player.xOffset > 0) {
                player.xOffset--;
            }
                 
            
            // Otherwise scroll the screen itself if we can ..
            
            else if (player.x > (PD::width - Constants::mapWidth) && player.x <= 0) {
                player.x--;
            }
            
            
            // If we cannot scroll the screen, move the player to the right ..
            
            else if (player.x >= (PD::width - Constants::mapWidth)) {
                player.xOffset--;
            }
            
        }

    }
    
    
    if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1))      { 


        // Can we move up?
        
        if (checkMovement(player, positionInWorldX, positionInWorldY - 1, Direction::Up)) {

            
            // If we are already in the bottom section of the screen, come back to the centre ..
            
            if (player.yOffset < 0) {                                  
                player.yOffset++;
            }
            
            
            // Otherwise scroll the screen itself if we can ..
            
            else if (player.y < 0) {
                player.y++;
            }
            
            
            // If we cannot scroll the screen, move the player up ..
            
            else if (player.y <= (PD::height / 2)) {     
                player.yOffset++;
            }
        
        }
        
    }
    
    if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1))    { 


        // Can we move down?
        
        if (checkMovement(player, positionInWorldX, positionInWorldY + 1, Direction::Down)) {

    
            // If we are already in the top section of the screen, come back to the centre ..
            
            if (player.yOffset > 0) {
                player.yOffset--;
            }
                 
            
            // Otherwise scroll the screen itself if we can ..
            
            else if (player.y > (PD::height - Constants::mapHeight) && player.y <= 0) {
                player.y--;
            }
            
            
            // If we cannot scroll the screen, move the player down ..
            
            else if (player.y >= (PD::height - Constants::mapHeight)) {
                player.yOffset--;
            }
            
        }

    }
    
}




// ---------------------------------------------------------------------------------------
//
//  Handle the enemy movements ..
//
void handleEnemyMovements() {


    // Where is the player currently ?
    
    int16_t playerPositionInWorldX = player.getPositionInWorldX();
    int16_t playerPositionInWorldY = player.getPositionInWorldY();
    
    
    // Move each enemy individually ..
    
    for (uint8_t i = 0; i < Constants::numberOfEnemies; i++) {

        if (playerPositionInWorldX < enemies[i].x) {

            if (checkMovement(enemies[i], enemies[i].x - 1, enemies[i].y, Direction::Left)) {
                enemies[i].x--;
            }
            
        }
        
        if (playerPositionInWorldX > enemies[i].x) {

            if (checkMovement(enemies[i], enemies[i].x + 1, enemies[i].y, Direction::Right)) {
                enemies[i].x++;
            }
            
        }

        if (playerPositionInWorldY < enemies[i].y) {

            if (checkMovement(enemies[i], enemies[i].x, enemies[i].y - 1, Direction::Up)) {
                enemies[i].y--;
            }
            
        }
        
        if (playerPositionInWorldY > enemies[i].y) {

            if (checkMovement(enemies[i], enemies[i].x, enemies[i].y + 1, Direction::Down)) {
                enemies[i].y++;
            }
            
        }
        
    }
    
}



// ---------------------------------------------------------------------------------------


int main(){

    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::invisiblecolor = 12;
    PD::loadRGBPalette(palettePico);   
    PD::setFont(fontC64);



    // Initialise the map ..
    
    tilemap.set(16, 16, Data::mapPixels);
    tilemap.tiles[TileType::Green] = Data::green16;
    tilemap.tiles[TileType::Tree] = Data::tree16;
    tilemap.tiles[TileType::Grass] = Data::grass16;
    tilemap.tiles[TileType::Water] = Data::water16;


    // Position the player into a vacant spot on the map ..
    
    player.x = -20;
    player.y = -50;
    
    
    
    // Position the enemies in a vacant spot ..

    enemies[0].x = 81;
    enemies[0].y = 49;

    enemies[1].x = 161;
    enemies[1].y = 49;

    enemies[2].x = 177;
    enemies[2].y = 100;

    
    while (PC::isRunning()) {
        
        if (!PC::update()) continue;

        PC::buttons.pollButtons();        



        // Handle player movements ..

        handlePlayerMovements();


        // Move enemies ..

        handleEnemyMovements();


        // Render screen ..

        tilemap.draw(player.x, player.y);
        
        
        // Render player and enemies ..
        
        PD::drawBitmap(Constants::screenCentreX - player.xOffset, Constants::screenCentreY - player.yOffset, Data::Player);

        for (uint8_t i = 0; i < Constants::numberOfEnemies; i++) {

            PD::drawBitmap(+enemies[i].x + player.x, +enemies[i].y + player.y, Data::Player);
            
        }


        // Check for collisions between the player and the enemy ..

        for (uint8_t i = 0; i < Constants::numberOfEnemies; i++) {

            if (collide(player, enemies[i])) {
                
                PD::setColor(2);
                PD::fillRect(78, 78, 80, 10);
                PD::setColor(0, 2);
                PD::setCursor(80, 80);
                PD::print("Game Over");

            }
            
        }
        

    }
    
    return 0;
    
}

