/*************************************************************************
    > File Name: log.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月22日 星期二 19时42分08秒
 ************************************************************************/
#include "log.h"
#include<iostream>
#include <sstream>
#include <time.h>

Log::Log(std::string fName): logFileName(fName), logFileIndex(1), logFileCount(1)
{
	create_ostream();
}
void Log::create_ostream()
{
	if (os.is_open())
	{
		os.flush();
		os.clear();
		os.close();
	}
	std::stringstream sstr;
	sstr << logFileIndex;
	os.open(logFileName + sstr.str(), std::ios::out);
	logFileIndex ++;
}
void Log::Log_Info (std::string logMesg)
{
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[80];

	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime (buffer, 80, "%F %r", timeInfo);
	os << buffer << "LOG_INFO " << "\t" << logMesg << std::endl; 
	logFileCount ++;

	if (logFileCount % 1000 == 0)
	{
		logFileCount = 1;
		create_ostream();
	}
}

void Log::Log_Warning(std::string logMesg)
{
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[80];

	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(buffer, 80, "%F %r", timeInfo);
	os << buffer <<  "LOG_WARNING "<<"\t" << logMesg << std::endl; 
	logFileCount ++;

	if (logFileCount % 1000 == 0)
	{
		logFileCount = 1;
		create_ostream();
	}
}

void Log::Log_Debug(std::string logMesg)
{
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[80];

	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime (buffer, 80, "%F %r", timeInfo);
	os << buffer <<  "LOG_DEBUG"<<"\t" << logMesg << std::endl; 
	logFileCount ++;

	if (logFileCount % 1000 == 0)
	{
		logFileCount = 1;
		create_ostream();
	}
}
 
void Log::Log_Error(std::string logMesg)
{
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[80];

	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(buffer, 80, "%F %r", timeInfo);
	os << buffer <<"LOG_ERROR"<<"\t" << logMesg << std::endl; 
	logFileCount ++;

	if (logFileCount % 1000 == 0)
	{
		logFileCount = 1;
		create_ostream();
	}
}
#ifdef LOG_TEST 
int main()
{
	Log myLog("test.log");
	for (int i = 0; i < (10000); ++i)
	{
		myLog.Log_Error("it is my Error");
		myLog.Log_Warning("it is my warning");
		myLog.Log_Info("it is my warning");
		myLog.Log_Debug("it is my warning");
	}
	return 0;
}
#endif
