#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"


class Semicolon : public Connector
{
   public:
      Semicolon(Base*, Base*);
      ~Semicolon();
      
      void execute(int, int);

   private:

};

#endif // SEMICOLON_H

