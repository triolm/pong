#ifndef ENTITY_H
#define ENTITY_H

#include "cs3113.h"

// enum Direction { LEFT, UP, RIGHT, DOWN }; // For walking

class Entity
{
private:
    Vector2 mPosition;
    Vector2 mMovement;

    Vector2 mScale;
    Vector2 mColliderDimensions;
    
    Texture2D mTexture;
    TextureType mTextureType;
    Vector2 mSpriteSheetDimensions;
    
    // std::map<Direction, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    // Direction mDirection;
    int mFrameSpeed;

    int mCurrentFrameIndex = 0;
    float mAnimationTime = 0.0f;

    int mSpeed;
    float mAngle;
    void animate(float deltaTime);

protected:
    bool isColliding(Entity *other) const;
    
public:
    static const int DEFAULT_SIZE        = 250;
    static const int DEFAULT_SPEED       = 200;
    static const int DEFAULT_FRAME_SPEED = 14;

    Entity();
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath);
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        //TextureType textureType, 
        Vector2 spriteSheetDimensions, std::vector<int> animationIndices); //
        //std::map<Direction, std::vector<int>> animationAtlas);
    ~Entity();

    void update(float deltaTime);
    void render();
    void normaliseMovement() { Normalise(&mMovement); };

    void moveUp()    { mMovement.y = -1; }// mDirection = UP;    }
    void moveDown()  { mMovement.y =  1; }// mDirection = DOWN;  }
    void moveLeft()  { mMovement.x = -1; }// mDirection = LEFT;  }
    void moveRight() { mMovement.x =  1; }// mDirection = RIGHT; }

    virtual const std::vector<int> getAnimationIndices() const { return mAnimationIndices; }
    virtual int getMaxFrame() const { return mAnimationIndices.size(); }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }

    Vector2     getPosition()              const { return mPosition;              }
    Vector2     getMovement()              const { return mMovement;              }
    Vector2     getScale()                 const { return mScale;                 }
    Vector2     getColliderDimensions()    const { return mColliderDimensions;    }
    Vector2     getSpriteSheetDimensions() const { return mSpriteSheetDimensions; }
    Texture2D   getTexture()               const { return mTexture;               }
    TextureType getTextureType()           const { return mTextureType;           }
    // Direction   getDirection()             const { return }// mDirectio }//n;             }
    int         getFrameSpeed()            const { return mFrameSpeed;            }
    int         getSpeed()                 const { return mSpeed;                 }
    float       getAngle()                 const { return mAngle;                 }
    float       getFrameIndex()            const { return mCurrentFrameIndex;     }


   // std::map<Direction, std::vector<int>> getAnimationAtlas() const { return mAnimationAtlas; }

    void incrementFrame(){
        mCurrentFrameIndex++;
        mCurrentFrameIndex %= getMaxFrame();        
    }

    void setPosition(Vector2 newPosition)
        { mPosition = newPosition;                }
    void setPositionX(float x)
        { mPosition.x = x;                        }
    void setPositionY(float y)
        { mPosition.y = y;                        }
    void setMovement(Vector2 newMovement)
        { mMovement = newMovement;                }
    void setMovementX(float x)
        { mMovement.x = x;                        }
    void setMovementY(float y)
        { mMovement.y = y;                        }
    void setScale(Vector2 newScale)
        { mScale = newScale;                      }
    void setColliderDimensions(Vector2 newDimensions) 
        { mColliderDimensions = newDimensions;    }
    void setSpriteSheetDimensions(Vector2 newDimensions) 
        { mSpriteSheetDimensions = newDimensions; }
    void setSpeed(int newSpeed)
        { mSpeed  = newSpeed;                     }
    void setFrameSpeed(int newSpeed)
        { mFrameSpeed = newSpeed;                 }
    void setFrameIndex(int newSpeed)
        { mCurrentFrameIndex = newSpeed;          }
    void setAngle(float newAngle) 
        { mAngle = newAngle;                      }
};

#endif // ENTITY_H