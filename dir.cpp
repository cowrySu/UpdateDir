/*************************************************************************
    > File Name: dir.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月16日 星期三 18时07分30秒
 ************************************************************************/

#include<iostream>
#include "dir.h"

Dir::Dir(std::string name1, Dir* father1) 
{
	childs.clear();
	name = name1;
	father = father1;
}
bool Dir::MakeDir(std::string name)
{
	//std::cout << "Dir::MakeDir" << std:: endl;
	Dir *newNode = new Dir(name, this);
	childs.push_back(newNode);
	return true;
}

bool Dir::Cp(DirTree *target, std::string path)
{
	std::cout << "Dir::Cp" << std::endl;
	 if (IsFile)
	 {
		 std::cout << "OK" << std::endl;
	 }
	return true;
}

bool Dir::Touch(std::string fileName)
{
	//std::cout << "Dir::Touch" << std::endl;
	Dir *newNode = new Dir(fileName, this);
	newNode->IsFile = true;
	childs.push_back(newNode);
	return true;
}
bool Dir::Ls()
{
	std::vector<DirTree*>::iterator it;
	for (it = childs.begin(); it != childs.end(); ++it)
	{
		(*it)->Message();
	}
	return true;
}
bool Dir::Message()
{
	if (IsFile)
	{
		std::cout << "fileName:" << name << std::endl;
	}
	else{
		std::cout << "dirName:" << name << std::endl;
	}
	return true;
}

#ifdef UNIT_TEST

int main()
{
	Dir *myDir = new Dir("root",NULL);
	std::string parm("test");
	myDir->MakeDir(parm);

	return 0;
}

#endif

