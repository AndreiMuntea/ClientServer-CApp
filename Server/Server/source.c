
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  


int main()
{

   _CrtDumpMemoryLeaks();
   return 0;
}