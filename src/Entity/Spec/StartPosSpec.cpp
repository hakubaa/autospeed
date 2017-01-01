#include "Entity/Spec/StartPosSpec.h"


tinyxml2::XMLElement* StartPosSpec::createXML(tinyxml2::XMLDocument* xmlDoc) const 
{ 
    tinyxml2::XMLElement* pMainElement = xmlDoc->NewElement("Entity");
    pMainElement->SetAttribute("type", "ENT_STARTPOS");

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

    pElement = xmlDoc->NewElement("angle");
    pElement->SetText(angle);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("width");
    pElement->SetText(width);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("height");
    pElement->SetText(height);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("id");
    pElement->SetText(id);
    pMainElement->InsertEndChild(pElement);

    return pMainElement;
}

void StartPosSpec::readXML(tinyxml2::XMLElement* node) 
{ 
    float x, y;

    tinyxml2::XMLElement* pElement = node->FirstChildElement("pos");

    tinyxml2::XMLElement* ePos = pElement->FirstChildElement("x");

    setlocale(LC_ALL,"C");

    tinyxml2::XMLError eResult = ePos->QueryFloatText(&x);

    ePos = pElement->FirstChildElement("y");
    ePos->QueryFloatText(&y);

    pos.x = x;
    pos.y = y;

    pElement = node->FirstChildElement("angle");
    pElement->QueryFloatText(&angle);

    pElement = node->FirstChildElement("width");
    pElement->QueryFloatText(&width);

    pElement = node->FirstChildElement("height");
    pElement->QueryFloatText(&height);

    pElement = node->FirstChildElement("id");
    pElement->QueryIntText(&id);
}