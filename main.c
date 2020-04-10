//#include "Communication.h"
//#include "Timer.h"
#include <stdio.h>
//#include "list.h"
#define __DEBUG__
#include "ucomlib.h"
#include <pthread.h>
#include <string.h>

pthread_mutex_t g_mutex;

int flag = 1;
int handler(const int event,const int msgId)
{
	int ret,len;
	char ms[100];
	char *msg2 = "123456789123456789";
	switch (event) {
		case EV_TIMEOUT:
			printf("ev_timeout\n");
			if(flag){
				ret = CommGetMsg(11,ms,&len);
				ms[len+1]=0;
				printf("get ret:%d  len:%d  m:%s\n",ret,len,ms);
			} else {
				printf("save ret:%d\n",CommSaveMsg(11,msg2,strlen(msg2)));
			}
			flag = !flag;
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
		sleep(2);
		OnTimer();
		//pthread_exit(NULL);
	}
}

char *msg1 = "12345678901234567";
char *msg2 = "Time out,-edit!";
void *thread_run1(void* arg)
{
	char ms[100];
	int ret,len;
	printf("new thread,thread is :%u,pid:%d\n",pthread_self(),getpid());
	CommSaveMsg(11,msg2,strlen(msg2));
	while(1) {
		sleep(5);
		printf("len:%d  save ret:%d\n",strlen(msg1),CommSaveMsg(10,msg1,strlen(msg1)));
		sleep(5);
		ret = CommGetMsg(10,ms,&len);
		ms[len+1]=0;
		printf("get ret:%d  len:%d  ms:%s\n",ret,len,ms);
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
	//pthread_create(&tid_run2,NULL,thread_run2,NULL);

	while(1){
		sleep(10);
	}

	return 0;
}
