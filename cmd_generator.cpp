/*************************************************************************
    > File Name: cmd_generator.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2016年01月04日 星期一 16时08分16秒
 ************************************************************************/
#include "cmd_generator.h"
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>

#include "log.h" 

#define random(x) (rand()%x)
CmdGenerator::CmdGenerator()
{
	CmdGenerator("default_name");
}
CmdGenerator::CmdGenerator(std::string id): cmdGeneratorId(id)
{
	params.clear();
	cmds.clear();
	cmds["cd"] = 1;
	cmds["ls"] = 0;
	cmds["cp"] = 2;
	cmds["mkdir"] = -1;
	cmds["touch"] = -2;

	srand((int)time(0));

	myLog = new Log("cmd_generator.log");

	myLog->Log_Debug("constructor CmdGenerator");
	
	std::stringstream ss;
	ss << "cmds.size = " << cmds.size() << std::endl;
	myLog->Log_Debug(ss.str());
}

void CmdGenerator::Generate()
{
	// reset cmd
	cmd = "";
;
	if (cmds.size() == 0)
	{
		myLog->Log_Warning("cmds.size = 0, please check");
		return ;
	}
	else
	{
		std::stringstream ss;
		ss << "cmds.size = " << cmds.size() << std::endl;
		myLog->Log_Debug(ss.str());
	}
	int x = random(cmds.size());
	int paramCount;
	myLog->Log_Debug("CmdGenerator::Generate");
	for (auto it = cmds.begin(); it != cmds.end(); ++ it)
	{
		if (x == 0)
		{
			cmd = it->first;
			paramCount = it->second;
			break;
		}
		--x;
	}
	std::stringstream ss;
	ss << random(100);
	switch(paramCount)
	{
		case -1: cmd += " "; cmd += "dir"; cmd += ss.str(); break; // mkdir dir?
		case -2: cmd += " "; cmd += "file"; cmd += ss.str(); break; // mkdir file?
		case 1: cmd += " "; cmd += params[random(params.size())]; break;
		case 2: cmd += " "; cmd += params[random(params.size())] + " " + params[random(params.size())];break;
		default: break;
	}
	return ;
}
std::string CmdGenerator::Cmd()
{
	if (cmd.length() == 0)
	{
		myLog->Log_Warning("cmd is null");
		return NULL;
	}
	myLog->Log_Info(cmd);
	return cmd;
}
std::string CmdGenerator::CmdId()
{
	if (cmdGeneratorId.length() == 0)
	{
		myLog->Log_Warning("cmdGeneratorId is NULL");
		return NULL;
	}
	myLog->Log_Info(cmdGeneratorId);
	return cmdGeneratorId;
}
void CmdGenerator::SetParams(std::vector<std::string> p)
{
	if (p.size() == 0)
	{
		myLog->Log_Warning("SetParams's param is NULL or zero_size");
		return ;
	}
	if (cmds.size() == 0)
	{
		myLog->Log_Warning("cmds's size is 0");
	}
	std::string msg = "params:";
	for (auto str = p.begin(); str != p.end(); ++str)
	{
		msg += *str + "\n";
	}
	params.swap(p); // core dump at here and IO has not flush
	return ;
}
#ifdef CMD_GENERATOR_TEST
int main()
{
	std::vector<std::string> newp = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	std::cout << newp.size() << std::endl;
	CmdGenerator myCmd("swn");
	myCmd.SetParams(newp);
	while (true)
	{
		myCmd.Generate();
		std::cout << myCmd.Cmd() << std::endl;
	}
	return 0;
}
#endif
