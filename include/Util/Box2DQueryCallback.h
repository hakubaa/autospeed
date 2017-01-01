#ifndef BOX2DQUERYCALLBACK_H
#define BOX2DQUERYCALLBACK_H

#include <Box2D/Box2D.h>

class Box2DQueryCallback : public b2QueryCallback {
public:
  std::vector<b2Body*> foundBodies;
  
  bool ReportFixture(b2Fixture* fixture) {
      foundBodies.push_back( fixture->GetBody() ); 
      return true;
  }
};

#endif