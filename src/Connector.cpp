
#include "header/Connector.h"

Connector::Connector(Base* l, Base* r)
{
    left = l;
    right = r;
}

Connector::~Connector() { }

void Connector::execute(int fd_in, int fd_out) {}




