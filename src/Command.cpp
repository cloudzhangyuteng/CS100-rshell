#include "header/Command.h"
#include <vector>

Command::Command() {}

Command::Command(std::vector<std::string> vec_com)
{
   command_line = vec_com;
}

Command::~Command() {}

void Command::execute(int fd_in, int fd_out)
{
   this->exec_flag = true;
    
      // *** test_path_file ***
      if (command_line[0] == "test") {
      struct stat st;
      std::string path_to(command_line.back());
        
      if (command_line[1] == "-d") {
         if (stat(path_to.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            std::cout << "(True)\n";
         }
         else {
            std::cout << "(False)\n";
            this->exec_flag = false;
         }
      }
      else if (command_line[1] == "-f") {
         if (stat(path_to.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
            std::cout << "(True)\n";
         }
         else {
            std::cout << "(False)\n";
            this->exec_flag = false;
         }
      }
      else {
         if (stat(path_to.c_str(), &st) == 0) {
            std::cout << "(True)\n";
         }
         else {
            std::cout << "(False)\n";
            this->exec_flag = false;
         }
      }
      return;
   }
    // *** end test_path_file ***
   
    
    std::vector<char*> vec_tempo{};
   for (std::string& s  : command_line) {
      vec_tempo.push_back(&s.front());
   }
   vec_tempo.push_back('\0');
   exec_command_line = vec_tempo.data();

      /// Starts execvp part
   if (strcmp(exec_command_line[0], "exit") == 0) {
      exit(0);
   }

   pid_t  pid;
   int    status;
   
   if ((pid = fork()) < 0) {
      perror("fork_error");
      exit(1);
   }
   else if (pid == 0) {
      if (fd_in != 0) {
         dup2(fd_in, 0);
         close(fd_in);
      }
      if (fd_out != 1) {
         dup2(fd_out, 1);
         close(fd_out);
      }
      
      execvp(exec_command_line[0], exec_command_line);
      exit(1);
   }
   else {
      waitpid(pid, &status, WUNTRACED);
      if (status > 0) {
         this->exec_flag = false;
      }
      else if (WEXITSTATUS(status) == 0) {
         this->exec_flag = true;
      }
      else if (WEXITSTATUS(status) == 1) {
         this->exec_flag = false;
      }
   }
}
