#ifndef CHECKPOINTMODE_H
#define CHECKPOINTMODE_H

#include "CarSim/EditorMode/BaseMode.h"
#include "CarSim/Entity/Checkpoint.h"
#include "CarSim/Box2DQueryCallback.h"
#include "CarSim/Entity/Node.h"
#include "CarSim/TrackEditor.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>

class CheckpointMode : public BaseMode {

    TrackEditor* m_editor;
    static Checkpoint* m_lastCheckpoint;
    static int m_type;
    static int m_orderNo;

    Node* sNode;
    Node* eNode;

public:
    CheckpointMode(TrackEditor* editor);

    void handleEvent(const sf::Event& event);
    std::string getInfo() const;
    std::string getStatus() const;
    void update(sf::Time timeStep);
};

#endif