#ifndef SHELL_H
#define SHELL_H

#include "Base.h"
#include "Command.h"
#include "Semicolon.h"
#include "And.h"
#include "Or.h"
#include "My_Pipe.h"
#include "My_In.h"
#include "My_Out.h"
#include "My_Out_Append.h"

#include <iostream>
#include <string>
#include <vector>

class Base;

class Shell
{
   public:
   Shell();
   virtual ~Shell();

   void read_input();
   void parse();
   void run();
   void input_preparation();
   Base* create_tree();
   Base* create_command();

   // test functions
   void set_input(std::string);
   std::string get_my_vec(int);
   
   private:
   std::string user_input;
   int index;
   
   std::vector<std::string> my_vec;
   std::string tempo;
};

#endif // SHELL_H
