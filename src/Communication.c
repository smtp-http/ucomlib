#include "Communication.h"
#include "MsgMmu.h"

int CommuInit(void)
{
	return g_msg_mmu.init();
}

int CommSetEventHandler(EVENT_HANDLER ev)
{
	return g_msg_mmu.set_ev_handler(ev);
}

int CommSaveMsg(const int msgId,const char *msgData,unsigned int dataLen)
{
	return g_msg_mmu.save_msg(msgId,msgData,dataLen);
}

int CommGetMsg(const int msgId,char *msgData,unsigned int* pDataLen)
{
	return g_msg_mmu.get_msg(msgId,msgData,pDataLen);
}


