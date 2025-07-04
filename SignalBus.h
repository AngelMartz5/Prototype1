#include "raylib.h"
#include "Thing.h"
#include <iostream>

#ifndef SIGNALBUS
#define SIGNALBUS

class SignalBus{
public:
    void AddCollision(Thing* NewThing);
    void EliminateCollision(Thing* EliminateThing);
    int ExistsObj(Thing* EliminateThing);
    int FreeSpace();
    Thing* CollisionArray[499]{};
protected:

};


#endif