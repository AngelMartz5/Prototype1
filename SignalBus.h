#include "raylib.h"
#include "Thing.h"

#ifndef SIGNALBUS
#define SIGNALBUS

class SignalBus{
public:
    SignalBus();
    void AddCollision(Thing &NewThing);
    void EliminateCollision(Thing EliminateThing);
    int QuantityCollision();
    Thing* CollisionArray[0];
    protected:
    

};


#endif