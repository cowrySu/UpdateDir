/*************************************************************************
    > File Name: log.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月22日 星期二 17时02分16秒
 ************************************************************************/
#ifndef _LOG_HEADER_
#define _LOG_HEADER_
#include <fstream>
#include <string>
class Log
{
	public:
		Log(std::string fName);
		void Log_Info(std::string);
		void Log_Warning(std::string);
		void Log_Debug(std::string);
		void Log_Error(std::string);
	private:
		void create_ostream();
	private:
		std::string logFileName;
		uint32_t logFileIndex;
		uint32_t logFileCount;
		std::ofstream os;
};
#endif

