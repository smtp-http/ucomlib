#ifndef __UCOMLIB_H__
#define __UCOMLIB_H__

typedef int (*EVENT_HANDLER)(const int event,const int msgId);

int CommuInit(void);
int CommSetEventHandler(EVENT_HANDLER ev);


#endif

