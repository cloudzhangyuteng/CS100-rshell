#ifndef MY_IN_H
#define MY_IN_H

#include "Connector.h"

class My_In : public Connector
{
public:
   My_In();
   My_In(Base*, Base*);
   ~My_In();
   
   void execute(int, int);
};

#endif
