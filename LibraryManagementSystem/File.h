#pragma once
#include"pch.h"
class File
{
public:
	File();
	std::string  GetPath()const { return m_path; }
	//设置默认路径
	void SetPath(const std::string& path) { m_path = path; };
	//添加文件夹
	void AddFolder(const std::string& name);
	//添加文件
	void Add(const std::string& name);
	//删除文件
	void Delete(const std::string& name);
	//更新方式采用创建新文件后将老文件数据复制后删除老文件（重命名）
	void Update(const std::string& oldfile, const std::string& newfile);
	//打开文件，可由第二个参数指定打开方式为只读
	void Open(const std::string& name, const bool& onlyread = true);
	//实现文件下载，本质是从默认下载路径复制文件到指定路径
	void Download(const std::string& name, const std::string& target);
	//实现文件上传，本质是从指定路径复制文件到默认路径
	bool Upload(const std::string&from,const std::string&to);
	
public:
	std::string m_path;
};

