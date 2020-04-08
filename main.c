//#include "Communication.h"
//#include "Timer.h"
#include <stdio.h>
//#include "list.h"
#include "ucomlib.h"


int handler(const int event,const int msgId)
{

}

void ENTER_CRITICAL()
{

}


void EXIT_CRITICAL()
{

}

int CRITICAL_INIT()
{

}

int CRITICAL_DEINIT()
{

}

int OnTimeOut()
{

}




int main()
{
	CommuInit();
	CommSetEventHandler(handler);
	printf("hello");
}
