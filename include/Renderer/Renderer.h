#ifndef RENDERER_H
#define RENDERER_H

#include "Entity/EntsBox.h"
#include "SimMode/SimMode.h"

class Renderer {
        
public:
    virtual ~Renderer() { }
    virtual void render(EntsBox* ents, SimMode* sim) = 0;
};

#endif 