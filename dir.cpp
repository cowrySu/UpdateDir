/*************************************************************************
    > File Name: dir.cpp
    > Author: swn
    > Mail: 1635737693@qq.com 
    > Created Time: 2015年12月16日 星期三 18时07分30秒
 ************************************************************************/

#include<iostream>
#include "dir.h"

Dir::Dir(std::string fatherpath, std::string name1, Dir* father1) : fatherPath(fatherpath), dirName(name1), fatherDir(father1) 
{
}
bool Dir::MakeDir(std::string name)
{
	//std::cout << "Dir::MakeDir" << std:: endl;
	if (exist(name))	
	{
		return false;
	}
	Dir *newNode = new Dir(fatherPath + "/" + dirName, name, this);
	childs.push_back(newNode);
	return true;
}
Dir *Dir::copyDir()
{
	Dir *newNode = new Dir(fatherPath, dirName, fatherDir);
	for (auto it = childs.begin(); it != childs.end(); ++it)
	{
		newNode->add((*it)->copyDir());
	}
	return newNode;
}
bool Dir::Cp(std::string fromPathStr, std::string toPathStr)
{
	Dir *fromDir = Cd(fromPathStr);
	Dir *toDir = Cd(toPathStr);
	toDir->add(fromDir->copyDir());
	return true;
}

bool Dir::Touch(std::string fileName)
{
	//std::cout << "Dir::Touch" << std::endl;
	if (exist(fileName))
	{
		return false;
	}
	Dir *newNode = new Dir(fatherPath + "/" + dirName, fileName, this);
	newNode->IsFile = true;
	childs.push_back(newNode);
	return true;
}
bool Dir::Ls()
{
	std::vector<Dir*>::iterator it;
	for (it = childs.begin(); it != childs.end(); ++it)
	{
		(*it)->Message();
		(*it)->Ls();
	}
	return true;
}
bool Dir::Message()
{
	if (IsFile)
	{
		std::cout << fatherPath << "/" << dirName << std::endl;
	}
	else{
		std::cout << fatherPath << "/" << dirName << "/" << std::endl;
	}
	return true;
}
bool Dir::Rm(std::string dirName)
{
	Dir *delDir = NULL; 
	int beginIndex = 0;
	int endIndex = dirName.find_last_of('/');

	if (endIndex == std::string::npos)
	{
		// the target directory is single-level directory
		auto it = childs.begin();
		for (; it != childs.end(); ++it)
		{
			if ((*it)->equal(dirName))
			{
				childs.erase(it);
				break;
			}
		}
		if (it == childs.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	// the target directory is multy-level directory
	std::string fatherDirPath = dirName.substr(beginIndex,endIndex - beginIndex);
	std::string delDirStr = dirName.substr(endIndex + 1,dirName.length() - endIndex);
	Dir *fatherDir = Cd(fatherDirPath);
	return	fatherDir->Rm(delDirStr);
}
Dir* Dir::Cd(std::string dir)
{
	Dir* targetDir = NULL;
	if ("." == dir)
	{
		targetDir = this;
	}
	if (".." == dir)
	{
		if (fatherDir)
		{
			targetDir = fatherDir;
		}
		else
		{
			std::cout << "this is root" << std::endl;
		}
	}
	// deal path
	if (dir.find("/", 0) == std::string::npos)
	{
		std::vector<Dir*>::iterator it;
		for (it = childs.begin(); it != childs.end(); ++ it)
		{
			if ((*it)->equal(dir))
			{
				targetDir = *it;
				break;
			}
		}
	}
	else
	{
		Dir *curDir = this;
		Dir *subDir = NULL;
		// frined function will be better
		while (curDir->father())
		{
			curDir = curDir->father();
		}
		// deal /123/456/7
		int beginIndex = 1;
		int endIndex = 0;
		int maxLen = dir.length();
		std::string subDirStr;

		while ((endIndex = dir.find_first_of('/',beginIndex)) != std::string::npos )
		{
		    subDirStr = dir.substr(beginIndex, endIndex - beginIndex);
			beginIndex = endIndex + 1;
			if (curDir->equal(subDirStr) && !curDir->father()) 
			{ // it is root 
				continue;
			}
			subDir = curDir->exist(subDirStr);
			if (subDir && !subDir->IsFile) 
			{
				curDir = subDir; 
			} 
			else 
			{
				std::cerr << "illegal directory path" << std::endl;
				break; 
			}
		}
		if (endIndex == std::string::npos)
		{
			subDirStr = dir.substr(beginIndex, maxLen - beginIndex);
			subDir = curDir->exist(subDirStr);
			if (curDir->equal(subDirStr) && !curDir->father())
			{
				targetDir = curDir;
			}
			else if(subDir && !subDir->IsFile)
			{
				targetDir = subDir;
			}
			else
			{
				std::cerr << "illegal directory path" << std::endl;
			}
		}
	}
	return targetDir;
}
Dir* Dir::exist(std::string nameStr)
{
	Dir* target = NULL;
	std::vector<Dir*>::iterator it;
	for (it = childs.begin(); it != childs.end(); ++ it)
	{
		if((*it)->equal(nameStr))
		{
		//	std::cout << "Dir is Exist" << std::endl;
			target = *it;
			break;
		}
	}
	return target;
}
#ifdef UNIT_TEST

int main()
{
	Dir *myDir = new Dir("", "root", NULL);
	std::string parm("test");
	myDir->MakeDir(parm);
	myDir->MakeDir(parm+"1");
	myDir->Touch(parm+".txt");
	myDir = myDir->Cd(parm+"1");
	myDir->MakeDir(parm+"3");
	myDir = myDir->Cd("/root/test");
	myDir->MakeDir(parm + "4");
	myDir->Rm("/root/test.txt");
	myDir = myDir->Cd("/root");
	Dir*	d = myDir->copyDir(); // memery leak
	d->Ls();
	myDir->Cp("/root/test1", "/root/test");
	std::cout << "--------------------" << std::endl;
	myDir->Ls();
	return 0;
}

#endif

