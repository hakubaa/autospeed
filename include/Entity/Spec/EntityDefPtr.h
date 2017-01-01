#ifndef ENTITYDEFPTR_H
#define ENTITYDEFPTR_H

#include "CarSim/Entity/Def/EntityDef.h"

class EntityDefPtr {
    EntityDef* m_ent;
public:
    EntityDefPtr(EntityDef* ent) : m_ent(ent) { }

    ~EntityDefPtr() {
        if (m_ent != nullptr) 
            delete m_ent;
    }

    EntityDef* operator->() const {
        return m_ent;
    }
};

#endif