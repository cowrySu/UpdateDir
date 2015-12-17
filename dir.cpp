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

bool Dir::Cp(Dir *target, std::string path)
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
			if (!subDir && !subDir->IsFile) 
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
			if (!subDir && !subDir->IsFile)
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
			std::cout << "Dir is Exist" << std::endl;
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
	myDir = myDir->Cd(parm+"1");
	myDir->MakeDir(parm+"3");
	myDir = myDir->Cd("/root");
	myDir->MakeDir(parm + "4");

	myDir->Ls();
	return 0;
}

#endif

