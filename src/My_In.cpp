#include "header/My_In.h"

My_In::My_In(Base* l, Base* r) : Connector(l, r) { }
My_In::~My_In() { }

void My_In::execute(int fd_in, int fd_out)
{
   std::string input_file = right->get_command_line_first_string();
   fd_in = open(input_file.c_str(), O_RDONLY);
   
   if (fd_in < 0) {
      perror("can't open input_file");
      this->exec_flag = false;
      return;
   }
   
   left->execute(fd_in, fd_out);
   this->exec_flag = left->exec_flag;
   
}
