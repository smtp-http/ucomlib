#ifndef __MSG_MMU_H__
#define __MSG_MMU_H__

#include "ucomlib.h"

typedef struct{
	int (*save_msg)(const int msgId,const char *msgData,unsigned int dataLen);
	int (*get_msg)(const int pMsgId,char *msgData,unsigned int* pDataLen);
	int (*set_ev_handler)(EVENT_HANDLER ev);
	int (*init)(void);
	EVENT_HANDLER ev_handler;
}msg_mmu_t;


extern msg_mmu_t g_msg_mmu;

#endif

