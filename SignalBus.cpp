#include "raylib.h"
#include "SignalBus.h"
#include "Thing.h"
#include <iostream>

void SignalBus::AddCollision(Thing* NewThing){
    cout <<"Espacio vacio numero: " << FreeSpace() << endl;
    int Result = ExistsObj(NewThing);
    //cout << "Entro: " << WhoEntere << " And Its result is: " << Result<< endl;
    if (Result == -1){
        int vacio = FreeSpace();
        CollisionArray[vacio] = NewThing;
    }
    
    
}

void SignalBus::EliminateCollision(Thing* EliminateThing){
    return;
}

int SignalBus::FreeSpace(){
    int where = 0;
    for (auto COll : CollisionArray)
    {
        if(COll == nullptr){
            break;
        }
        ++where;
    }
    return where;
    
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