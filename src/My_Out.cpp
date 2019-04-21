#include "header/My_Out.h"

My_Out::My_Out(Base* l, Base* r) : Connector(l, r) { }
My_Out::~My_Out() { }

void My_Out::execute(int fd_in, int fd_out)
{
   std::string output_file = right->get_command_line_first_string();
   fd_out = open(output_file.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
 
   left->execute(fd_in, fd_out);
   this->exec_flag = left->exec_flag;
}
