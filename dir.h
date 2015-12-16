/*************************************************************************
    > File Name: dir.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月16日 星期三 17时59分14秒
 ************************************************************************/

#ifndef _UPDATE_DIR_DIR_
#define _UPDATE_DIR_DIR_

#include "dir_tree.h" 

class Dir : public DirTree
{
	public:
		Dir() = default;
		Dir(std::string ,Dir* );
		bool MakeDir(std::string name);
		bool Cp(DirTree *target, std::string path);
		bool Touch(std::string fileName);
		bool Ls();
		bool Message();

};

#endif
