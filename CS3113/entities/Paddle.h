#ifndef PADDLE_H
#define PADDLE_H
#include "Entity.h"


class Paddle: public Entity
{
public:
    Paddle(Vector2 position, Vector2 scale, const char *textureFilepath, 
           float minHeight, float maxHeight,
           Vector2 spriteSheetDimensions,std::vector<int> animationIndices) : 
           minHeight(minHeight), maxHeight(maxHeight), 
           Entity(position, scale, textureFilepath, 
           spriteSheetDimensions, animationIndices) {}


    void update(float deltaTime){
        Entity::update(deltaTime);
        if(getPosition().y + getColliderDimensions().y/2.0f > maxHeight) setPositionY(maxHeight - getColliderDimensions().y/2.0f);
        if(getPosition().y - getColliderDimensions().y/2.0f < minHeight) setPositionY(minHeight + getColliderDimensions().y/2.0f);

        if(upgradeCountdpwn > 0){
            upgradeCountdpwn -= deltaTime;
        }
        if(upgraded && upgradeCountdpwn < 0){
            std::vector<int> a = getAnimationIndices();
            setAnimationIndices({a[0] +4 ,a[1] +4});
            upgraded = false;
        }
    }

    void reset(){
        if(upgraded){
            std::vector<int> a = getAnimationIndices();
            setAnimationIndices({a[0] +4 ,a[1] +4});
            upgraded = false;
        }
    }

    void upgrade(){
        if(upgraded) return;
        upgraded = true;
        upgradeCountdpwn = 10;
        std::vector<int> a = getAnimationIndices();
        setAnimationIndices({a[0] -4 ,a[1] -4});
        
    }

private:
    float minHeight, maxHeight;
    float upgradeCountdpwn = 0;
    bool upgraded = false;
};

#endif