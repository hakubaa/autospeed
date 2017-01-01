#include "Entity/EntsBox.h"


void EntsBox::addEnt(Entity* ent) {
    bool present = std::find(m_ents.begin(), m_ents.end(), ent) != m_ents.end();
    if (!present)
        m_ents.push_back(ent);
}

void EntsBox::delEnt(Entity* ent) {
    std::vector<Entity*>::iterator it = std::find(m_ents.begin(), m_ents.end(), ent);
    if (it != m_ents.end())
        m_ents.erase(it);
}

void EntsBox::clear() {
    m_ents.clear();
}

std::vector<Entity*>::iterator EntsBox::getIterator() {
    return m_ents.begin();
}