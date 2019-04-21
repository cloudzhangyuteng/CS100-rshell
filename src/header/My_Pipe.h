#ifndef MY_PIPE_H
#define MY_PIPE_H

#include "Connector.h"

class My_Pipe : public Connector
{
public:
   My_Pipe();
   My_Pipe(Base*, Base*);
   ~My_Pipe();
   
   void execute(int, int);
};

#endif
