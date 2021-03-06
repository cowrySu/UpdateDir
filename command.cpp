/*************************************************************************
    > File Name: command.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月23日 星期三 14时48分05秒
 ************************************************************************/
#include "command.h"
#include<iostream>

#include "dir.h"
#include "log.h"


Command::Command()
{
	func = &Command::mkdir;
	execute["mv"] = &Command::mv;
	execute["cp"] = &Command::cp;
	execute["mkdir"] = &Command::mkdir;
	execute["touch"] = &Command::touch;
	execute["cd"] = &Command::cd;
	execute["ls"] = &Command::ls;
	execute["rm"] = &Command::rm;

	myDir = NULL;
	commandHistory.clear();
	memento.clear();

	myLog = new Log("command.log");
	myLog->Log_Debug("Command::Command");
}
bool Command::SetCommand(std::string commandStr)
{
	// opt param1 param2
	size_t beginIndex = commandStr.find_first_not_of(' ', 0);
	size_t endIndex = std::string::npos;
	size_t maxLen = commandStr.find_last_not_of(' ');

	if ((endIndex = commandStr.find(' ', beginIndex)) != maxLen)
	{
		opt = commandStr.substr(beginIndex, endIndex - beginIndex);
	}
	else
	{
		std::cerr << "error command" << std::endl;
	}

	beginIndex = endIndex + 1;

	if ((endIndex = commandStr.find(' ', beginIndex)) != maxLen)
	{
		param1 = commandStr.substr(beginIndex, endIndex - beginIndex);
	}
	else 
	{
		param1 = commandStr.substr(beginIndex, maxLen - beginIndex);
	}

	beginIndex = endIndex + 1;

	if ((endIndex = commandStr.find(' ', beginIndex)) != maxLen)
	{
		param2 = commandStr.substr(beginIndex, endIndex - beginIndex);
	}
	else 
	{
		param2 = commandStr.substr(beginIndex, maxLen - beginIndex);
	}
	
	return true;
}
bool Command::Execute()
{
	myLog->Log_Info("Command::Execute:" + opt);
	if (execute.count(opt) > 0)
	{
		(this->*execute[opt])();
	}
	else 
	{
		std::cerr << "command is error" << std::endl;
	}
	return true;
}

bool Command::History()
{
	for (auto it = commandHistory.begin(); it != commandHistory.end(); ++it)
	{
		std::cout << (*it) << std::endl;
	}
	return true;
}
bool Command::CreateMemento(std::string dscr)
{
	if (myDir)
	{
		if (memento.count(dscr) > 0)
		{
			std::cerr << "the tag you input is exist" << std::endl;
		}
		else 
		{
			memento[dscr] = myDir->copyDir();
		}
	}
	else
	{
		std::cerr << "directory is NULL" << std::endl;
	}
	return true;
}
bool Command::SetMemento(std::string dscr)
{
	// how to destroy the dir*	
	// should use shared_ptr<Dir*>
	if (memento.count(dscr) > 0)
	{
		myDir = memento[dscr];
	}
	else 
	{
		std::cerr << "the tag you input is not exist" << std::endl;
	}
	return true;
}

std::vector<std::string> Command::lss()
{
	return myDir->Lss();
}

void Command::mv()
{
	if (myDir)
	{
		myDir->Mv(param1, param2);
	}
	else
	{
		std::cerr << "directory is null" << std::endl;
	}
}
void Command::cp()
{
	if (myDir)
	{
		myDir->Cp(param1, param2);
	}
	else
	{
		std::cerr << "directory is null" << std::endl;
	}
}

void Command::mkdir()
{
	std::string m("");
	myLog->Log_Info(m + "command::mkdir" + "  param1=" + param1);
	if (myDir)
	{
		myDir->MakeDir(param1);
	}
	else
	{
		myDir = new Dir("", param1, NULL, false);
	}
}

void Command::rm()
{
	if (myDir)
	{
		myDir->Rm(param1);
	}
	else
	{
		std::cerr << "directory is null" << std::endl;
	}
}

void Command::touch()
{
	if (myDir)
	{
		myDir->Touch(param1);
	}
	else
	{
		std::cerr << "directory is null" << std::endl;
	}
}
void Command::cd()
{
	if (myDir)
	{
		myDir = myDir->Cd(param1);
	}
	else
	{
		std::cerr << "directory is null" << std::endl;
	}
}
void Command::ls()
{
	if (myDir)
	{
		myDir->Ls();
	}
	else
	{
		std::cerr << "directory is null" << std::endl;
	}
}
#ifdef COMMAND_TEST
int main()
{
	Command myCommand;
	myCommand.lss();
	std::string command;
	while (true)
	{
		getline(std::cin, command);
		myCommand.SetCommand(command);
		myCommand.Execute();
	}
	return 0;
}
#endif
