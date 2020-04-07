//#include "Communication.h"
//#include "Timer.h"
#include <stdio.h>
//#include "list.h"
#include "ucomlib.h"

int handler(const int event,const int msgId)
{

}

int main()
{
	CommuInit();
	CommSetEventHandler(handler);
	printf("hello");
}
