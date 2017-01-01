#ifndef TRACKEDITOR_H
#define TRACKEDITOR_H

#include "CarSim/EditorMode/BaseMode.h"
#include "CarSim/EditorMode/NodeMode.h"
#include "CarSim/EditorMode/LinkMode.h"
#include "CarSim/EditorMode/DelMode.h"
#include "CarSim/EditorMode/LazyMode.h"
#include "CarSim/EditorMode/CheckpointMode.h"
#include "CarSim/EditorMode/StartPosMode.h"
#include "CarSim/Entity/Entity.h"
#include "CarSim/Entity/Node.h"
#include "CarSim/Entity/Checkpoint.h"

#include "CarSim/GUI/FileChooser.h"
#include "SFMLDebugDraw.h"
#include "tinyxml2.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include <vector>
#include <iostream>
#include <string>


class TrackEditor {

    friend class NodeMode;
    friend class LinkMode;
    friend class DelMode;
    friend class LazyMode;
    friend class CheckpointMode;
    friend class StartPosMode;

    std::vector<Entity*> ents;

    Node* m_activeNode;

    sf::RenderWindow* m_window;
    b2World* m_world;

    BaseMode* m_mode;

public:

    TrackEditor(sf::RenderWindow* window, b2World* world);
    ~TrackEditor();

    void handleEvent(const sf::Event& event);

    void addEntity(Entity* ent);
    void delEntity(Entity* ent);

    tinyxml2::XMLDocument* createXML();
    tinyxml2::XMLError loadXML(tinyxml2::XMLDocument& xmlDoc);

    std::string getInfo() const;
    std::string getStatus() const;

    void update(sf::Time);

};

#endif