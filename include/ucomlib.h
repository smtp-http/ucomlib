#ifndef __UCOMLIB_H__
#define __UCOMLIB_H__


/////////////////////////// error code ///////////////////////////////
#define ERR_TARGET_NULL    -10
#define ERR_DATA_EXCESSIVE -11
#define ERR_ID_EXIST       -12
#define ERR_MSG_TOO_LONG   -13
#define ERR_MSG_BUF_FULL   -14
#define ERR_MSG_NOT_EXIST  -15

/////////////////////////// user implementation //////////////////////
typedef int (*EVENT_HANDLER)(const int event,const int msgId);

int CRITICAL_INIT();
void ENTER_CRITICAL();
void EXIT_CRITICAL();
int CRITICAL_DEINIT();
int OnTimeOut();



/////////////////////////////////// debug ////////////////////////////
//#define __DEBUG__
#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif
/*example*/
// char str[]="Hello World";  
// DEBUG("A ha, check me: %s",str);
//
//////////////////////////////////////////////////////////////////////
#define MAX_ASYNC_MSG_NUM   10

///////////////////////////// API ////////////////////////////////////
int CommuInit(void);
int CommSetEventHandler(EVENT_HANDLER ev);
int OnTimer(int msec);


#endif

