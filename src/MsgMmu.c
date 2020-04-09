#include "MsgMmu.h"
#include "MsgBuff.h"

//unsigned char msg_buf[MSG_BUF_LEN];


static int MsgMmuSetEvHandle(EVENT_HANDLER ev)
{
	g_msg_mmu.ev_handler = ev;
}


static int Init(void)
{
	int ret;
	ret = msg_buff_init();
	if(ret != 0) {
		DEBUG("msg buff init err,ret:%d",ret);
		return ret;
	}
}

static void msg_timing_processing()
{
	mm_timing_processing(g_msg_mmu.ev_handler);
}

msg_mmu_t g_msg_mmu = {
	.init = Init,
	.set_ev_handler = MsgMmuSetEvHandle,
	.save_msg = msg_buff_save,
	.get_msg = msg_buf_get,
	.timing_processing = msg_timing_processing
};


