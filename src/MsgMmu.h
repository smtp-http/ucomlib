#ifndef __MSG_MMU_H__
#define __MSG_MMU_H__

#include "ucomlib.h"

typedef struct{
	int (*save_msg)(int msgId,const char *msgData,unsigned int dataLen);
	int (*get_msg)(int* pMsgId,char *msgData,unsigned int* pDataLen);
	int (*set_ev_handler)(EVENT_HANDLER ev);
	EVENT_HANDLER ev_handler;
}msg_mmu_t;


extern msg_mmu_t g_msg_mmu;

#endif

