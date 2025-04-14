#include"pch.h"
#include "Login.h"

Login::Login(const WindowPros& pros)
{
	//默认值为1280,720
	m_window = new Window();
	m_window->m_pros = pros;
	m_account = nullptr;
}

Login::~Login()
{
	if (m_window != nullptr)
	{
		delete m_window;
		m_window = nullptr;
	}
	if (m_account != nullptr)
	{
		delete m_account;
		m_account = nullptr;
	}
	if (!buttons.empty())
	{
		for (Button* b : buttons)
		{
			if (b != nullptr)
			{
				delete b;
				b = nullptr;
			}
		}
	}
	buttons.clear();
}
int Login::Show()
{
	cleardevice();
	RECT r = { 0,0,m_window->m_pros.Width,m_window->m_pros.Height / 4 };
	drawtext(_T("Welcome to Library!"), &r, DT_CENTER | ODT_BUTTON | DT_SINGLELINE);
	for (Button* b : buttons)
	{
		b->Creat();
	}
	ExMessage m;
	bool run = true;
	while (run) {
		m = getmessage(EX_MOUSE | EX_KEY);
		if (m.message == WM_LBUTTONDOWN) {

			std::cout << "x:" << m.x << " " << "y:" << m.y << std::endl;
			for (Button* b : buttons)
			{
				if (b->IsPressed(m.x, m.y))
				{
					std::cout << b->Getname() << std::endl;
					if (b->Getname() == "manager")
					{
						run = false;
						cleardevice();
						m_account = new Manager();
						m_account->SetLoginMuneFn(std::bind(&Login::Show, this));
						m_account->Login();
					}
					if (b->Getname() == "user")
					{
						run = false;
						cleardevice();
						m_account = new User();
						m_account->SetLoginMuneFn(std::bind(&Login::Show, this));
						m_account->Login();
					}
					if (b->Getname() == "visit")
					{
						run = false;
						cleardevice();
						m_account = new Visit();
						m_account->SetLoginMuneFn(std::bind(&Login::Show, this));
						m_account->Login();
					}
					if (b->Getname() == "exit")
					{
						run = false;
						break;
					}
				}
			}
		}
	}
	return 0;
}
int Login::Init()
{
	//创建一个根目录，存放图书和论文
	File f;
	f.AddFolder("\\root");
	f.AddFolder("\\root\\Books");
	f.AddFolder("\\root\\Paper");
	setbkmode(TRANSPARENT);
	//初始化登录界面的按钮
	Button *b0=new Button(m_window->m_pros.Width/2-30, m_window->m_pros.Height/4-20, m_window->m_pros.Width / 2 + 30, m_window->m_pros.Height / 4+20,"manager");
	Button* b1 = new Button(m_window->m_pros.Width / 2 - 30, 2* m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 30, 2* m_window->m_pros.Height / 4 + 20, "user");
	Button* b2 = new Button(m_window->m_pros.Width / 2 - 30, 3* m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 30, 3* m_window->m_pros.Height / 4 + 20, "visit");
	Button* b3 = new Button(m_window->m_pros.Width / 2 - 30, 4* m_window->m_pros.Height / 4 - 40, m_window->m_pros.Width / 2 + 30, 4* m_window->m_pros.Height / 4, "exit");
	buttons.push_back(b0); buttons.push_back(b1); buttons.push_back(b2); buttons.push_back(b3);
	Show();
	return 0;
}


