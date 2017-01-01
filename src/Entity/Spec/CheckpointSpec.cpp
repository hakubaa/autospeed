#include "Entity/Spec/CheckpointSpec.h"

CheckpointSpec::CheckpointSpec() : 
    isSensor(false), 
    sNode(b2Vec2(0.0f, 0.0f)),
    eNode(b2Vec2(0.0f, 0.0f)),
    type(0),
    orderNo(0)
{ 
}

tinyxml2::XMLElement* CheckpointSpec::createXML(tinyxml2::XMLDocument* xmlDoc) const {
    
    tinyxml2::XMLElement* pMainElement = xmlDoc->NewElement("Entity");
    pMainElement->SetAttribute("type", "ENT_CHECKPOINT");

    tinyxml2::XMLElement* pElement;
    tinyxml2::XMLElement* pos_x, *pos_y;

    pElement = xmlDoc->NewElement("SNode");
    pos_x = xmlDoc->NewElement("x");
    pos_x->SetText(sNode.x);
    pElement->InsertEndChild(pos_x);
    pos_y = xmlDoc->NewElement("y");
    pos_y->SetText(sNode.y);
    pElement->InsertEndChild(pos_y);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("ENode");
    pos_x = xmlDoc->NewElement("x");
    pos_x->SetText(eNode.x);
    pElement->InsertEndChild(pos_x);
    pos_y = xmlDoc->NewElement("y");
    pos_y->SetText(eNode.y);
    pElement->InsertEndChild(pos_y);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("IsSensor");
    pElement->SetText(isSensor);
    pMainElement->InsertEndChild(pElement);

    pElement = xmlDoc->NewElement("Type");
    pElement->SetText(type);
    pMainElement->InsertEndChild(pElement);
   
    pElement = xmlDoc->NewElement("OrderNo");
    pElement->SetText(orderNo);
    pMainElement->InsertEndChild(pElement);

    return pMainElement;

}

void CheckpointSpec::readXML(tinyxml2::XMLElement* node) { 
    
    setlocale(LC_ALL,"C");

    tinyxml2::XMLElement* pElement = node->FirstChildElement("SNode");

    tinyxml2::XMLElement* pos;
    float x, y;

    pos = pElement->FirstChildElement("x");

    pos->QueryFloatText(&x);
    pos = pElement->FirstChildElement("y");
    pos->QueryFloatText(&y);

    sNode.x = x;
    sNode.y = y;

    pElement = node->FirstChildElement("ENode");
    pos = pElement->FirstChildElement("x");
    pos->QueryFloatText(&x);
    pos = pElement->FirstChildElement("y");
    pos->QueryFloatText(&y);

    eNode.x = x;
    eNode.y = y;

    pElement = node->FirstChildElement("IsSensor");
    pElement->QueryBoolText(&isSensor);

    pElement = node->FirstChildElement("Type");
    pElement->QueryIntText(&type);

    pElement = node->FirstChildElement("OrderNo");
    pElement->QueryIntText(&orderNo);

}