#include "header/Command_mock.h"

Command_mock::Command_mock() { }

Command_mock::Command_mock(bool set)
{
    exec_flag = false;
    this->set = set;
}

Command_mock::~Command_mock() { }

void Command_mock::execute(int fd_in, int fd_out)
{
    exec_flag = set;
}
