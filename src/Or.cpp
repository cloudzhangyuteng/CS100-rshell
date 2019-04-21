#include "header/Or.h"

//Or::Or() {}

Or::Or(Base* l, Base* r) : Connector(l, r) {}

void Or::execute(int fd_in, int fd_out)
{
    this->exec_flag = true;
    this->result = "true";  //unit_test
    left->execute(fd_in, fd_out);
    if (!left->exec_flag) {
        right->execute(fd_in, fd_out);
        this->exec_flag = right->exec_flag;
        if(!this->exec_flag) {this->result = "false";}  //unit_test
    }
}

Or::~Or() {}
