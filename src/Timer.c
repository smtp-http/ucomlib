#include "Timer.h"
#include "MsgMmu.h"


int OnTimer()
{
	g_msg_mmu.timing_processing();
}



