#include "raylib.h"
#include "SignalBus.h"
#include "Thing.h"
#include <iostream>
#include <vector>
void SignalBus::AddCollision(Thing* NewThing){
    int Result = ExistsObj(NewThing);
    //cout << "Entro: " << WhoEntere << " And Its result is: " << Result<< endl;
    if (Result == -1){
        CollisionArray.push_back(NewThing);
    }
    
    
}

void SignalBus::EliminateCollision(Thing* EliminateThing){
    return;
}

int SignalBus::ExistsObj(Thing* EliminateThing){
    int where = 0;  
    for (auto COll : CollisionArray)
    {
        if(COll != nullptr){
            
            if(EliminateThing == COll){
                cout << "IGUALES DETECTADOS" << endl;
                return where;
            }
        }
        ++where;
    }
    return -1;
}