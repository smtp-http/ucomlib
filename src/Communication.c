#include "Communication.h"
#include "MsgMmu.h"

int CommuInit(void)
{

}

int CommSetEventHandler(EVENT_HANDLER ev)
{
	g_msg_mmu.set_ev_handler(ev);
}



