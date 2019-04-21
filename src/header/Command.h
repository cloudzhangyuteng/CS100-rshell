#ifndef COMMAND_H
#define COMMAND_H

#include "Base.h"

class Command : public Base
{
public:
   Command();
   Command(std::vector<std::string>);
   virtual ~Command();
   void execute(int, int);

   protected:

   private:
   char** exec_command_line;

};

#endif // COMMAND_H
