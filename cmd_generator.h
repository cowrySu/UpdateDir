/*************************************************************************
    > File Name: cmd_generator.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2016年01月04日 星期一 15时56分13秒
 ************************************************************************/
#ifndef _UPDATE_DIR_CMD_GENERATOR_
#define _UPDATE_DIR_CMD_GENERATOR_

#include <string>
#include <map>
#include <vector>
class Log;
class CmdGenerator
{
	public:
		CmdGenerator();
		CmdGenerator(std::string id);
		std::string CmdId();
		std::string Cmd();
		void SetParams(std::vector<std::string> newp);
		void Generate();
	private:
		Log *myLog;
		std::string cmdGeneratorId;
		std::vector<std::string> params;
		std::map<std::string, int> cmds; // int is the number of its params
		std::string cmd;
};

#endif
