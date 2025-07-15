#include "Thing.h"
#include "raymath.h" 
#include <iostream>
#include "Window.h"
#include <string>
#include "raymath.h"

using namespace std;

Thing::Thing(Shapes WhichShapeChose, Color WhichColorChose, Vector2 PositionSpawn,string OWNNAME, bool Coll, bool AreaColl):
    x(PositionSpawn.x),
    y(PositionSpawn.y),
    MyName(OWNNAME),
    HasCollsion(Coll),
    DetectionArea(AreaColl){
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

void Thing::Movement(float xMov, float yMov){
    
    MovementVector = Vector2{xMov * Velocity,yMov * Velocity};
    if (xMov >0){
        FaceX = 1;
    }else{
        FaceX = -1;
    }
}

void Thing::DelltaProcess(vector<Thing*> ArrayOthers){
    if(HasCollsion){
        
        CollisionsArray = ArrayOthers;
    }
    
    CanYouMoveThen() ? IsColliding = false :IsColliding = true;
    //std::cout << "LastX: " << lastX << "  X: " << x << std::endl;
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
    Vector2 ResCool = CollisionBorder(Nright_x,Nleft_x,Nbutton_y, Nup_y);
    if(DetectionArea){
        if(ResCool != Vector2{0.f,0.f}){
            resultM = false;
        }
    }else{
        Vector2 ResultColl{0.f,0.f};
        if (CollisionsArray.size() != 0 ){
            ResultColl = Collisions(Nright_x,Nleft_x,Nbutton_y, Nup_y );
        }
        
        //std::cout << " X:  " << Result.x << "  Y: " << Result.y<< std::endl;
        if (ResultColl != Vector2{0,0} ){
            resultM = false;
        }
    }

    return resultM;
}

Vector2 Thing::Collisions(float right__x, float left__x, float button__y, float up__y) {
    for (Thing* COLL : CollisionsArray) {
        if (COLL == this) continue;

        float otherLeft   = COLL->left_x;
        float otherRight  = COLL->right_x;
        float otherTop    = COLL->up_y;
        float otherBottom = COLL->button_y;

        bool overlapX = (left__x < otherRight && right__x > otherLeft);
        bool overlapY = (up__y < otherBottom && button__y > otherTop);
        bool isArea = COLL->DetectionArea;

        if (overlapX && overlapY) {
            if (!isArea) {
                // --- Colisión física ---
                float overlapRight  = right_x - otherLeft;
                float overlapLeft   = otherRight - left_x;
                float overlapBottom = button_y - otherTop;
                float overlapTop    = otherBottom - up_y;

                float penX = std::min(overlapRight, overlapLeft);
                float penY = std::min(overlapBottom, overlapTop);

                if (penX < penY) {
                    CollisionDirection.x = (overlapRight < overlapLeft) ? 1 : -1;
                } else {
                    CollisionDirection.y = (overlapBottom < overlapTop) ? 1 : -1;
                }
            } else {
                // --- Área de detección ---
                Thing* CollResult = ArrayColls(COLL, true);
                if (CollResult != nullptr) {

                    if (NextArea) {
                        if (AreaCollision != COLL) {
                            cout << "↪ CAMBIANDO a nueva área: " << COLL->MyName << endl;
                        }
                        AreaCollision = COLL;
                        if (!EnteredArea) {
                            EnteredArea = true;
                            cout << "✅ ENTRÓ al área: " << COLL->MyName << endl;
                        }
                    } else {
                        if (AreaArray.size() >= 1) {
                            if(AreaArray[0] == CollResult){

                                AreaCollision = COLL;
                                EnteredArea = true;
                                cout << "✅ ENTRÓ a su primera área: " << COLL->MyName << endl;
                            }
                        }
                    }
                }
            }
        } else if (isArea) {
            if (AreaCollision == COLL) {
                Thing* result = ArrayColls(COLL, false);

                if (NextArea) {
                    if (AreaCollision == COLL) {
                        cout << "❌ SALIÓ del área: " << COLL->MyName << endl;
                        AreaCollision = result;
                        if (AreaCollision != nullptr) {
                            cout << "🔄 NUEVA área activa: " << AreaCollision->MyName << endl;
                        } else {
                            EnteredArea = false;
                            cout << "🛑 NO queda ninguna área activa.\n";
                        }
                    }
                } else {
                    if (AreaCollision == COLL) {
                        cout << "❌ SALIÓ de su área persistente: " << COLL->MyName << endl;
                        AreaCollision = result;
                        if (AreaCollision != nullptr) {
                            cout << "🔄 CAMBIO a otra área válida: " << AreaCollision->MyName << endl;
                        } else {
                            EnteredArea = false;
                            cout << "🛑 NO queda ninguna área persistente activa.\n";
                        }
                    }
                }
            }
        }
    }

    return CollisionDirection;
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



void Thing::BackHandsOfTime(){
    x = lastX;
    y = lastY;
}

Thing* Thing::ArrayColls(Thing* AreaEntered, bool AddArea) {
    if (AddArea) {
        // Añadir si no existe
        for (Thing* COLL : AreaArray) {
            if (COLL == AreaEntered) {
                return nullptr;
            }
        }
        AreaArray.push_back(AreaEntered);
        return AreaEntered;

    } else {
        // Remover el área y devolver la siguiente válida
        for (size_t i = 0; i < AreaArray.size(); ++i) {
            if (AreaArray[i] == AreaEntered) {
                AreaArray.erase(AreaArray.begin() + i);

                // Buscar siguiente válida (de derecha a izquierda)
                for (int j = static_cast<int>(AreaArray.size()) - 1; j >= 0; --j) {
                    Thing* maybe = AreaArray[j];
                    float ml = maybe->left_x;
                    float mr = maybe->right_x;
                    float mt = maybe->up_y;
                    float mb = maybe->button_y;

                    bool insideX = (left_x < mr && right_x > ml);
                    bool insideY = (up_y < mb && button_y > mt);

                    if (insideX && insideY) {
                        return maybe;
                    }
                }

                return nullptr;
            }
        }
    }

    return nullptr;
}
