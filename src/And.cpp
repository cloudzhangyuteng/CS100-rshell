#include "header/And.h"

// And Class

// And::And() {}

And::And(Base* l, Base* r) : Connector(l, r) {}
void And::execute(int fd_in, int fd_out)
{
    this->exec_flag = false;
    this->result = "false";  //unit_test
    left->execute(fd_in, fd_out);
    if (left->exec_flag) {
        right->execute(fd_in, fd_out);
        this->exec_flag = right->exec_flag;
        if (this->exec_flag) {this->result = "true";}  //unit_test
    }
}

And::~And() {}
