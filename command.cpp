/*************************************************************************
    > File Name: command.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月23日 星期三 14时48分05秒
 ************************************************************************/
#include "command.h"
#include "dir.h"
#include<iostream>

Command::Command()
{
	execute["mv"] = mv;
	/*
	execute["cp"] = (cp);
	execute["mkdir"] = func_ptr(mkdir);
	execute["touch"] = func_ptr(touch);
	execute["cd"] = func_ptr(cd);
*/
	myDir = NULL;
	commandHistory.clear();
	memento.clear();
	execute.clear();
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
	execute[opt]();
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
		memento[dscr] = myDir->copyDir();
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
	myDir = memento[dscr] != NULL ? memento[dscr] : myDir;
	return true;
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
	if (myDir)
	{
		myDir->MakeDir(param1);
	}
	else
	{
		myDir = new Dir("/", param1, NULL, false);
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
	std::string command;

	while (std::cin >> command)
	{
		myCommand.SetCommand(command);
		myCommand.Execute();
	}
	return 0;
}
#endif
