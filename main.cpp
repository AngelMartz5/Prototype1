#include "raylib.h"
#include "Thing.h"
#include "Window.h"
#include "SignalBus.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    
    SignalBus SignalRederence{};
    Window windowScreen;
    InitWindow(windowScreen.width, windowScreen.height, "Test GAME");
    Thing ActualPlayer{SP_CIRCLE, GREEN, {windowScreen.width/2, windowScreen.height/ 2}, {"Angel"}, true};
    Thing OtherBlock{SP_RECTANGLE , RED, {100,windowScreen.height/ 2}, {"Pedro"}, true} ;
    Thing OtherBlock2{SP_RECTANGLE , PURPLE, {windowScreen.width/2+200,windowScreen.height/ 2}, {"Roberto"}, true} ;
    Thing* CollisionPrototype[6]{};
    CollisionPrototype[1] = &ActualPlayer;
    CollisionPrototype[4] = &OtherBlock;
    CollisionPrototype[3] = &OtherBlock2;
    int numb = 0;
    for (auto targets: CollisionPrototype)
    {
        if(targets != nullptr){
            if (targets->HasCollsion){

                cout << "NAME:  " << targets->MyName << "  IN:  " << numb << endl;
            }
        }
        numb++;
    }

    //SignalRederence.AddCollision(ActualPlayer);
    
    SignalRederence.AddCollision(&ActualPlayer);
    SignalRederence.AddCollision(&OtherBlock);
    SignalRederence.AddCollision(&OtherBlock2);
    //cout << "EL NAME IS : " << SignalRederence.CollisionArray[1]->MyName<< endl;
    /*
    SignalRederence.AddCollision(OtherBlock);
    */
    Vector2 PlayerMovement {0,0};
    int direction = 1;
    int direction2 = 1;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        /*if(collision_with_axe){
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        */
        
        /*
        //Update Collsiion
        collision_with_axe =   (r_circle_x >= l_axe_x) &&   
                            (b_circle_y >= u_axe_y) && 
                            (l_circle_x <= r_axe_x) && 
                            (u_circle_y <= b_axe_y);
        */
        ClearBackground(WHITE);
        
        ActualPlayer.DelltaProcess(SignalRederence.CollisionArray);
        OtherBlock.DelltaProcess(SignalRederence.CollisionArray);
        OtherBlock2.DelltaProcess(SignalRederence.CollisionArray);
        //std::cout << "CollisionBorder: " << OtherBlock.IsColliding <<std::endl;
        
        if(IsKeyDown(KEY_D)){
            PlayerMovement.x = 1;
        }
        else if(IsKeyDown(KEY_A)){
            PlayerMovement.x = -1;
        }
        else{
            PlayerMovement.x = 0;
        }
        if(IsKeyDown(KEY_S)){
            PlayerMovement.y = 1;
        }
        else if(IsKeyDown(KEY_W)){
            PlayerMovement.y = -1;
        }
        else{
            PlayerMovement.y = 0;
        }
        
        
        ActualPlayer.Movement(PlayerMovement.x,PlayerMovement.y);
        //move de axe
        
        if (OtherBlock.IsColliding){
            direction *= -1;
        }
        OtherBlock.Movement(0.f,direction);

        if (OtherBlock2.IsColliding){
            direction2 *= -1;
        }
        OtherBlock2.Movement(direction2,0.f);
        //if(b_axe_y >= u_circle_y && u_axe_y <= b_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x){
        
        
        EndDrawing();
    }
    

}