#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Entity.h"

enum GameStatus {PLAYING, WAITING, STARTMENU, PLAYER1, PLAYER2};


class Background: public Entity
{
public:
    Background(Vector2 position, Vector2 scale, const char *textureFilepath,
           Vector2 spriteSheetDimensions, GameStatus *gGameStatus,
            std::map<GameStatus, std::vector<int>> atlas) :  
           Entity(position, scale, textureFilepath,spriteSheetDimensions, {}), atlas(atlas), gGameStatus(gGameStatus) {
            // setSpriteSheetDimensions(spriteSheetDimensions);
            
           }


            
    virtual const std::vector<int> getAnimationIndices() const { 
        printf("hi\n");
        return  atlas.at(*gGameStatus);
    }

private:
    std::map<GameStatus, std::vector<int>> atlas;
    GameStatus *gGameStatus;
    float minHeight, maxHeight;
};

#endif