#include "CS3113/entities/Entity.h"
#include "CS3113/entities/Paddle.h" 
#include "CS3113/entities/Ball.h" 
#include "CS3113/entities/Button.h" 
#include "CS3113/entities/Score.h" 
#include "CS3113/entities/Background.h" 
#include "CS3113/entities/PowerUp.h" 

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
// Ball *gBall[3];
Background *gBg = nullptr;
// Entity *gStartBg = nullptr;

Button *gSinglePlayer = nullptr;
Button *gMultiPlayer = nullptr;

Button *gEasy = nullptr;
Button *gMid = nullptr;
Button *gHard = nullptr;

Score *gLeftScore = nullptr;
Score *gRightScore = nullptr;

PowerUp *gPowerUp = nullptr;

std::vector<Ball*> gBalls;

// Entity *gWaitingBg = nullptr;
// Entity *gP1bg = nullptr;
// Entity *gP2bg = nullptr;

float gSpeed = 500.0f;

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

    gLeftPaddle->reset();
    gRightPaddle->reset();
    gBalls[0]->reset(gSpeed);
    for(size_t i = gBalls.size() -1; i >= 1; --i){
        // printf("hi%i\n", i);
        delete gBalls[i];
        gBalls.pop_back();
    }
    gPowerUp->reset();
}

void newBall(){
    gBalls.push_back(new Ball(
            ORIGIN,// position
            {13*4.5f, 24*4.5f}, // scale
            "./assets/gameplay.png",    // texture file address
            30.0f, SCREEN_HEIGHT - 30.0f,
            40.0f, SCREEN_WIDTH - 40.0f,
            { 3,10 },                     // atlas dimensions
            { 4,5 },
            gSpeed              // actual atlas
        ));
        gBalls[gBalls.size() -1]->setColliderDimensions({30.0f,30.0f});
}

void resetScores(){
    gLeftScore->reset();
    gRightScore->reset();
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation / Entities");

    float sizeRatio  = 48.0f / 64.0f;

    std::map<GameStatus, std::vector<int>> bgMap{
        {WAITING, {1}},
        {PLAYING, {0}},
        {PLAYER1, {2,3}},
        {PLAYER2, {4,5}},
        {STARTMENU, {6,7}},
        {DIFFSELECT, {6,7}}
    };

    gBg = new Background(
        ORIGIN,// position
       {SCREEN_WIDTH,SCREEN_HEIGHT}, // scale
       "./assets/bg.png",
       { 4,2 },  &gGameStatus,                    // atlas dimensions
       bgMap
    );

    gPowerUp = new PowerUp(
            ORIGIN,// position
            {13*4.5f, 24*4.5f}, // scale
            "./assets/gameplay.png",    // texture file address
            60.0f, SCREEN_HEIGHT - 60.0f,
            60.0f, SCREEN_WIDTH - 60.0f,
            { 3,10 },                     // atlas dimensions
            { 6 }        // actual atlas
        );

   gLeftScore = new Score(
        {SCREEN_WIDTH/2- 40, 70},// position
        {13*4.5f, 24*4.5f}, // scale
        "./assets/gameplay.png",    // texture file address
        { 3,10 },                     // atlas dimensions
        { 20,21,22,23,24,25,26,27,28,29 }               // actual atlas
    );
   gRightScore = new Score(
        {SCREEN_WIDTH/2+ 40, 70},// position
        {13*4.5f, 24*4.5f}, // scale
        "./assets/gameplay.png",    // texture file address
        { 3,10 },                     // atlas dimensions
        { 10,11,12,13,14,15,16,17,18,19 }                // actual atlas
    );


   gSinglePlayer = new Button(
        {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2 + 10},
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
       { 5,2 },                     // atlas dimensions
       {0,1}                // actual atlas
    );
    gSinglePlayer->setColliderDimensions({150.0f,60.0f});
   gMultiPlayer = new Button(
       {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2 + 80},// position
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
       { 5,2 },                     // atlas dimensions
       {2,3}                // actual atlas
    );
    gMultiPlayer->setColliderDimensions({150.0f,60.0f});


    gEasy = new Button(
       {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2},// position
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
       { 5,2 },                     // atlas dimensions
       {4,5}                // actual atlas
    );
    gEasy->setColliderDimensions({150.0f,60.0f});
    gMid = new Button(
       {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2 + 60},// position
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
       { 5,2 },                     // atlas dimensions
       {6,7}                // actual atlas
    );
    gMid->setColliderDimensions({150.0f,60.0f});

    gHard = new Button(
       {SCREEN_WIDTH/2 , SCREEN_HEIGHT/ 2 + 120},// position
       {80*4.5f, 22*4.5f}, // scale
       "./assets/ui.png",    // texture file address
       { 5,2 },                     // atlas dimensions
       {8,9}                // actual atlas
    );
    gHard->setColliderDimensions({150.0f,60.0f});




    
    gLeftPaddle = new Paddle(
        { 60, SCREEN_HEIGHT / 2 },// position
        {13*4.5f, 30*4.5f}, // scale
        "./assets/upgrade.png",      // texture file address
        40.0f, SCREEN_HEIGHT - 40.0f,
        { 1,8 },                     // atlas dimensions
        {4,5}                // actual atlas
    );
    gLeftPaddle->setColliderDimensions({30,90});

    gRightPaddle = new Paddle( 
        { SCREEN_WIDTH - 60, SCREEN_HEIGHT /2 },// position
        {13*4.5f, 30*4.5f}, // scale
        "./assets/upgrade.png",       // texture file address
        40.0f, SCREEN_HEIGHT - 40.0f,
        { 1,8 },                     // atlas dimensions
        {6,7}                // actual atlas
    );
    gRightPaddle->setColliderDimensions({30,90});

    newBall();

    SetTargetFPS(FPS);
}

void processInput() 
{
    gLeftPaddle->resetMovement();
    gRightPaddle->resetMovement();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;

    if(gGameStatus == DIFFSELECT){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gEasy->CollidingWithPoint(GetMousePosition())){
            gGameStatus = WAITING;
            gSpeed = 400;
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gMid->CollidingWithPoint(GetMousePosition())){
            gGameStatus = WAITING;
            gSpeed = 500;
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gHard->CollidingWithPoint(GetMousePosition())){
            gGameStatus = WAITING;
            gSpeed = 600;
        }
    }

    if(gGameStatus == STARTMENU || gGameStatus == PLAYER1 || gGameStatus == PLAYER2){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gSinglePlayer->CollidingWithPoint(GetMousePosition())){
            gGameStatus = DIFFSELECT;
            gAuto = true;
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gMultiPlayer->CollidingWithPoint(GetMousePosition())){
            gGameStatus = DIFFSELECT;
            gAuto = false;
        }
    }

    if (gGameStatus == WAITING && IsKeyPressed(KEY_SPACE)){
        gGameStatus = PLAYING;
        gBalls[0]->setDead(false);
        gBalls[0]->reset(gSpeed);
    }

    if (gGameStatus == PLAYING && IsKeyPressed(KEY_ONE)){
        newBall();
    }
    if (gGameStatus == PLAYING && IsKeyPressed(KEY_TWO)){
        newBall();
        newBall();
    }
    if (gGameStatus == PLAYING && IsKeyPressed(KEY_THREE)){
        newBall();
        newBall();
        newBall();
    }

  

    if(IsKeyPressed(KEY_T)) gAuto = !gAuto;
    
    if(gGameStatus == PLAYING){

        if      (IsKeyDown(KEY_W)) gLeftPaddle->moveUp();
        else if (IsKeyDown(KEY_S)) gLeftPaddle->moveDown();

        if(!gAuto){
            if      (IsKeyDown(KEY_UP)) gRightPaddle->moveUp();
            else if (IsKeyDown(KEY_DOWN)) gRightPaddle->moveDown();
        } else {
            Ball* b = gBalls[0];
            for(Ball* ball : gBalls){
                if(b->getDead() || (!ball->getDead() && ball->getPosition().x > b->getPosition().x)) b = ball;
            }

            if(b->getPosition().y - gRightPaddle->getPosition().y > 5) gRightPaddle->moveDown();
            else if(gRightPaddle->getPosition().y - b->getPosition().y > 5) gRightPaddle->moveUp();
        }
    }

}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    gBg->update(deltaTime);

    if(gGameStatus == DIFFSELECT){
        gEasy->update(deltaTime);
        gMid->update(deltaTime);
        gHard->update(deltaTime);
    }

    if(gGameStatus == STARTMENU || gGameStatus == PLAYER1 || gGameStatus == PLAYER2){
        // gStartBg->update(deltaTime);
        gSinglePlayer->update(deltaTime);
        gMultiPlayer->update(deltaTime);
    }

    if(gGameStatus == WAITING){
        gLeftPaddle->update(deltaTime);
        gRightPaddle->update(deltaTime);
    }

    if(gGameStatus == PLAYING){
        // we're not checking collisions—for now
        gLeftPaddle->update(deltaTime);
        gRightPaddle->update(deltaTime);

        gPowerUp->update(deltaTime, gLeftPaddle, gRightPaddle);

        bool allDead = true;
        for(const Ball* b: gBalls){
            // printf("%i\n", b->getDead());
            if(!b->getDead()){
                allDead = false;
                break;
            }
        }

        if(allDead){
            reset();
            gGameStatus = WAITING;
            
        }

        // printf("balls\n");

        for (Ball* b : gBalls){
            // printf("%i\n", b->getDead());
            if(!b->getDead()) {
                b->update(deltaTime);
                b->paddleInteraction(gLeftPaddle);
                b->paddleInteraction(gRightPaddle);
                
                if(!b->getBeenScored()){
                    if(b->getPosition().x > SCREEN_WIDTH /2.0f) gLeftScore->increaseScore();
                    else gRightScore->increaseScore();
                    b->setBeenScored(true);
                }

                if(gLeftScore->getWon()) {
                    gGameStatus = PLAYER1;
                    resetScores();
                    reset();
                }
                if(gRightScore->getWon()) {
                    gGameStatus = PLAYER2;
                    resetScores();
                    reset();
                }
            }
        }

        
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    gBg->render();
    

    if(gGameStatus == DIFFSELECT){
        gEasy->render();
        gMid->render();
        gHard->render();
    }
    
    if(gGameStatus == STARTMENU){
        // gStartBg->render();
        gSinglePlayer->render();
        gMultiPlayer->render();
    }

    if(gGameStatus == PLAYER1){
        // gP1bg->render();
        gSinglePlayer->render();
        gMultiPlayer->render();
    }
    if(gGameStatus == PLAYER2){
        // gP2bg->render();
        gSinglePlayer->render();
        gMultiPlayer->render();
    }

    if(gGameStatus == PLAYING || gGameStatus == WAITING){
        // gGameBg->render();
        // if(gGameStatus == WAITING){
            // gWaitingBg->render();
        // }
        gPowerUp->render();
        gLeftPaddle->render();
        gRightPaddle->render();

        for(Ball* b: gBalls){
            if(!b->getDead()) b->render();
        }

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