#include "pch.h"
#include "File.h"

File::File()
{
	m_path = _getcwd(NULL, 512);
}

void File::AddFolder(const std::string& name)
{
	std::string cmd;
	cmd = "mkdir ";
	cmd += m_path;
	cmd += name;
	std::cout << cmd << std::endl;
	system(cmd.c_str());
}

void File::Add(const std::string& name)
{
	std::fstream f;
	f.open(m_path+name, std::ios::out);
	f.close();
}

void File::Delete(const std::string& name)
{
	std::string cmd;
	cmd = "del ";
	cmd += m_path;
	cmd += name;
	std::cout << cmd << std::endl;
	system(cmd.c_str());
}

void File::Update(const std::string& oldfile, const std::string& newfile)
{
	Add(newfile);
	std::string cmd;
	cmd = "copy ";
	cmd += m_path;
	cmd += oldfile;
	cmd += " ";
	cmd += m_path;
	cmd += newfile;
	std::cout << cmd << std::endl;
	system(cmd.c_str());
	Delete(oldfile);
}

void File::Open(const std::string& name,const bool&onlyread)
{
	std::string cmd;
	if (onlyread)
	{
		//设为只读
		cmd = "attrib +R ";
		cmd += m_path + name;
		std::cout << cmd << std::endl;
		system(cmd.c_str());
	}
	else
	{
		//取消只读
		cmd = "attrib -R ";
		cmd += m_path + name;
		std::cout << cmd << std::endl;
		system(cmd.c_str());
	}
	cmd = "start ";
	cmd += m_path;
	cmd += name;
	std::cout << cmd << std::endl;
	system(cmd.c_str());
}

bool File::Upload(const std::string& from, const std::string& to)
{
	std::string cmd = "copy ";
	cmd += from;
	cmd += " ";
	cmd += m_path + to;
	std::cout << cmd << std::endl;
	std::fstream f;
	std::string str;
	for (int i = 0; i < from.size(); i++)
	{
		str.push_back(from[i]);
		if (from[i] == '\\')
		{
			str.push_back(from[i]);
		}
	}
	std::cout << str << std::endl;
	f.open(str);
	if (f.is_open())
	{
		system(cmd.c_str());
		f.close();
		return 1;
	}
	else
	{
		f.close();
		return 0;
	}
}

void File::Download(const std::string& name, const std::string& target)
{
	std::string from = m_path+"\\root\\Paper\\";
	from += name;
	std::string to = m_path + target + name;
	File f;
	f.Add(to);
	std::string cmd = "copy ";
	cmd += from;
	cmd += " ";
	cmd += to;
	std::cout << from << std::endl;
	std::cout << to << std::endl;
	system(cmd.c_str());
}
