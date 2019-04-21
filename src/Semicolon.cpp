#include "header/Semicolon.h"

Semicolon::Semicolon(Base* l, Base* r) : Connector(l, r) {}

void Semicolon::execute(int fd_in, int fd_out)
{
   left->execute(fd_in, fd_out);
   right->execute(fd_in, fd_out);
   this->exec_flag = right->exec_flag;
   this->result = (this->exec_flag) ? "true" : "false";
}

Semicolon::~Semicolon() {}
