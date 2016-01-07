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
#include <map>
class Dir;
class Log;
class Command
{
	public:
		typedef void (Command::*func_ptr)();
		void (Command::*func)();
	public:
		Command();
		bool SetCommand(std::string commandStr);
		bool Execute();
		bool History(); // look up command

		bool CreateMemento(std::string dscr);
		bool SetMemento(std::string dscr); 
		std::vector<std::string> lss();
	private:
		 void mv();
		 void cp();
		 void mkdir();
		 void rm();
		 void touch();
		 void cd();
		 void ls();
	private:
		std::string opt;
		std::string param1;
		std::string param2;

		Dir *myDir;
		std::map<std::string, Dir*> memento;	
		std::vector<std::string> commandHistory;
		std::map<std::string, func_ptr> execute;
		
		Log *myLog;
};
#endif
