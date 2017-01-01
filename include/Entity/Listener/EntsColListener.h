#ifndef ENTSCOLLISTENER_H
#define ENTSCOLLISTENER_H

#include "Entity/Entity.h"

#include <Box2D/Box2D.h>

class EntsColListener : public b2ContactListener {

public:    
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif