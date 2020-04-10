#include "MsgBuff.h"

#ifndef NULL
#define NULL 0
#endif

char msg_buff[MSG_BUF_LEN][BLOCK_SIZE];
msg_ctrl_unit_t msg_ctrl_units[MAX_ASYNC_MSG_NUM];
char block_status[MSG_BUF_LEN];

/////////////////////////////////////// local //////////////////////////////////////////

static inline int msg_check(int msg_id,unsigned int dataLen)
{
	int i;
	
	if(dataLen > MAX_ASYNC_MSG_LEN || dataLen == 0) {
		return ERR_DATA_EXCESSIVE;
	}

	for(i = 0;i < MAX_ASYNC_MSG_NUM;i ++) {
		if ( msg_ctrl_units[i].msg_id == msg_id) {
			return ERR_ID_EXIST;
		}
	}
	
	return 0;
}

static inline msg_ctrl_unit_t* get_free_msg_unit(void) 
{
	int i;

	for(i = 0;i < MAX_ASYNC_MSG_NUM;i ++) {
		if(msg_ctrl_units[i].msg_id <= 0)
			return &msg_ctrl_units[i];
	}
	return NULL;
}


static inline msg_ctrl_unit_t* get_msg_unit(int id) 
{
	int i;

	for(i = 0;i < MAX_ASYNC_MSG_NUM;i ++) {
		if(msg_ctrl_units[i].msg_id == id)
			return &msg_ctrl_units[i];
	}
	return NULL;
}



/////////////////////// return block number //////////////////
static inline int get_block()
{
	int i;
	
	for(i = 0;i < MSG_BUF_LEN;i ++) {
		if(block_status[i] == 0) {
			block_status[i] = 1;
			return i;
		}
	}

	return ERR_MSG_BUF_FULL;
}

static inline void free_block(int bid)
{
	if (bid >= MSG_BUF_LEN)
		return;
	block_status[bid] = 0;
}

static inline int free_block_num()
{
	
}


////////////////////////////////////////// global /////////////////////////////////////
int msg_buff_init()
{
	int i;

	if(MSG_BUF_LEN > 255){
		return ERR_MSG_TOO_LONG;
	}

	for (i = 0;i < MSG_BUF_LEN;i ++) {
		block_status[i] = 0;
	}

	for(i = 0;i < MAX_ASYNC_MSG_NUM;i ++) {
		msg_ctrl_units[i].msg_id = 0;
	}

	return 0;
}

int msg_buff_save(const int msgId,const char *msgData,unsigned int dataLen)
{
	int count,block_num,i,j,k;
	int ret = msg_check(msgId,dataLen);
	if (ret != 0) {
		return ret;
	}
	
	count = (dataLen % BLOCK_SIZE)?dataLen/BLOCK_SIZE + 1:dataLen/BLOCK_SIZE;

	if(count > MAX_BLOCKNUM_PERMSG) {
		DEBUG("count:%d", count);
		return ERR_MSG_TOO_LONG;
	}

	ENTER_CRITICAL();

	msg_ctrl_unit_t* mu = get_free_msg_unit();
	if(mu == NULL) {
		EXIT_CRITICAL();
		return ERR_TARGET_NULL;
	}
	
	for(i = 0;i < count;i ++) {
		mu->block_rationing[i] = get_block();
		if(mu->block_rationing[i] < 0) {
			for(k = 0;k < i;k ++){
				free_block(mu->block_rationing[k]);
			}
			EXIT_CRITICAL();
			return mu->block_rationing[i];
		}
	}

	//////////////// preemptive blocks /////////////////////

	mu->msg_id = msgId;
	mu->timer_count = 0;
	mu->data_len = dataLen;
	
	EXIT_CRITICAL();

	///////////////// data capy ////////////////////////////
	for( i = 0;i < count;i ++) {
		for(j = 0;j < BLOCK_SIZE;j ++) {
			if(i * BLOCK_SIZE + j >= dataLen)
				break;
			msg_buff[i][j] = msgData[i * BLOCK_SIZE + j];
		}
	}

	return 0;
}

int msg_buf_get(const int msgId,char *msgData,unsigned int* pDataLen)
{
	int i,j,count;
	
	msg_ctrl_unit_t* mu = get_msg_unit(msgId);
	if (mu == NULL) {
		return ERR_MSG_NOT_EXIST;
	}

	count = (mu->data_len % BLOCK_SIZE)?mu->data_len/BLOCK_SIZE + 1:mu->data_len/BLOCK_SIZE;

	for(i = 0;i < count;i ++) {
		for(j = 0;j < BLOCK_SIZE;j ++) {
			msgData[i * BLOCK_SIZE + j] = msg_buff[i][j];
			if(i * BLOCK_SIZE + j >= mu->data_len)
				break;
		}
	}

	*pDataLen = mu->data_len;

	ENTER_CRITICAL();
	for(i = 0;i < count;i ++) {
		block_status[mu->block_rationing[i]] = 0;
	}

	mu->msg_id = 0;

	EXIT_CRITICAL();
	
	return 0;
}

void mm_timing_processing(EVENT_HANDLER ev)
{
	unsigned int i;

	for(i = 0;i < MAX_ASYNC_MSG_NUM ;i ++) {
		if(msg_ctrl_units[i].msg_id != 0){
			msg_ctrl_units[i].timer_count ++;
			if(msg_ctrl_units[i].timer_count >= MAX_TIMEER_COUNT){
				msg_ctrl_units[i].timer_count = 0;
				ev(EV_TIMEOUT,msg_ctrl_units[i].msg_id);
			}
			
		}
	}

}


