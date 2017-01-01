#ifndef NORENDERER_H
#define NORENDERER_H

#include "Renderer/Renderer.h"

class NoRenderer : public Renderer {

public:
    void render(EntsBox* ents) { return REvent(REvent::None); }
    
};

#endif