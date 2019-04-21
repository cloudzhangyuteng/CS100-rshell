#ifndef AND_H
#define AND_H

#include "Connector.h"


class And : public Connector
{
   public:
      And();
      And(Base*, Base*);
      ~And();
      
      void execute(int, int);

   private:
};

#endif // AND_H
