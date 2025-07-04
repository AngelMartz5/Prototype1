#include "Thing.h"
#include "raymath.h" 
#include <iostream>
#include "Window.h"
#include <string>

Thing::Thing(Shapes WhichShapeChose, Color WhichColorChose, Vector2 PositionSpawn,string OWNNAME, bool Coll):
    x(PositionSpawn.x),
    y(PositionSpawn.y),
    MyName(OWNNAME),
    HasCollsion(Coll){
    MyShape = WhichShapeChose;
    MyColor = WhichColorChose;
    switch (MyShape)
    {
    case SP_CIRCLE:
        size /= 2;
        break;
    }
}

Vector2 Thing::saberLocalizacion(){
    return Vector2{x,y} ;
}

Thing* Thing::CollisionDectector(Thing* thingsArray[]){
    Thing* WhoEntrerd = thingsArray[0];
    return WhoEntrerd;
}

void Thing::Movement(float xMov, float yMov){
    
    MovementVector = Vector2{xMov * Velocity,yMov * Velocity};
    if (xMov >0){
        FaceX = 1;
    }else{
        FaceX = -1;
    }
}

void Thing::DelltaProcess(){
    
    //std::cout << "LastX: " << lastX << "  X: " << x << std::endl;
    CanYouMoveThen() ? IsColliding = false :IsColliding = true;
    if (!IsColliding){
        x += MovementVector.x;
        y += MovementVector.y;
    }else{
        if (CollisionDirection.x != 0){
            if (CollisionDirection.y == 0){
                y += MovementVector.y;
            }
            
            
        }
        if (CollisionDirection.y != 0){
            if (CollisionDirection.x == 0){
                x += MovementVector.x;
            }
           
        }
    }

    switch (MyShape)
    {
    case SP_CIRCLE:
        left_x = x - size;
        up_y = y - size;
        right_x = x + size;
        button_y = y + size;
        DrawCircle(x,y,size,BLUE);
        break;
    case SP_RECTANGLE:
        left_x = x;
        up_y = y;
        right_x = x + size;
        button_y = y + size;
        DrawRectangle(x,y,size,size,MyColor);
        break;
    default:
        break;
    }
    
}

bool Thing::CanYouMoveThen(){
    bool resultM = true;
    float Nleft_x{ left_x + MovementVector.x };
    float Nright_x{ right_x + MovementVector.x };
    float Nup_y{ up_y+ MovementVector.y };
    float Nbutton_y{ button_y+ MovementVector.y };
    Vector2 Result = CollisionBorder(Nright_x,Nleft_x,Nbutton_y, Nup_y);
    //std::cout << " X:  " << Result.x << "  Y: " << Result.y<< std::endl;
    if ( Result != Vector2{0,0}){
        resultM = false;
    }

    return resultM;
}

Vector2 Thing::CollisionBorder(float right__x, float left__x, float button__y, float up__y){
    Window windowScreen;
    if (right__x > windowScreen.width){
        x = windowScreen.width-size;
        CollisionDirection.x = 1;
    }else if(left__x < 0){
        switch (MyShape)
        {
        case SP_CIRCLE:
            x = 0+size;
            break;
        case SP_RECTANGLE:
            x = 0;
        break;
        }
        CollisionDirection.x = -1;
    }else{
        CollisionDirection.x = 0;
    }

    if (button__y > windowScreen.height){
        y = windowScreen.height-size;
        CollisionDirection.y = 1;

    }else if(up__y < 0){
        switch (MyShape)
        {
        case SP_CIRCLE:
            y = 0+size;
            break;
        case SP_RECTANGLE:
            y = 0;
        break;
        }
        CollisionDirection.y = -1;
    }else{
        CollisionDirection.y = 0;
    }
    

    return CollisionDirection;
}

Vector2 Thing::Collisions(Thing* ArrayOthers[]){

}

void Thing::BackHandsOfTime(){
    x = lastX;
    y = lastY;
}