#include "raylib.h"
#include <string>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef THING
#define THING

enum Shapes{
    SP_CIRCLE,
    SP_RECTANGLE
};

class Thing {
public:
    Thing(Shapes WhichShapeChose, Color WhichColorChose, Vector2 PositionSpawn, string OWNNAME, bool Coll);
    Vector2 saberLocalizacion();
    void Movement(float xMov, float yMov);
    Vector2 CollisionBorder(float right__x, float left__x, float button__y, float up__y);
    void DelltaProcess(vector<Thing*> ArrayOthers);
    Vector2 Collisions( float right__x, float left__x, float button__y, float up__y);
    bool CanYouMoveThen();
    void BackHandsOfTime();
    float x = 0.f;
    float y = 0.f;
    int size{50};
    //axe edges
    float left_x{x - static_cast<float>(size)};
    float right_x{x + static_cast<float>(size)};
    float up_y{y - static_cast<float>(size)};
    float button_y{y + static_cast<float>(size)};
    bool IsColliding = false;
    string MyName;
    bool HasCollsion = true;
private:

   

protected:
    Vector2 NextVector{0.f,0.f};
    Vector2 CollisionDirection{0.f,0.f};
    Vector2 CollisionDirectionHelper{0.f,0.f};
    float lastX = 0.f;
    float lastY = 0.f;
    vector<Thing*>CollisionsArray;
    Shapes MyShape;
    Color MyColor;
    int FaceX = 1;
    Vector2 MovementVector {0.f,0.f};
    float Velocity = 10.f;
    Thing* CopyColls[499];
};


#endif