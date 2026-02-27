#ifndef SCORE_H
#define SCORE_H
#include "Entity.h"

class Score: public Entity
{
public:
    Score(Vector2 position, Vector2 scale, const char *textureFilepath,
           Vector2 spriteSheetDimensions,
           std::vector<int> animationIndices) :  
           Entity(position, scale, textureFilepath, 
          spriteSheetDimensions, animationIndices) {}


    void animate(float deltaTime){}

    void increaseScore(){
        if(getFrameIndex() == 4) won = true;
        incrementFrame();
    }
    bool getWon() const {return won;}

    void reset(){
        setFrameIndex(0);
        won = false;
    }

private:
    float minHeight, maxHeight;
    bool won = false;
};

#endif