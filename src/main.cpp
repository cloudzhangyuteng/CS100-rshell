#include "header/Shell.h"
#include "header/Base.h"

#include <iostream>

using namespace std;

int main()
{
    while (true) { 
    
        cout << "$ ";
        
        Shell my_shell;
        my_shell.read_input();
        my_shell.parse();
        my_shell.run();
    }

	return 0;
}
