#include "CS3113/entities/Entity.h"
#include "CS3113/entities/Paddle.h" 
#include "CS3113/entities/Ball.h" 

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

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation / Entities");

    // std::map<Direction, std::vector<int>> animationAtlas = {
    //     {DOWN,  {  1 }},
    //     {LEFT,  {  8,  9, 10, 11, 12, 13, 14, 15 }},
    //     {UP,    { 24, 25, 26, 27, 28, 29, 30, 31 }},
    //     {RIGHT, { 40, 41, 42, 43, 44, 45, 46, 47 }},
    // };

    float sizeRatio  = 48.0f / 64.0f;

    /*
    By default, the colliders of our entity object will have the same
    dimensions as the entity's scale.

    Assets from @see https://sscary.itch.io/the-adventurer-female
    */
   gBall = new Ball(
       ORIGIN,// position
       {20,20}, // scale
       "./assets/drawing_path21.png",    // texture file address
        05.0f, SCREEN_HEIGHT - 05.0f,
        10.0f, SCREEN_WIDTH - 10.0f
       // ATLAS,                        // single image or atlas?
       // { 1,1 },                     // atlas dimensions
       // animationAtlas                // actual atlas
   );
   gBall->moveLeft();
    gLeftPaddle = new Paddle(
        { 30, SCREEN_HEIGHT / 2 },// position
        {15.30f, 60.40f}, // scale
        "./assets/drawing_rect21.png",      // texture file address
        50.0f, SCREEN_HEIGHT - 50.0f
        // ATLAS,                        // single image or atlas?
        // { 1,1 },                     // atlas dimensions
        // animationAtlas                // actual atlas
    );

    gRightPaddle = new Paddle( 
        { SCREEN_WIDTH - 30, SCREEN_HEIGHT /2 },// position
        {15.30f, 60.40f}, // scale
        "./assets/drawing_rect21.png",       // texture file address
        50.0f, SCREEN_HEIGHT - 50.0f
        // ATLAS,                        // single image or atlas?
        // { 1,1 },                     // atlas dimensions
        // animationAtlas                // actual atlas
    );

    SetTargetFPS(FPS);
}

void processInput() 
{
    gLeftPaddle->resetMovement();
    gRightPaddle->resetMovement();


    // if      (IsKeyDown(KEY_A)) gLeftPaddle->moveLeft();
    // else if (IsKeyDown(KEY_D)) gLeftPaddle->moveRight();
    if      (IsKeyDown(KEY_W)) gLeftPaddle->moveUp();
    else if (IsKeyDown(KEY_S)) gLeftPaddle->moveDown();

    if      (IsKeyDown(KEY_UP)) gRightPaddle->moveUp();
    else if (IsKeyDown(KEY_DOWN)) gRightPaddle->moveDown();

    // to avoid faster diagonal speed
    // if (GetLength(gLeftPaddle->getMovement()) > 1.0f) 
    //     gLeftPaddle->normaliseMovement();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    // we're not checking collisions—for now
    gLeftPaddle->update(deltaTime);
    gRightPaddle->update(deltaTime);
    gBall->update(deltaTime);
    
    gBall->paddleInteraction(gLeftPaddle);
    gBall->paddleInteraction(gRightPaddle);
    // if(gBall->isColliding(gLeftPaddle)) printf("AAA\n");
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    gLeftPaddle->render();
    gRightPaddle->render();
    gBall->render();

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