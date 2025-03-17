#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject {
protected:
    std::vector<Observer*> observers;

public:
    virtual void subscribe(Observer* o) = 0;
    virtual void notifyObservers() = 0;
};

#endif
