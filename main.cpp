#include "CS3113/entities/Entity.h"
#include "CS3113/entities/Paddle.h" 
#include "CS3113/entities/Ball.h" 
#include "CS3113/entities/Button.h" 
#include "CS3113/entities/Score.h" 

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 120;

constexpr char    BG_COLOUR[] = "#FFFFFFF";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPreviousTicks = 0.0f;

Paddle *gLeftPaddle = nullptr;
Paddle *gRightPaddle = nullptr;
Ball *gBall = nullptr;
Entity *gGameBg = nullptr;
Entity *gStartBg = nullptr;

Button *gSinglePlayer = nullptr;
Button *gMultiPlayer = nullptr;

Score *gLeftScore = nullptr;
Score *gRightScore = nullptr;

Entity *gWaitingBg = nullptr;
Entity *gP1bg = nullptr;
Entity *gP2bg = nullptr;

enum GameStatus {PLAYING, WAITING, STARTMENU, PLAYER1, PLAYER2};

bool gAuto = false;

GameStatus gGameStatus = STARTMENU;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();


void reset(){
    gLeftPaddle->setPosition({ 60, SCREEN_HEIGHT / 2 });
    gRightPaddle->setPosition({ SCREEN_WIDTH-60, SCREEN_HEIGHT / 2 });
    gBall->reset();
}

void resetScores(){
    gLeftScore->reset();
    gRightScore->reset();
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation / Entities");

    float sizeRatio  = 48.0f / 64.0f;

    /*
    By default, the colliders of our entity object will have the same
    dimensions as the entity's scale.

    Assets from @see https://sscary.itch.io/the-adventurer-female
    */
   gWaitingBg = new Entity(
       ORIGIN,// position
       {SCREEN_WIDTH,SCREEN_HEIGHT}, // scale
       "./assets/waiting.png"    // texture file address
    //    ATLAS,                        // single image or atlas?
    //    { 1,1 },                     // atlas dimensions
    //    ballAtlas                // actual atlas
    );
   gGameBg = new Entity(
       ORIGIN,// position
       {SCREEN_WIDTH,SCREEN_HEIGHT}, // scale
       "./assets/bg.png"    // texture file address
    //    ATLAS,                        // single image or atlas?
    //    { 1,1 },                     // atlas dimensions
    //    ballAtlas                // actual atlas
    );
   gP1bg = new Entity(
       ORIGIN,// position
       {SCREEN_WIDTH,SCREEN_HEIGHT}, // scale
       "./assets/player1.png",
        // ATLAS,                        // single image or atlas?
       { 2,1 },                     // atlas dimensions
       {0,1}                 // actual atlas
    );
   gP2bg = new Entity(
       ORIGIN,// position
       {SCREEN_WIDTH,SCREEN_HEIGHT}, // scale
       "./assets/player2.png",
    //    ATLAS,                        // single image or atlas?
       { 2,1 },                     // atlas dimensions
       {0,1}                // actual atlas
    );


   gLeftScore = new Score(
        {SCREEN_WIDTH/2- 30, 60},// position
        {13*4.5f, 24*4.5f}, // scale
        "./assets/gameplay.png",    // texture file address
        // ATLAS,                        // single image or atlas?
        { 3,10 },                     // atlas dimensions
        { 20,21,22,23,24,25,26,27,28,29 }               // actual atlas
    );
   gRightScore = new Score(
        {SCREEN_WIDTH/2+ 30, 60},// position
        {13*4.5f, 24*4.5f}, // scale
        "./assets/gameplay.png",    // texture file address
        // ATLAS,                        // single image or atlas?
        { 3,10 },                     // atlas dimensions
        { 10,11,12,13,14,15,16,17,18,19 }                // actual atlas
    );
   gStartBg = new Entity(
       ORIGIN,// position
       {SCREEN_WIDTH,SCREEN_HEIGHT}, // scale
       "./assets/startmenubg.png",    // texture file address
    //    ATLAS,                        // single image or atlas?
       { 2,1 },                     // atlas dimensions
       {0,1}                // actual atlas
    );


   gBall = new Ball(
       ORIGIN,// position
       {13*4.5f, 24*4.5f}, // scale
       "./assets/gameplay.png",    // texture file address
        30.0f, SCREEN_HEIGHT - 30.0f,
        40.0f, SCREEN_WIDTH - 40.0f,
    //    ATLAS,                        // single image or atlas?
       { 3,10 },                     // atlas dimensions
       { 4,5 }                // actual atlas
    );
    gBall->setColliderDimensions({30.0f,30.0f});


   gSinglePlayer = new Button(
        {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2 + 10},
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
    //    ATLAS,                        // single image or atlas?
       { 3,2 },                     // atlas dimensions
       {0,1}                // actual atlas
    );
    gSinglePlayer->setColliderDimensions({150.0f,60.0f});
   gMultiPlayer = new Button(
       {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2 + 80},// position
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
    //    ATLAS,                        // single image or atlas?
       { 3,2 },                     // atlas dimensions
       {2,3}                // actual atlas
    );
    gMultiPlayer->setColliderDimensions({150.0f,60.0f});
    
    gLeftPaddle = new Paddle(
        { 60, SCREEN_HEIGHT / 2 },// position
        {13*4.5f, 24*4.5f}, // scale
        "./assets/gameplay.png",      // texture file address
        40.0f, SCREEN_HEIGHT - 40.0f,
        // ATLAS,                        // single image or atlas?
        { 3,10 },                     // atlas dimensions
        {0,1}                // actual atlas
    );
    gLeftPaddle->setColliderDimensions({30,90});

    gRightPaddle = new Paddle( 
        { SCREEN_WIDTH - 60, SCREEN_HEIGHT /2 },// position
        {13*4.5f, 24*4.5f}, // scale
        "./assets/gameplay.png",       // texture file address
        40.0f, SCREEN_HEIGHT - 40.0f,
        // ATLAS,                        // single image or atlas?
        { 3,10 },                     // atlas dimensions
        {2,3}                // actual atlas
    );
    gRightPaddle->setColliderDimensions({30,90});


    SetTargetFPS(FPS);
}

void processInput() 
{
    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;

    if(gGameStatus == STARTMENU || gGameStatus == PLAYER1 || gGameStatus == PLAYER2){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gSinglePlayer->CollidingWithPoint(GetMousePosition())){
            gGameStatus = WAITING;
            gAuto = true;
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gMultiPlayer->CollidingWithPoint(GetMousePosition())){
            gGameStatus = WAITING;
            gAuto = false;
        }
    }

    if (gGameStatus == WAITING && IsKeyPressed(KEY_SPACE)){
        gGameStatus = PLAYING;
        gBall->setDead(false);
    }

    if(IsKeyPressed(KEY_T)) gAuto = !gAuto;
    
    if(gGameStatus == PLAYING){
        gLeftPaddle->resetMovement();
        gRightPaddle->resetMovement();

        if      (IsKeyDown(KEY_W)) gLeftPaddle->moveUp();
        else if (IsKeyDown(KEY_S)) gLeftPaddle->moveDown();

        if(!gAuto){
            if      (IsKeyDown(KEY_UP)) gRightPaddle->moveUp();
            else if (IsKeyDown(KEY_DOWN)) gRightPaddle->moveDown();
        } else {
            if(gBall->getPosition().y - gRightPaddle->getPosition().y > 5) gRightPaddle->moveDown();
            else if(gRightPaddle->getPosition().y - gBall->getPosition().y > 5) gRightPaddle->moveUp();
        }
    }

}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    if(gGameStatus == STARTMENU){
        gStartBg->update(deltaTime);
        gSinglePlayer->update(deltaTime);
        gMultiPlayer->update(deltaTime);
    }

    if(gGameStatus == PLAYER1){
        gP1bg->update(deltaTime);
        gSinglePlayer->update(deltaTime);
        gMultiPlayer->update(deltaTime);
    }

    if(gGameStatus == PLAYER2){
        gP2bg->update(deltaTime);
        gSinglePlayer->update(deltaTime);
        gMultiPlayer->update(deltaTime);
    }

    if(gGameStatus == PLAYING){
        // we're not checking collisions—for now
        gLeftPaddle->update(deltaTime);
        gRightPaddle->update(deltaTime);
        gBall->update(deltaTime);
        
        gBall->paddleInteraction(gLeftPaddle);
        gBall->paddleInteraction(gRightPaddle);
        // if(gBall->isColliding(gLeftPaddle)) printf("AAA\n");

        if(gBall->getDead()){
            gGameStatus = WAITING;
            if(gBall->getPosition().x > SCREEN_WIDTH /2.0f) gLeftScore->increaseScore();
            else gRightScore->increaseScore();
            
            reset();

            if(gLeftScore->getWon()) {
                gGameStatus = PLAYER1;
                resetScores();
            }
            if(gRightScore->getWon()) {
                gGameStatus = PLAYER2;
                resetScores();
            }
            
        }
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    
    
    if(gGameStatus == STARTMENU){
        gStartBg->render();
        gSinglePlayer->render();
        gMultiPlayer->render();
    }

    if(gGameStatus == PLAYER1){
        gP1bg->render();
        gSinglePlayer->render();
        gMultiPlayer->render();
    }
    if(gGameStatus == PLAYER2){
        gP2bg->render();
        gSinglePlayer->render();
        gMultiPlayer->render();
    }
    
    if(gGameStatus == PLAYING || gGameStatus == WAITING){
        gGameBg->render();
        if(gGameStatus == WAITING){
            gWaitingBg->render();
        }
        gLeftPaddle->render();
        gRightPaddle->render();
        gBall->render();

        gLeftScore->render();
        gRightScore->render();
    }

    
    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow();
    
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}