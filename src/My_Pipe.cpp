#include "header/My_Pipe.h"

//My_Pipe::My_Pipe() { }
My_Pipe::My_Pipe(Base* l, Base* r) : Connector(l, r) { }

void My_Pipe::execute(int fd_in, int fd_out)
{
   this->exec_flag = true;
   
   int pipe_fd[2];

   pipe(pipe_fd);

   left->execute(fd_in, pipe_fd[1]);
   if (!left->exec_flag) {
      this->exec_flag = false;
      return;
   }
   close(pipe_fd[1]);
   
   right->execute(pipe_fd[0], fd_out);
   if (!right->exec_flag) {
      this->exec_flag = false;
      return;
   }
   close(pipe_fd[0]);
}


My_Pipe::~My_Pipe() { }
