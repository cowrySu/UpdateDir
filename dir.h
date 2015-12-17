/*************************************************************************
    > File Name: dir.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月16日 星期三 17时59分14秒
 ************************************************************************/

#ifndef _UPDATE_DIR_DIR_
#define _UPDATE_DIR_DIR_

#include <vector>
#include <string.h>
class Dir 
{
	public:
		Dir() = default;
		Dir(std::string fatherpath,std::string dirname,Dir* f);
		bool MakeDir(std::string name);
		bool Cp(Dir *target, std::string path);
		bool Touch(std::string fileName);
		bool Ls();
		bool Message();
		bool IsFile = false;
		Dir* Cd(std::string path);
	public:
		bool equal(std::string n)
		{
			return n == dirName;
		}
		Dir* father()
		{
			return fatherDir;
		}
		Dir* exist(std::string nameStr);

	private:
		std::string fatherPath;
		std::string dirName;
		std::vector<Dir*> childs;
		Dir* fatherDir;
};

#endif
