#include "MsgMmu.h"



static int MsgMmuSetEvHandle(EVENT_HANDLER ev)
{
	g_msg_mmu.ev_handler = ev;
}


static int SaveMsg(int msgId,const char *msgData,unsigned int dataLen)
{

}


static int GetMsg(int* pMsgId,char *msgData,unsigned int* pDataLen)
{

}

msg_mmu_t g_msg_mmu = {
	.set_ev_handler = MsgMmuSetEvHandle,
	.save_msg = SaveMsg,
	.get_msg = GetMsg

};


