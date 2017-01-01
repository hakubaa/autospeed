#ifndef DRIVER_H
#define DRIVER_H

class Driver {
   
public:
    virtual ~Driver() { }

    virtual int update() = 0;
    virtual bool isActive() = 0;
    virtual void setActive(bool) = 0;

    
    virtual float getFitness() = 0;
    virtual void updateFitness() = 0;
};

#endif