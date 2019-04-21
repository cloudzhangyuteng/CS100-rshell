#include "header/My_Out_Append.h"

My_Out_Append::My_Out_Append(Base* l, Base* r) : Connector(l, r) { }
My_Out_Append::~My_Out_Append() { }

void My_Out_Append::execute(int fd_in, int fd_out)
{
   std::string output_file = right->get_command_line_first_string();
   fd_out = open(output_file.c_str(), O_CREAT | O_APPEND | O_WRONLY, 0644);

   left->execute(fd_in, fd_out);
   this->exec_flag = left->exec_flag;
}
