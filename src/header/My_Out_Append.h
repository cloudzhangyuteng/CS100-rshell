#ifndef MY_OUT_APPEND_H
#define MY_OUT_APPEND_H

#include "Connector.h"

class My_Out_Append : public Connector
{
public:
   My_Out_Append();
   My_Out_Append(Base*, Base*);
   ~My_Out_Append();
   
   void execute(int, int);
};

#endif
