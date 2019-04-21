#ifndef MY_OUT_H
#define MY_OUT_H

#include "Connector.h"

class My_Out : public Connector
{
public:
   My_Out();
   My_Out(Base*, Base*);
   ~My_Out();
   
   void execute(int, int);
};

#endif
