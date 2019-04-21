#ifndef OR_H
#define OR_H

#include "Connector.h"


class Or : public Connector
{
   public:
      Or();
      Or(Base*, Base*);
      ~Or();
      void execute(int, int);

   private:
};

#endif // OR_H

