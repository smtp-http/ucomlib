#include "Timer.h"
#include "MsgMmu.h"


int OnTimer()
{
	g_msg_mmu.ev_handler(EV_TIMEOUT,10);
}



