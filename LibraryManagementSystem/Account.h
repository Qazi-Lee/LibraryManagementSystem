#pragma once
#include"Window.h"
#include"Button.h"
#include"TextBox.h"
#include"DataBase.h"
#include"Message.h"
#include"File.h"

class Account
{
public:
	using LoginMuneFn = std::function<int()>;
public:
	Account() { m_window = new Window; m_loginmunefn = nullptr; errormsg = new Message(0, m_window->m_pros.Height - 40, m_window->m_pros.Width / 2-60, m_window->m_pros.Height); }
	~Account();
	void SetLoginMuneFn(const LoginMuneFn& fn) { m_loginmunefn = fn; }
	virtual void Login() = 0;
	virtual void Main() = 0;
public:
	std::string m_account;
	std::string m_password;
	Window* m_window;
	Message* errormsg;
	LoginMuneFn m_loginmunefn;
};
class Manager :public Account
{
public:
	void Login() override;
	void Main()override;
	Manager();
private:
	void ManageBooks();
	void ManagePaper();
	void ManageReader();
	void ManageMessage();
	void Add(const std::string &tablename);
	void Delete(const std::string& tablename);
	//Delete函数的子函数
	void Delete1(const std::string& tablename,const pqxx::row&r);
	void Update(const std::string& tablename);
	void Update1(const std::string& tablename, const pqxx::row& r);
	void Select(const std::string& tablename);
	void ShowAll(const std::string& tablename);
	void ShowAll(const std::string& tablename, const pqxx::result& res);
};
class User :public Account
{
public:

	void Login()override;
	void Main()override;
	User();
private:
	void ManageBooks();
	void ManagePaper();
	void Select(const std::string& tablename);
	void ShowAll(const std::string& tablename, const pqxx::result& res);
	void BorrowBooks();
	void Borrow(const pqxx::row&r);
	void ReturnBooks();
	void Return(const pqxx::row&r);
	void UploadPaper();
	void Upload(const std::string& sql,const std::string&name);
	void DownloadPaper();
	void Download(const pqxx::row&r);
};
class Visit :public Account
{
public:

	void Login()override;
	void Main()override;
	void ShowAll(const std::string& tablename);
	Visit() {};
};
