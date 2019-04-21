#ifndef COMMAND_MOCK_H
#define COMMAND_MOCK_H

#include "Base.h"


class Command_mock : public Base
{
    public:
    Command_mock();

    Command_mock(bool);

    virtual ~Command_mock();
    void execute(int, int);

    protected:

    private:
    bool set;
};

#endif
