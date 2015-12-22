/*************************************************************************
    > File Name: command.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月22日 星期二 15时25分38秒
 ************************************************************************/

#ifndef _UPDATE_DIR_COMMOND_
#define _UPDATE_DIR_COMMOND_
#include <string>
#include <vector>

class Dir;
class Command
{
	public:
		SetCommand(std::string commandStr);
		Execute();
		History(); // look up command

		CreateMemento();
		SetMemento(); 
	private:
		std::string opt;
		std::string param1;
		std::string param2;

		Dir *myDir;
		std::stack<Dir*> memento;	
		std::vector<string> commandHistory;
};
#endif
