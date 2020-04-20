# ucomlib

A simple key-value memory database


## 1.接口定义
ucomlib接口主要有：
 * 初始化和去初始化。
 * 数据读取和存储接口。
 * 超时机制。

### 1.1 初始化和去初始化
```
int CommuInit(void);
```
### 1.2 数据读取和存储接口
```
int CommSaveMsg(const int msgId,const char *msgData,unsigned int dataLen)
功能：
  数据存储

参数：
  msgId: 消息ID
  msgData: 数据内容
  dataLen:数据长度


int CommGetMsg(const int msgId,char *msgData,unsigned int* pDataLen)

功能：
  获取数据（同时数据删除）
参数：
  msgId：消息ID
  msgData:获取数据存储地址
  pDataLen:获取到的数据长度
```

### 1.3 超时机制相关。


超时处理功能需要用户实现超时处理函数，然后调用接口：
```
int CommSetEventHandler(EVENT_HANDLER ev)
```
进行添加。

需要在用户的定时程序中调用：
```
int OnTimer()
```
来更新计数并出发超时事件


### 1.5 需要用户实现的回调函数
#### 1.  事件（超时）处理函数
      函数类型为：typedef int (*EVENT_HANDLER)(const int event,const int msgId)
      
#### 2.  互斥锁
```
int CRITICAL_INIT();
void ENTER_CRITICAL();
void EXIT_CRITICAL();
int CRITICAL_DEINIT();
```
在MCU中可以用关中断和开中断实现，linux下用线程锁pthread_mutex_t。

#### 3. 命令（应答）处理函数:
```
     函数类型：typedef int (*command_handler_t)(void *para)。
```

## 2．应用实例：
这里实现了一个并发环境访问的简单实例。
代码：

[main.c](https://github.com/smtp-http/ucomlib/blob/master/main.c)

