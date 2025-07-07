#include "raylib.h"
#include "Thing.h"
#include <iostream>
#include <vector>

#ifndef SIGNALBUS
#define SIGNALBUS

class SignalBus{
public:
    void AddCollision(Thing* NewThing);
    void EliminateCollision(Thing* EliminateThing);
    int ExistsObj(Thing* EliminateThing);
    vector<Thing*>CollisionArray;
protected:

};


#endif