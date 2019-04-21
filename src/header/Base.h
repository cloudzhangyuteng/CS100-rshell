#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>

#include <string>
#include <string.h>
#include <vector>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>


class Base
{
   public:
   Base() { };
   virtual ~Base() { };

   virtual void execute(int, int) = 0;
    
   std::string get_command_line_first_string()
   {
       return command_line[0];
   }
   
   std::string read_file(std::string file_name)
   {
      std::ifstream my_file(file_name);
      std::string line;
      std::getline(my_file, line);
      my_file.close();
      return line;
   }   

   std::string result;
   bool exec_flag;
    
    // for dup2()

   protected:
   std::vector<std::string> command_line;
   Base* left;
   Base* right;

   private:
};

#endif // BASE_H
