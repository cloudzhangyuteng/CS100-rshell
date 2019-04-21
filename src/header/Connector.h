#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"


class Connector : public Base
{
    public:
    Connector(Base*, Base*);
    virtual ~Connector();

    void execute(int, int);

    protected:

    private:
};

#endif // CONNECTOR_H
