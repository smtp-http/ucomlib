//#include "Communication.h"
//#include "Timer.h"
#include <stdio.h>
//#include "list.h"
#define __DEBUG__
#include "ucomlib.h"
#include <pthread.h>
#include <string.h>

pthread_mutex_t g_mutex;

int handler(const int event,const int msgId)
{
	switch (event) {
		case EV_TIMEOUT:
			DEBUG("ev_timeout");
			break;
		default:
			DEBUG("undefine event");
			break;	
	}
}

void ENTER_CRITICAL()
{
	pthread_mutex_lock(&g_mutex);
}


void EXIT_CRITICAL()
{
	pthread_mutex_unlock(&g_mutex);
}

int CRITICAL_INIT()
{
	pthread_mutex_init(&g_mutex, NULL);
}

int CRITICAL_DEINIT()
{
	pthread_mutex_destroy(&g_mutex);
}


void *thread_timer(void* arg)
{
	printf("new thread,thread is :%u,pid:%d\n",pthread_self(),getpid());
	while(1) {
		sleep(1);
		OnTimer();
		//pthread_exit(NULL);
	}
}

char *msg1 = "hello hehe hehe hhe hs";
void *thread_run1(void* arg)
{
	printf("new thread,thread is :%u,pid:%d\n",pthread_self(),getpid());
	CommSaveMsg(11,msg1,strlen(msg1));
	while(1) {
		sleep(5);
		printf("save ret:%d\n",CommSaveMsg(10,msg1,strlen(msg1)));
	}
}

void *thread_run2(void* arg)
{
	char ms[100];
	int ret,len;
	printf("new thread,thread is :%u,pid:%d\n",pthread_self(),getpid());
	while(1) {
		sleep(3);

		ret = CommGetMsg(10,ms,&len);
		
		printf("get ret:%d  len:%d\n",ret,len);
	}
}





int main()
{
	CommuInit();
	CommSetEventHandler(handler);

	pthread_t tid_timer,tid_run1,tid_run2;
	pthread_create(&tid_timer,NULL,thread_timer,NULL);
	pthread_create(&tid_run1,NULL,thread_run1,NULL);
	pthread_create(&tid_run2,NULL,thread_run2,NULL);

	while(1){
		sleep(10);
	}

	return 0;
}
