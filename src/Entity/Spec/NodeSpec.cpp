#include "Entity/Spec/NodeSpec.h"


tinyxml2::XMLElement* NodeSpec::createXML(tinyxml2::XMLDocument* xmlDoc) const { 

    tinyxml2::XMLElement* pMainElement = xmlDoc->NewElement("Entity");
    pMainElement->SetAttribute("type", "ENT_NODE");

    tinyxml2::XMLElement* pElement;
    tinyxml2::XMLElement* pos_x, *pos_y;

    pElement = xmlDoc->NewElement("pos");
    pos_x = xmlDoc->NewElement("x");
    pos_x->SetText(pos.x);
    pElement->InsertEndChild(pos_x);

    pos_y = xmlDoc->NewElement("y");
    pos_y->SetText(pos.y);
    pElement->InsertEndChild(pos_y);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("radius");
    pElement->SetText(radius);
    pMainElement->InsertEndChild(pElement);

    return pMainElement;
}

void NodeSpec::readXML(tinyxml2::XMLElement* node) 
{ 

    setlocale(LC_ALL,"C");
    
    float x, y;

    tinyxml2::XMLElement* pElement = node->FirstChildElement("pos");

    tinyxml2::XMLElement* ePos = pElement->FirstChildElement("x");
    ePos->QueryFloatText(&x);
    ePos = pElement->FirstChildElement("y");
    ePos->QueryFloatText(&y);

    pos.x = x;
    pos.y = y;

    pElement = node->FirstChildElement("radius");
    pElement->QueryFloatText(&radius);
}
