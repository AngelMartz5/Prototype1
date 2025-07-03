#include "raylib.h"
#include "SignalBus.h"
#include "Thing.h"
#include <iostream>

void SignalBus::AddCollision(Thing &NewThing){
    int size  = (*CollisionArray)->size;
    size += 1;
    CollisionArray[size]; 
    CollisionArray[size] = &NewThing;
    
}

int SignalBus::QuantityCollision(){
    int howMuch = (*CollisionArray)->size;
    return howMuch;
}