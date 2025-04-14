#pragma once
#include"Button.h"
#include"TextBox.h"
#include"Window.h"
#include"Account.h"
#include"File.h"
class Login
{
public:
	Login(const WindowPros& pros = WindowPros());
	~Login();
	int Init();
	int Show();
public:
	Window* m_window;
private:
	std::vector<Button*>buttons;
	Account* m_account;
};
