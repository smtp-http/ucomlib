//#include "Communication.h"
//#include "Timer.h"
#include <stdio.h>
//#include "list.h"
#include "ucomlib.h"


int handler(const int event,const int msgId)
{
	switch (event) {
		case EV_TIMEOUT:
			DEBUG("ev_timeout");
			break;
		default:
			DEBUG("undefine event");
			break;	
	}
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





int main()
{
	CommuInit();
	CommSetEventHandler(handler);
	printf("hello");
}
