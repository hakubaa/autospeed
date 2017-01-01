#include "Entity/Listener/EntsColListener.h"


void EntsColListener::BeginContact(b2Contact* contact) {
    
    b2Body* aBody = contact->GetFixtureA()->GetBody();
    b2Body* bBody = contact->GetFixtureB()->GetBody();

    Entity* aEnt = (Entity*)aBody->GetUserData();
    Entity* bEnt = (Entity*)bBody->GetUserData();

    if (!aEnt || !bEnt) 
        return;

    aEnt->handleCollision(bEnt);
    bEnt->handleCollision(aEnt);

}

void EntsColListener::EndContact(b2Contact* contact) {

}