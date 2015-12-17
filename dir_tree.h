/*************************************************************************
    > File Name: dir_tree.h
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月16日 星期三 17时49分44秒
 ************************************************************************/

#ifndef _UPDATE_DIR_TREE_
#define _UPDATE_DIR_TREE_
#include <string.h>
#include <vector>
class DirTree
{
	public:
		bool IsFile;
		virtual bool MakeDir(std::string name) = 0;
		virtual bool Cp(DirTree *target, std::string path) = 0;
		virtual bool Touch(std::string fileName) = 0;
		virtual bool Message() = 0;
	protected:
		std::string name;
		DirTree *father;
		std::vector<DirTree *> childs;
		bool request(std::string);
};
#endif
