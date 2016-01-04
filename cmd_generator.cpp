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

#include "log.h" 

#define random(x) (rand()%x)
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
}

void CmdGenerator::Generate()
{
	// reset cmd
	static Log myLog("cmd_generator.log");
	cmd = "";
	int x = random(cmds.size());
	int paramCount;
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
	switch(paramCount)
	{
		case -1: cmd += " "; cmd += "dir"; cmd += random(100);break; // mkdir dir?
		case -2: cmd += " "; cmd += "file"; cmd += random(100);break; // mkdir file?
		case 1: cmd += " "; cmd += params[random(params.size())]; break;
		case 2: cmd += " "; cmd += params[random(params.size())] + " " + params[random(params.size())];break;
		default: break;
	}
	myLog.Log_Info(cmdGeneratorId + " " + cmd);
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
