/*************************************************************************
    > File Name: single_thread.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2016年01月04日 星期一 22时43分24秒
 ************************************************************************/
#ifndef _UPDATE_DIR_SINGLE_THREAD_
#define _UPDATE_DIR_SINGLE_THREAD_

#include "cmd_generator.h"
#include "command.h"

class SingleThread
{
	public:
		SingleThread() = default;
		void Execute();
	private:
		CmdGenerator myCmdGenerator; // no perfect, shall default construct
		Command myCommand;	
};
#endif
