#ifndef ENTSBOX_H
#define ENTSBOX_H


#include "Entity/Entity.h"

#include <vector>
#include <algorithm>

class EntsBox {

    std::vector<Entity*> m_ents;
public:

    void addEnt(Entity* ent);
    void delEnt(Entity* ent);
    void clear();

    std::vector<Entity*>::iterator getIterator();
};

#endif