/*************************************************************************
    > File Name: single_thread.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2016年01月04日 星期一 22时43分24秒
 ************************************************************************/

#include "single_thread.h"
#include<iostream>
#include <unistd.h>

void SingleThread::Execute()
{
	while (true)
	{
		myCmdGenerator.SetParams(myCommand.lss());
		myCmdGenerator.Generate();
		myCommand.SetCommand(myCmdGenerator.Cmd());
		myCommand.Execute();
		sleep(5);
	}
}
#ifdef SINGLE_THREAD_TEST
int main()
{
	SingleThread mySingleThread;
	mySingleThread.Execute();
	return 0;
}
#endif
