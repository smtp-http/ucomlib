#include "Communication.h"
#include "MsgMmu.h"

int CommuInit(void)
{
	g_msg_mmu.init();
}

int CommSetEventHandler(EVENT_HANDLER ev)
{
	g_msg_mmu.set_ev_handler(ev);
}



