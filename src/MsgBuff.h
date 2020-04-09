#ifndef __MSG_BUF_H__
#define __MSG_BUF_H__

#include "ucomlib.h"
/////////////////////////////  define the message bufffer size ////////////////////////////

#define BLOCK_SIZE 10
#define MAX_ASYNC_MSG_LEN   20 
#define MAX_BLOCKNUM_PERMSG ((MAX_ASYNC_MSG_LEN % BLOCK_SIZE)?(MAX_ASYNC_MSG_LEN/BLOCK_SIZE) + 1:(MAX_ASYNC_MSG_LEN/BLOCK_SIZE))

#define MSG_BUF_LEN (MAX_ASYNC_MSG_NUM * MAX_BLOCKNUM_PERMSG)// * BLOCK_SIZE)

#ifdef _MSC_VER

	#pragma pack(push)
	#pragma pack(1)

	#define PACKED

#else

	#define PACKED __attribute((packed))__

#endif


struct msg_ctrl_unit{
	int msg_id;								// 0: idel msg ctrl unit      not 0: msg id
	char data_len;								// data length: 0~255
	char block_rationing[MAX_BLOCKNUM_PERMSG];  // the block number used
	unsigned char timer_count;							// for timeout task
} PACKED;

typedef struct msg_ctrl_unit msg_ctrl_unit_t;


#ifdef _MSC_VER

	#pragma pack(pop)

#endif


int msg_buff_init();
int msg_buff_save(const int msgId,const char *msgData,unsigned int dataLen);
int msg_buf_get(const int pMsgId,char *msgData,unsigned int* pDataLen);
void mm_timing_processing(EVENT_HANDLER ev);


#endif

