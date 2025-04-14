#include"pch.h"
#include"Account.h"

Account::~Account()
{
	if (m_window != NULL)
	{
		delete m_window;
		m_window = nullptr;
	}
	if (errormsg != nullptr)
	{
		delete errormsg;
		errormsg = nullptr;
	}
}
void Manager::Login()
{
	//文本输入框
	TextBox tb(m_window->m_pros.Width/2-50,m_window->m_pros.Height/2-60,m_window->m_pros.Width/2+50,m_window->m_pros.Height/2-30,"账号");
	TextBox tb1(m_window->m_pros.Width / 2 - 50, m_window->m_pros.Height / 2, m_window->m_pros.Width / 2 + 50, m_window->m_pros.Height / 2 + 30, "密码");
	tb.Creat();
	tb1.Creat();
	//按钮
	Button b(m_window->m_pros.Width / 2 - 30, 3 * m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 30, 3 * m_window->m_pros.Height / 4 + 20, "登录");
	Button b1(m_window->m_pros.Width / 2 - 30,  m_window->m_pros.Height- 40, m_window->m_pros.Width / 2 + 30, m_window->m_pros.Height, "返回");
	b.Creat();
	b1.Creat();
	ExMessage msg;
	bool run = true;
	DataBase db;
	pqxx::result r;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					std::cout << b.Getname() << std::endl;
					m_account = tb.Gettext();
					m_password = tb1.Gettext();
					db.ChooseTable("ManagerAccount");
					std::string sql = "SELECT password FROM \""; sql += db.m_table; sql += "\" WHERE \"ManagerAccount\".account='"; sql += m_account; sql += "'";
					r=db.Select(sql);
					if (!r.empty())
					{
						if (m_password == r.front().front().c_str())
						{
							//std::cout << "密码为："<<m_password<<"登录成功" << std::endl;
							errormsg->SetMsg("登录成功！");
							cleardevice();
							Main();
							run = false;
							break;
					}
						else
						{
							//std::cout <<"密码错误" << std::endl;
							errormsg->SetMsg("密码错误！");
						}
					}
					else
					{
						//std::cout << "账号不存在！" << std::endl;
						errormsg->SetMsg("账号不存在！");
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
						std::cout << b1.Getname() << std::endl;
						m_loginmunefn();
						run = false;
						break;
				}
				if (tb.Check(msg.x, msg.y))
				{
					tb.OnMessage();
				}
				if (tb1.Check(msg.x, msg.y))
				{
					tb1.OnMessage(TB_PRIVATE);
				}

			}
		}
	}
}

void Manager::Main()
{
	//按钮
	Button b(m_window->m_pros.Width / 2 - 100,  m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100,  m_window->m_pros.Height / 6 + 20, "管理图书");
	Button b1(m_window->m_pros.Width / 2 - 100, 2*m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 2*m_window->m_pros.Height / 6 + 20, "管理论文");
	Button b2(m_window->m_pros.Width / 2 - 100, 3*m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 3*m_window->m_pros.Height / 6 + 20, "管理读者");
	Button b3(m_window->m_pros.Width / 2 - 100, 4*m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 4*m_window->m_pros.Height / 6 + 20, "管理信息");
	Button b4(m_window->m_pros.Width / 2 - 100, 5*m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 5*m_window->m_pros.Height / 6 + 20, "返回主界面");
	b.Creat(); b1.Creat(); b2.Creat(); b3.Creat(); b4.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				ManageBooks();
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				ManagePaper();
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				ManageReader();
				run = false;
				break;
			}
			if (b3.IsPressed(msg.x, msg.y))
			{
				std::cout << b3.Getname() << std::endl;
				ManageMessage();
				run = false;
				break;
			}
			if (b4.IsPressed(msg.x, msg.y))
			{
				std::cout << b4.Getname() << std::endl;
				m_loginmunefn();
				run = false;
				break;
			}
		}
	}
}

Manager::Manager()
{

}

void Manager::ManageBooks()
{
	//显示所有图书
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 6 + 20, "显示所有图书");
	//增删改查
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 6 + 20, "增加图书");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 6 + 20, "删除图书");
	Button b3(m_window->m_pros.Width / 2 - 100, 4 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 4 * m_window->m_pros.Height / 6 + 20, "修改图书");
	Button b4(m_window->m_pros.Width / 2 - 100, 5 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 5 * m_window->m_pros.Height / 6 + 20, "查找图书");
	Button b5(0, 0, 100, 20, "返回");
	b.Creat(); b1.Creat(); b2.Creat(); b3.Creat(); b4.Creat(); b5.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				cleardevice();
				ShowAll("Books");
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				Add("Books");
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				cleardevice();
				Delete("Books");
				run = false;
				break;
			}
			if (b3.IsPressed(msg.x, msg.y))
			{
				std::cout << b3.Getname() << std::endl;
				cleardevice();
				Update("Books");
				run = false;
				break;
			}
			if (b4.IsPressed(msg.x, msg.y))
			{
				std::cout << b4.Getname() << std::endl;
				cleardevice();
				Select("Books");
				run = false;
				break;
			}
			if (b5.IsPressed(msg.x, msg.y))
			{
				std::cout << b5.Getname() << std::endl;
				cleardevice();
				Main();
				run = false;
				break;
			}
		}
	}
}

void Manager::ManagePaper()
{
	//显示所有论文
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 6 + 20, "显示所有论文");
	//增删改查
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 6 + 20, "增加论文");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 6 + 20, "删除论文");
	Button b3(m_window->m_pros.Width / 2 - 100, 4 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 4 * m_window->m_pros.Height / 6 + 20, "修改论文");
	Button b4(m_window->m_pros.Width / 2 - 100, 5 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 5 * m_window->m_pros.Height / 6 + 20, "查找论文");
	Button b5(0, 0, 100, 20, "返回");
	b.Creat(); b1.Creat(); b2.Creat(); b3.Creat(); b4.Creat(); b5.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				cleardevice();
				ShowAll("Paper");
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				Add("Paper");
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				cleardevice();
				Delete("Paper");
				run = false;
				break;
			}
			if (b3.IsPressed(msg.x, msg.y))
			{
				std::cout << b3.Getname() << std::endl;
				cleardevice();
				Update("Paper");
				run = false;
				break;
			}
			if (b4.IsPressed(msg.x, msg.y))
			{
				std::cout << b4.Getname() << std::endl;
				cleardevice();
				Select("Paper");
				run = false;
				break;
			}
			if (b5.IsPressed(msg.x, msg.y))
			{
				std::cout << b5.Getname() << std::endl;
				cleardevice();
				Main();
				run = false;
				break;
			}
		}
	}
}

void Manager::ManageReader()
{
	//显示所有用户
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 6 + 20, "显示所有用户");
	//增删改查
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 6 + 20, "增加用户");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 6 + 20, "删除用户");
	Button b3(m_window->m_pros.Width / 2 - 100, 4 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 4 * m_window->m_pros.Height / 6 + 20, "修改用户");
	Button b4(m_window->m_pros.Width / 2 - 100, 5 * m_window->m_pros.Height / 6 - 20, m_window->m_pros.Width / 2 + 100, 5 * m_window->m_pros.Height / 6 + 20, "查找用户");
	Button b5(0, 0, 100, 20, "返回");
	b.Creat(); b1.Creat(); b2.Creat(); b3.Creat(); b4.Creat(); b5.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				cleardevice();
				ShowAll("UserAccount");
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				Add("UserAccount");
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				cleardevice();
				Delete("UserAccount");
				run = false;
				break;
			}
			if (b3.IsPressed(msg.x, msg.y))
			{
				std::cout << b3.Getname() << std::endl;
				cleardevice();
				Update("UserAccount");
				run = false;
				break;
			}
			if (b4.IsPressed(msg.x, msg.y))
			{
				std::cout << b4.Getname() << std::endl;
				cleardevice();
				Select("UserAccount");
				run = false;
				break;
			}
			if (b5.IsPressed(msg.x, msg.y))
			{
				std::cout << b5.Getname() << std::endl;
				cleardevice();
				Main();
				run = false;
				break;
			}
		}
	}
}

void Manager::ManageMessage()
{
	cleardevice();
	Button b =  Button(m_window->m_pros.Width / 2 - 120, m_window->m_pros.Height / 4, m_window->m_pros.Width / 2 + 120, m_window->m_pros.Height / 4+40, "查看借阅信息");
	Button b1=  Button(m_window->m_pros.Width / 2 - 120, 2*m_window->m_pros.Height / 4, m_window->m_pros.Width / 2 + 120, 2*m_window->m_pros.Height / 4+40, "查看下载信息");
	Button b2=  Button(m_window->m_pros.Width / 2 - 120,3*m_window->m_pros.Height / 4, m_window->m_pros.Width / 2 + 120, 3*m_window->m_pros.Height / 4+40, "返回");
	b.Creat(); b1.Creat(); b2.Creat();
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					ShowAll("BooksMsg");
					break;
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					ShowAll("PaperMsg");
					break;
				}
				if (b2.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					Main();
					break;
				}
			}
		}
	}
}

void Manager::Add(const std::string&tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int row = r.size();//属性数量
	int height = m_window->m_pros.Height /( 2 * (row + 1));
	std::vector<TextBox*>textboxs;
	for (int i = 0; i < r.size(); i++)
	{
		TextBox* t = new TextBox(m_window->m_pros.Width/2-100,(2*i+1)*height,m_window->m_pros.Width/2+100,(2*i+2)*height,r[i].front().c_str());
		textboxs.push_back(t);
	}
	//文本框
	for (TextBox* t : textboxs)
	{
		t->Creat();
	}
	//按钮（返回，添加）
	Button b = Button(m_window->m_pros.Width/2 - 40, m_window->m_pros.Height - height, m_window->m_pros.Width/2 + 40, m_window->m_pros.Height, "添加");
	Button b1 = Button(0, 0, 30, height/2, "返回");
	b.Creat(); b1.Creat();
	//错误信息框
	Message m = Message(0, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height);
	std::string name, author;
	ExMessage msg;
	bool run = true;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (TextBox* t : textboxs)
				{
					if (t->Check(msg.x, msg.y))
					{
						t->OnMessage();
					}
				}
				if (b.IsPressed(msg.x, msg.y))
				{
					for (TextBox* t : textboxs)
					{
						if (t->Getname() == "name")
						{
							name = t->Gettext();
						}
						if (t->Getname() == "author")
						{
							author = t->Gettext();
						}
					}
					//判断是否存在，用名字和作者作为键值（需优化）
					sql = "SELECT * FROM "; sql += "\""; sql += tablename; sql += "\""; sql += " WHERE name='"; sql += name; sql += "' AND author='"; sql += author; sql += "'";
					r=db.Select(sql);
					if (r.empty())
					{
						//不存在该数据，可插入
						std::string column, values,sql1,column1,values1;
						bool not_null = false;
						for (TextBox* t : textboxs)
						{
							column += t->Getname(); column += ",";
							values += "'"; values += t->Gettext(); values += "',";
							not_null |= !t->Gettext().empty();
						}
						column.pop_back(); values.pop_back();
						//插入到图书借阅表中
						if (tablename == "Books") {
							column1 = textboxs[0]->Getname(); column1 += ","; column1 += textboxs[1]->Getname();
							values1 = "'"; values1 += textboxs[0]->Gettext(); values1 += "','"; values1 += textboxs[1]->Gettext(); values1 += "'";
						}
						//std::cout << sql << std::endl;
						if (not_null) {
							sql = "INSERT INTO "; sql += "\""; sql += tablename; sql += "\"("; sql += column; sql += ") VALUES("; sql += values; sql += ")";
							if (db.Insert(sql))
							{
								m.SetMsg("添加成功!");
								if (tablename == "Books") {
									sql1 = "INSERT INTO "; sql1 += "\""; sql1 += "BorrowBooks"; sql1 += "\"("; sql1 += column1; sql1 += ") VALUES("; sql1 += values1; sql1 += ")";
									db.Insert(sql1);
								}
								//添加成功则创建文件
								if (tablename == "Books" || tablename == "Paper")
								{
									File f;
									std::string str = "\\root\\"; str += tablename; str += "\\"; str += name; str += "-"; str += author; str += ".txt";
									f.Add(str);
								}
								//成功后退出界面
								Sleep(500);
								cleardevice();
								if (tablename == "Books")
								{
									ManageBooks();
								}
								if (tablename == "Paper")
								{
									ManagePaper();
								}
								if (tablename == "UserAccount")
								{
									ManageReader();
								}
								run = false;
								break;
							}
							else
							{
								m.SetMsg("添加失败");
							}
						}
						else
						{
							m.SetMsg("添加失败，请输入数据！");
						}
					}
					else
					{
						//存在数据，不可插入
						m.SetMsg("添加失败，数据已存在");
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					if (tablename == "Books")
					{
						ManageBooks();
					}
					if (tablename == "Paper")
					{
						ManagePaper();
					}
					if (tablename == "UserAccount")
					{
						ManageReader();
					}
					run = false;
					break;
				}
			}
		}
	}
	//释放空间
	for (TextBox* t : textboxs)
	{
		delete t;
		t = nullptr;
	}
}

void Manager::Delete(const std::string& tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*> buttons;
	for (int i = 0; i < r.size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
		columns.push_back(m);
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += tablename; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小

	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 40, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
				messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		bool run1 = true;
		while (run1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					if (tablename == "Books")
					{
						ManageBooks();
					}
					if (tablename == "Paper")
					{
						ManagePaper();
					}
					if (tablename == "UserAccount")
					{
						ManageReader();
					}
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						pqxx::row m_row = r[i];
						cleardevice();
						Delete1(tablename, m_row);
						run = false;
						run1 = false;
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void Manager::Delete1(const std::string& tablename,const pqxx::row&r)
{
	std::vector<Message*>culomn;
	std::vector<Message*>values;
	int width = (m_window->m_pros.Width - 40) / r.size();
	int height = m_window->m_pros.Height / 12;
	int count = 0;
	for (int i = 0; i < r.size(); i++)
	{
		if (!r[i].is_null())
		{
			count++;
		}
		Message* m = new Message(i*width+20, 0,(i+1)*width+20,height,r[i].name());
		Message* m1 = new Message(i * width + 20, height, (i + 1) * width + 20, 2*height, r[i].c_str());
		culomn.push_back(m);
		values.push_back(m1);
		culomn[i]->Creat();
		values[i]->Creat();
	}
	Button b = Button(m_window->m_pros.Width/2-200,2*m_window->m_pros.Height/3,m_window->m_pros.Width/2-120,2*m_window->m_pros.Height/3+height,"删除");
	Button b1 = Button(m_window->m_pros.Width / 2 +  120, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 +200, 2 * m_window->m_pros.Height / 3 + height, "返回");
	b.Creat(); b1.Creat();
	//信息提示
	Message m = Message(0,m_window->m_pros.Height-height,m_window->m_pros.Width,m_window->m_pros.Height);
	std::string sql;
	bool is_ok = true;
	DataBase db;
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					std::cout << b.Getname() << std::endl;
					//加一个判断，如果书本被借出，则无法删除
					sql = "SELECT borrower FROM \"BorrowBooks\" WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
					pqxx::result res = db.Select(sql);
					sql = "DELETE FROM \""; sql += tablename; sql += "\" WHERE ";
					for (int i = 0; i < r.size(); i++)
					{

						if (!r[i].is_null()) {
							sql += r[i].name(); sql += "="; sql += "'"; sql += r[i].c_str(); sql += "'";sql += " AND ";
						}
					}
					if (count)
					{
						sql = sql.substr(0, sql.length() - 5);
					}
					std::cout << sql << std::endl;
					if (tablename != "Books" || res.front().front().is_null()) {
						if (db.Delete(sql))
						{
							m.SetMsg("删除成功！");
							//从借阅信息中删除
							if (tablename == "Books")
							{
								std::string s, s1;
								s = "DELETE FROM \"BorrowBooks\" WHERE name='"; s += r[0].c_str(); s += "' AND author='"; s += r[1].c_str(); s += "'";
								s1 = "DELETE FROM \"BooksMsg\" WHERE name='"; s1 += r[0].c_str(); s1 += "' AND author='"; s1 += r[1].c_str(); s1 += "'";
								if (db.Delete(s))
								{
									std::cout << "借阅表中删除成功" << std::endl;
								}
								else
								{
									std::cout << "借阅表中删除失败" << std::endl;
								}
								if (db.Delete(s1))
								{
									std::cout << "借阅信息中删除成功" << std::endl;
								}
								else
								{
									std::cout << "借阅信息中删除失败" << std::endl;
								}
							}
							//删除成功则删除文件,前两项为键值
							if (tablename == "Books" || tablename == "Paper")
							{
								File f;
								std::string str = "\\root\\"; str += tablename; str += "\\"; str += r[0].c_str(); str += "-"; str += r[1].c_str(); str += ".txt";
								f.Delete(str);
							}
							Sleep(500);
							cleardevice();
							Delete(tablename);
							break;
						}
						else
						{
							m.SetMsg("删除失败！");
						}
					}
					else
					{
						m.SetMsg("删除失败，图书被借出！");
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					std::cout << b1.Getname() << std::endl;
					cleardevice();
					Delete(tablename);
					break;
				}
			}
		}
	}
	//释放空间
	for (int i = 0; i < r.size(); i++)
	{
		delete culomn[i]; culomn[i] = nullptr;
		delete values[i]; values[i] = nullptr;
	}
}

void Manager::Update(const std::string& tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*> buttons;
	for (int i = 0; i < r.size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
		columns.push_back(m);
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += tablename; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小

	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 40, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
				messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		bool run1 = true;
		while (run1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					if (tablename == "Books")
					{
						ManageBooks();
					}
					if (tablename == "Paper")
					{
						ManagePaper();
					}
					if (tablename == "UserAccount")
					{
						ManageReader();
					}
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						pqxx::row m_row = r[i];
						cleardevice();
						Update1(tablename, m_row);
						run = false;
						run1 = false;
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void Manager::Update1(const std::string& tablename, const pqxx::row& r)
{
	std::vector<Message*>culomn;
	std::vector<Message*>values;
	std::vector<TextBox*>newvalues;
	int width = (m_window->m_pros.Width - 40) / r.size();
	int height = m_window->m_pros.Height / 12;
	int count = 0;
	for (int i = 0; i < r.size(); i++)
	{
		if (!r[i].is_null())
		{
			count++;
		}
		Message* m = new Message(i * width + 20, 0, (i + 1) * width + 20, height, r[i].name());
		Message* m1 = new Message(i * width + 20, height, (i + 1) * width + 20, 2 * height, r[i].c_str());
		TextBox* t = new TextBox(i * width + 20, 2 * height, (i + 1) * width + 20, 3 * height, r[i].name());
		culomn.push_back(m);
		values.push_back(m1);
		newvalues.push_back(t);
		culomn[i]->Creat();
		values[i]->Creat();
		newvalues[i]->Creat();
	}
	Button b = Button(m_window->m_pros.Width / 2 - 200, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 - 120, 2 * m_window->m_pros.Height / 3 + height, "更新");
	Button b1 = Button(m_window->m_pros.Width / 2 + 120, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 + 200, 2 * m_window->m_pros.Height / 3 + height, "返回");
	b.Creat(); b1.Creat();
	//信息提示
	Message m = Message(0, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height);
	std::string sql;
	DataBase db;
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					std::cout << b.Getname() << std::endl;
					sql = "UPDATE \""; sql += tablename; sql += "\" SET ";
					for (int i = 0; i < r.size(); i++)
					{

						sql += r[i].name(); sql += "="; sql += "'"; 
						//未更新则保留原有数据
						if (newvalues[i]->Gettext().empty())
						{
							sql += values[i]->Getmsg();
						}
						else
						{
							sql += newvalues[i]->Gettext();
						}
						sql += "'";
						if (i != r.size() - 1)
						{
							sql += ",";
						}
					}
					sql += " WHERE ";
					for (int i = 0; i < r.size(); i++)
					{
						if (!r[i].is_null()) {
							sql += r[i].name(); sql += "="; sql += "'"; sql += r[i].c_str(); sql += "'"; sql += " AND ";
						}
					}
					if (count)
					{
						sql = sql.substr(0, sql.length() - 5);
					}
					std::cout << sql << std::endl;


					//判断更新后的数据是否存在
					std::string sql1 = "SELECT * FROM \""; sql1 += tablename; sql1 += "\" WHERE ";
					sql1 += r[0].name(); sql1 += "="; sql1 += "'";
					//未更新则保留原有数据
					if (newvalues[0]->Gettext().empty())
					{
						sql1 += values[0]->Getmsg();
					}
					else
					{
						sql1 += newvalues[0]->Gettext();
					}
					sql1 += "'";
					sql1 += " AND ";
					sql1 += r[1].name(); sql1 += "="; sql1 += "'";
					//未更新则保留原有数据
					if (newvalues[1]->Gettext().empty())
					{
						sql1 += values[1]->Getmsg();
					}
					else
					{
						sql1 += newvalues[1]->Gettext();
					}
					sql1 += "'";
					std::cout << sql1 << std::endl;
					pqxx::result res = db.Select(sql1);

					//没有数据
					if (res.empty()) {
						if (db.Update(sql))
						{
							m.SetMsg("更新成功！");
							//更新成功后在借阅表中同步更新
							if (tablename == "Books")
							{
								std::string s, s1;
								s = "UPDATE \"BorrowBooks\" SET name='";
								if (newvalues[0]->Gettext().empty())
								{
									s += values[0]->Getmsg();
								}
								else
								{
									s += newvalues[0]->Gettext();
								}
								s += "',author='";
								if (newvalues[1]->Gettext().empty())
								{
									s += values[1]->Getmsg();
								}
								else
								{
									s += newvalues[1]->Gettext();
								}
								s += "' WHERE name='"; s += r[0].c_str(); s += "' AND author='"; s += r[1].c_str(); s += "'";
								s1 = "UPDATE \"BooksMsg\" SET name='";
								if (newvalues[0]->Gettext().empty())
								{
									s1 += values[0]->Getmsg();
								}
								else
								{
									s1 += newvalues[0]->Gettext();
								}
								s1 += "',author='";
								if (newvalues[1]->Gettext().empty())
								{
									s1 += values[1]->Getmsg();
								}
								else
								{
									s1 += newvalues[1]->Gettext();
								}
								s1+= "' WHERE name='"; s1 += r[0].c_str(); s1 += "' AND author='"; s1 += r[1].c_str(); s1 += "'";
								if (db.Update(s))
								{
									std::cout << "更新借阅表成功！" << std::endl;
								}
								if (db.Update(s1))
								{
									std::cout << "更新借阅信息成功！" << std::endl;
								}
							}

							if (tablename == "Books" || tablename == "Paper")
							{
								//发生改变才更新文件
								if (newvalues[0]->Gettext() != values[0]->Getmsg() || newvalues[1]->Gettext() != values[1]->Getmsg()) {
									File f;
									std::string oldfile = "\\root\\"; oldfile += tablename; oldfile += "\\"; oldfile += values[0]->Getmsg(); oldfile += "-"; oldfile += values[1]->Getmsg(); oldfile += ".txt";
									std::string newfile = "\\root\\"; newfile += tablename; newfile += "\\";
									if (!newvalues[0]->Gettext().empty()) {
										newfile += newvalues[0]->Gettext();
									}
									else
									{
										newfile += values[0]->Getmsg();
									}
									newfile += "-";
									if (!newvalues[1]->Gettext().empty()) {
										newfile += newvalues[1]->Gettext();
									}
									else
									{
										newfile += values[1]->Getmsg();
									}
									newfile += ".txt";
									f.Update(oldfile, newfile);
								}
							}
							Sleep(500);
							cleardevice();
							Update(tablename);
							break;
						}
						else
						{
							m.SetMsg("更新失败！");
						}
					}
					else
					{
						m.SetMsg("更新失败，更新后数据已存在！");
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					std::cout << b1.Getname() << std::endl;
					cleardevice();
					Update(tablename);
					break;
				}
				for (TextBox* t : newvalues)
				{
					if (t->Check(msg.x, msg.y))
					{
						t->OnMessage();
					}
				}
			}
		}
	}
	//释放空间
	for (int i = 0; i < r.size(); i++)
	{
		delete culomn[i]; culomn[i] = nullptr;
		delete values[i]; values[i] = nullptr;
		delete newvalues[i]; newvalues[i] = nullptr;
	}
}

void Manager::Select(const std::string& tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int height =  m_window->m_pros.Height / (4 * r.size());
	std::vector<TextBox*>textboxs;
	for (int i = 0; i < r.size(); i++)
	{
		TextBox* t = new TextBox(m_window->m_pros.Width / 2 - 100, (2*i + 1) * height, m_window->m_pros.Width / 2 + 100, (2*i + 2) * height, r[i].front().c_str());
		textboxs.push_back(t);
		t->Creat();
	}
	Button b = Button(m_window->m_pros.Width / 2 - 200,(2*r.size()+2)*height, m_window->m_pros.Width / 2 - 120, (2 * r.size() + 3) * height,"查找");
	Button b1= Button(m_window->m_pros.Width / 2 +120, (2 * r.size() + 2) * height, m_window->m_pros.Width / 2 +200, (2 * r.size() + 3) * height, "返回");
	b.Creat(); b1.Creat();
	Message error = Message(0, (2 * r.size() + 3) * height, m_window->m_pros.Width, m_window->m_pros.Height);
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			for (TextBox* t : textboxs)
			{
				if (t->Check(msg.x, msg.y))
				{
					t->OnMessage();
				}
			}
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				sql = "SELECT * FROM \""; sql += tablename; sql += "\" WHERE ";
				bool is_null = true;
				for (int i = 0; i < textboxs.size(); i++)
				{
					if (!textboxs[i]->Gettext().empty())
					{
						sql += r[i].front().c_str(); sql += "="; sql += "'"; sql += textboxs[i]->Gettext(); sql += "'"; sql += " AND ";
						is_null = false;
					}
				}
				//有数据输入
				if (!is_null)
				{
					sql = sql.substr(0, sql.length() - 5);
					std::cout << sql << std::endl;
					r = db.Select(sql);
					cleardevice();
					ShowAll(tablename,r);					
					run = false;
					break;
				}
				else
				{
					error.SetMsg("请输入内容！");
				}
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				if (tablename == "Books")
				{
					ManageBooks();
				}
				if (tablename == "Paper")
				{
					ManagePaper();
				}
				if (tablename == "UserAccount")
				{
					ManageReader();
				}
				run = false;
				break;
			}
		}
	}
	//释放空间
	for (TextBox* t : textboxs)
	{
		delete t;
		t = nullptr;
	}
}

void Manager::ShowAll(const std::string& tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*>buttons;
	if (tablename == "BooksMsg" || tablename == "PaperMsg")
	{
		for (int i = 0; i < r.size(); i++)
		{
			if (i !=r.size()-1) {
				Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i+1].front().c_str());
				columns.push_back(m);
			}
			else
			{
				Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[0].front().c_str());
				columns.push_back(m);
			}
		}
	}
	else 
	{
		for (int i = 0; i < r.size(); i++)
		{
			Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
			columns.push_back(m);
		}
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += tablename; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小

	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0; 
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
					Message* m = new Message(20 + j%column * width, (i%10+1) * height, 20 + (j %column+ 1) * width, (i%10 + 2) * height, r[i][j].c_str());
					messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
	 }
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}

			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0,m_window->m_pros.Height-height,width/2,m_window->m_pros.Height,"上一页");
		Button next(m_window->m_pros.Width-width/2, m_window->m_pros.Height - height,m_window->m_pros.Width,m_window->m_pros.Height,"下一页");
		Button exit(m_window->m_pros.Width/2-width/4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height,"返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		while (1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					if (tablename == "Books")
					{
						ManageBooks();
					}
					if (tablename == "Paper")
					{
						ManagePaper();
					}
					if (tablename == "UserAccount")
					{
						ManageReader();
					}
					if (tablename == "BooksMsg" || tablename == "PaperMsg")
					{
						ManageMessage();
					}
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						//打开对应文件
						if (tablename == "Books" || tablename == "Paper")
						{
							File f;
							std::string str = "\\root\\"; str += tablename; str += "\\"; str += buttons[i]->Getname(); str += "-"; str +=messages[i*column+1]->Getmsg(); str += ".txt";
							f.Open(str);
						}
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void Manager::ShowAll(const std::string& tablename,const pqxx::result& res)
{
	int column = res.front().size();
	int width = (m_window->m_pros.Width - 40) / res.front().size();
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*>buttons;
	for (int i = 0; i < res.front().size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, res.front()[i].name());
		columns.push_back(m);
	}
	Message empty = Message(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!res.empty())
	{
		if (res.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = res.size() / 10 + (bool)(res.size() % 10);
		}
		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, res[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, res[i][j].c_str());
				messages.push_back(m);
			}
		}
	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (res.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}
		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		while (1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					if (tablename == "Books")
					{
						ManageBooks();
					}
					if (tablename == "Paper")
					{
						ManagePaper();
					}
					if (tablename == "UserAccount")
					{
						ManageReader();
					}
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						//打开对应文件
						if (tablename == "Books" || tablename == "Paper")
						{
							File f;
							std::string str = "\\root\\"; str += tablename; str += "\\"; str += buttons[i]->Getname(); str += "-"; str += messages[i * column + 1]->Getmsg(); str += ".txt";
							f.Open(str,false);
						}
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void User::Login()
{
	//文本输入框
	TextBox tb(m_window->m_pros.Width / 2 - 50, m_window->m_pros.Height / 2 - 60, m_window->m_pros.Width / 2 + 50, m_window->m_pros.Height / 2 - 30, "账号");
	TextBox tb1(m_window->m_pros.Width / 2 - 50, m_window->m_pros.Height / 2, m_window->m_pros.Width / 2 + 50, m_window->m_pros.Height / 2 + 30, "密码");
	tb.Creat();
	tb1.Creat();
	//按钮
	Button b(m_window->m_pros.Width / 2 - 30, 3 * m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 30, 3 * m_window->m_pros.Height / 4 + 20, "登录");
	Button b1(m_window->m_pros.Width / 2 - 30, m_window->m_pros.Height - 40, m_window->m_pros.Width / 2 + 30, m_window->m_pros.Height, "返回");
	b.Creat();
	b1.Creat();
	ExMessage msg;
	bool run = true;
	DataBase db;
	pqxx::result r;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					std::cout << b.Getname() << std::endl;
					m_account = tb.Gettext();
					m_password = tb1.Gettext();
					db.ChooseTable("UserAccount");
					std::string sql = "SELECT password FROM \""; sql += db.m_table; sql += "\" WHERE \"UserAccount\".account='"; sql += m_account; sql += "'";
					r = db.Select(sql);
					if (!r.empty())
					{
						if (m_password == r.front().front().c_str())
						{
							//std::cout << "密码为："<<m_password<<"登录成功" << std::endl;
							errormsg->SetMsg("登录成功！");
							//登录成功则创建目录
							File f;
							std::string root = m_account; root += "-"; root += m_password;
							f.AddFolder("\\" + root);
							f.AddFolder("\\" + root + "\\Books");
							f.AddFolder("\\" + root + "\\Paper");
							cleardevice();
							Main();
							run = false;
							break;
						}
						else
						{
							//std::cout <<"密码错误" << std::endl;
							errormsg->SetMsg("密码错误！");
						}
					}
					else
					{
						//std::cout << "账号不存在！" << std::endl;
						errormsg->SetMsg("账号不存在！");
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					std::cout << b1.Getname() << std::endl;
					m_loginmunefn();
					run = false;
					break;
				}
				if (tb.Check(msg.x, msg.y))
				{
					tb.OnMessage();
				}
				if (tb1.Check(msg.x, msg.y))
				{
					tb1.OnMessage(TB_PRIVATE);
				}

			}
		}
	}
}

void User::Main()
{
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 4 + 20, "图书操作");
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 4 + 20, "论文操作");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 4 + 20, "返回主界面");
	b.Creat(); b1.Creat(); b2.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				cleardevice();
				ManageBooks();
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				ManagePaper();
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				cleardevice();
				m_loginmunefn();
				run = false;
				break;
			}

		}
	}
}

User::User()
{

}

void User::ManageBooks()
{
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 5 + 20, "查询图书");
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 5 + 20, "借阅图书");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 5 + 20, "归还图书");
	Button b3(m_window->m_pros.Width / 2 - 100, 4 * m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, 4 * m_window->m_pros.Height / 5 + 20, "返回");
	b.Creat(); b1.Creat(); b2.Creat(); b3.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				cleardevice();
				Select("Books");
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				BorrowBooks();
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				ReturnBooks();
				run = false;
				break;
			}
			if (b3.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				cleardevice();
				Main();
				run = false;
				break;
			}

		}
	}
}

void User::ManagePaper()
{
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 5 + 20, "查询论文");
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 5 + 20, "上传论文");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 5 + 20, "下载论文");
	Button b3(m_window->m_pros.Width / 2 - 100, 4 * m_window->m_pros.Height / 5 - 20, m_window->m_pros.Width / 2 + 100, 4 * m_window->m_pros.Height / 5 + 20, "返回");
	b.Creat(); b1.Creat(); b2.Creat(); b3.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				cleardevice();
				Select("Paper");
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				UploadPaper();
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				DownloadPaper();
				run = false;
				break;
			}
			if (b3.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				cleardevice();
				Main();
				run = false;
				break;
			}

		}
	}
}

void User::Select(const std::string& tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int height = m_window->m_pros.Height / (4 * r.size());
	std::vector<TextBox*>textboxs;
	for (int i = 0; i < r.size(); i++)
	{
		TextBox* t = new TextBox(m_window->m_pros.Width / 2 - 100, (2 * i + 1) * height, m_window->m_pros.Width / 2 + 100, (2 * i + 2) * height, r[i].front().c_str());
		textboxs.push_back(t);
		t->Creat();
	}
	Button b = Button(m_window->m_pros.Width / 2 - 200, (2 * r.size() + 2) * height, m_window->m_pros.Width / 2 - 120, (2 * r.size() + 3) * height, "查找");
	Button b1 = Button(m_window->m_pros.Width / 2 + 120, (2 * r.size() + 2) * height, m_window->m_pros.Width / 2 + 200, (2 * r.size() + 3) * height, "返回");
	b.Creat(); b1.Creat();
	Message error = Message(0, (2 * r.size() + 3) * height, m_window->m_pros.Width, m_window->m_pros.Height);
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			for (TextBox* t : textboxs)
			{
				if (t->Check(msg.x, msg.y))
				{
					t->OnMessage();
				}
			}
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				sql = "SELECT * FROM \""; sql += tablename; sql += "\" WHERE ";
				bool is_null = true;
				for (int i = 0; i < textboxs.size(); i++)
				{
					if (!textboxs[i]->Gettext().empty())
					{
						sql += r[i].front().c_str(); sql += "="; sql += "'"; sql += textboxs[i]->Gettext(); sql += "'"; sql += " AND ";
						is_null = false;
					}
				}
				//有数据输入
				if (!is_null)
				{
					sql = sql.substr(0, sql.length() - 5);
					std::cout << sql << std::endl;
					r = db.Select(sql);
					cleardevice();
					ShowAll(tablename, r);
					run = false;
					break;
				}
				else
				{
					error.SetMsg("请输入内容！");
				}
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				cleardevice();
				if (tablename == "Books")
				{
					ManageBooks();
				}
				if (tablename == "Paper")
				{
					ManagePaper();
				}
				run = false;
				break;
			}
		}
	}
	//释放空间
	for (TextBox* t : textboxs)
	{
		delete t;
		t = nullptr;
	}
}

void User::ShowAll(const std::string& tablename, const pqxx::result& res)
{
	int column = res.front().size();
	int width = (m_window->m_pros.Width - 40) / res.front().size();
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*>buttons;
	for (int i = 0; i < res.front().size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, res.front()[i].name());
		columns.push_back(m);
	}
	Message empty = Message(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!res.empty())
	{
		if (res.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = res.size() / 10 + (bool)(res.size() % 10);
		}
		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, res[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, res[i][j].c_str());
				messages.push_back(m);
			}
		}
	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (res.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}
		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		while (1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					if (tablename == "Books")
					{
						ManageBooks();
					}
					if (tablename == "Paper")
					{
						ManagePaper();
					}
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						//打开对应文件
						if (tablename == "Books" || tablename == "Paper")
						{
							File f;
							std::string str = "\\root\\"; str += tablename; str += "\\"; str += buttons[i]->Getname(); str += "-"; str += messages[i * column + 1]->Getmsg(); str += ".txt";
							f.Open(str, false);
						}
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void User::BorrowBooks()
{
	DataBase db;
	std::string tablename = "Books";
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*> buttons;
	for (int i = 0; i < r.size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
		columns.push_back(m);
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += tablename; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小
	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 40, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
				messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		bool run1 = true;
		while (run1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
                    ManageBooks();
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						pqxx::row m_row = r[i];
						cleardevice();
						Borrow(m_row);
						run = false;
						run1 = false;
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void User::Borrow(const pqxx::row& r)
{
	std::vector<Message*>culomn;
	std::vector<Message*>values;
	int width = (m_window->m_pros.Width - 40) / r.size();
	int height = m_window->m_pros.Height / 12;
	int count = 0;
	for (int i = 0; i < r.size(); i++)
	{
		if (!r[i].is_null())
		{
			count++;
		}
		Message* m = new Message(i * width + 20, 0, (i + 1) * width + 20, height, r[i].name());
		Message* m1 = new Message(i * width + 20, height, (i + 1) * width + 20, 2 * height, r[i].c_str());
		culomn.push_back(m);
		values.push_back(m1);
		culomn[i]->Creat();
		values[i]->Creat();
	}
	Button b = Button(m_window->m_pros.Width / 2 - 200, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 - 120, 2 * m_window->m_pros.Height / 3 + height, "借阅");
	Button b1 = Button(m_window->m_pros.Width / 2 + 120, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 + 200, 2 * m_window->m_pros.Height / 3 + height, "返回");
	b.Creat(); b1.Creat();
	//信息提示
	Message m = Message(0, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height);
	std::string sql;
	DataBase db;
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					std::cout << b.Getname() << std::endl;
					//从借阅表中查找
					sql = "SELECT borrower FROM \"BorrowBooks\" WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
					pqxx::result res = db.Select(sql);
					//为空则代表可以借阅
					if (res.front().front().is_null())
					{
						sql = "UPDATE \"BorrowBooks\" SET borrower='"; sql += m_account; sql += "' WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
						if (db.Update(sql))
						{
							m.SetMsg("借阅成功！");
							//借阅成功则添加借阅次数到借阅信息表
							sql = "SELECT * FROM \"BooksMsg\" WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
							res = db.Select(sql);
							//为空则说明第一次借阅，将该数据插入到表中
							if (res.empty())
							{
								sql = "INSERT INTO \"BooksMsg\" VALUES('"; sql += r[0].c_str(); sql += "','"; sql += r[1].c_str(); sql += "',1)";
								if (db.Insert(sql))
								{
									std::cout << "插入借阅次数表成功！" << std::endl;
								}
								else
								{
									std::cout << "插入借阅次数表失败！" << std::endl;
								}
							}
							//不为空则更新即可
							else
							{
								sql = "UPDATE \"BooksMsg\" SET number=number+1 WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
								if (db.Update(sql))
								{
									std::cout << "更新借阅次数表成功！" << std::endl;
								}
								else
								{
									std::cout << "更新借阅次数表失败！" << std::endl;
								}
							}
							Sleep(500);
							cleardevice();
							BorrowBooks();
							break;
						}
						else
						{
							m.SetMsg("借阅失败！");
						}
					}
					else
					{
						m.SetMsg("借阅失败，该图书已被借出！");
					}
				
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					std::cout << b1.Getname() << std::endl;
					cleardevice();
					BorrowBooks();
					break;
				}
			}
		}
	}
	//释放空间
	for (int i = 0; i < r.size(); i++)
	{
		delete culomn[i]; culomn[i] = nullptr;
		delete values[i]; values[i] = nullptr;
	}
}

void User::ReturnBooks()
{
	DataBase db;
	std::string tablename = "Books";
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*> buttons;
	for (int i = 0; i < r.size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
		columns.push_back(m);
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += tablename; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小

	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 40, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
				messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		bool run1 = true;
		while (run1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					ManageBooks();
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						pqxx::row m_row = r[i];
						cleardevice();
						Return(m_row);
						run = false;
						run1 = false;
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void User::Return(const pqxx::row&r)
{
	std::vector<Message*>culomn;
	std::vector<Message*>values;
	int width = (m_window->m_pros.Width - 40) / r.size();
	int height = m_window->m_pros.Height / 12;
	int count = 0;
	for (int i = 0; i < r.size(); i++)
	{
		if (!r[i].is_null())
		{
			count++;
		}
		Message* m = new Message(i * width + 20, 0, (i + 1) * width + 20, height, r[i].name());
		Message* m1 = new Message(i * width + 20, height, (i + 1) * width + 20, 2 * height, r[i].c_str());
		culomn.push_back(m);
		values.push_back(m1);
		culomn[i]->Creat();
		values[i]->Creat();
	}
	Button b = Button(m_window->m_pros.Width / 2 - 200, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 - 120, 2 * m_window->m_pros.Height / 3 + height, "归还");
	Button b1 = Button(m_window->m_pros.Width / 2 + 120, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 + 200, 2 * m_window->m_pros.Height / 3 + height, "返回");
	b.Creat(); b1.Creat();
	//信息提示
	Message m = Message(0, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height);
	std::string sql;
	DataBase db;
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					std::cout << b.Getname() << std::endl;
					//从借阅表中查找
					sql = "SELECT borrower FROM \"BorrowBooks\" WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
					pqxx::result res = db.Select(sql);
					//不为空则代表可以归还
					if (!res.front().front().is_null())
					{
						if (m_account == res.front().front().c_str()) {
							sql = "UPDATE \"BorrowBooks\" SET borrower=NULL"; sql += " WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
							if (db.Update(sql))
							{
								m.SetMsg("归还成功！");
								Sleep(500);
								cleardevice();
								ReturnBooks();
								break;
							}
							else
							{
								m.SetMsg("归还失败！");
							}
						}
						else
						{
							m.SetMsg("归还失败，未借阅该图书");
						}
					}
					else
					{
						m.SetMsg("归还失败，该图书已归还！");
					}

				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					std::cout << b1.Getname() << std::endl;
					cleardevice();
					ReturnBooks();
					break;
				}
			}
		}
	}
	//释放空间
	for (int i = 0; i < r.size(); i++)
	{
		delete culomn[i]; culomn[i] = nullptr;
		delete values[i]; values[i] = nullptr;
	}
}

void User::UploadPaper()
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name='Paper'";
	pqxx::result r = db.Select(sql);
	int row = r.size();//属性数量
	int height = m_window->m_pros.Height / (2 * (row + 1));
	std::vector<TextBox*>textboxs;
	for (int i = 0; i < r.size(); i++)
	{
		TextBox* t = new TextBox(m_window->m_pros.Width / 2 - 100, (2 * i + 1) * height, m_window->m_pros.Width / 2 + 100, (2 * i + 2) * height, r[i].front().c_str());
		textboxs.push_back(t);
	}
	//文本框
	for (TextBox* t : textboxs)
	{
		t->Creat();
	}
	//按钮（返回，添加）
	Button b = Button(m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + 40, m_window->m_pros.Height, "上传");
	Button b1 = Button(0, 0, 30, height / 2, "返回");
	b.Creat(); b1.Creat();
	//错误信息框
	Message m = Message(0, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height);
	std::string name, author;
	ExMessage msg;
	bool run = true;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (TextBox* t : textboxs)
				{
					if (t->Check(msg.x, msg.y))
					{
						t->OnMessage();
					}
				}
				if (b.IsPressed(msg.x, msg.y))
				{
					for (TextBox* t : textboxs)
					{
						if (t->Getname() == "name")
						{
							name = t->Gettext();
						}
						if (t->Getname() == "author")
						{
							author = t->Gettext();
						}
					}
					//判断是否存在，用名字和作者作为键值（需优化）
					sql = "SELECT * FROM \"Paper\" WHERE name='"; sql += name; sql += "' AND author='"; sql += author; sql += "'";
					r = db.Select(sql);
					if (r.empty())
					{
						//不存在该数据，可插入
						std::string column, values;
						bool not_null = false;
						for (TextBox* t : textboxs)
						{
							column += t->Getname(); column += ",";
							values += "'"; values += t->Gettext(); values += "',";
							not_null |= !t->Gettext().empty();
						}
						column.pop_back(); values.pop_back();
						std::cout << sql << std::endl;
						if (not_null) {
							sql = "INSERT INTO "; sql += "\""; sql += "Paper"; sql += "\"("; sql += column; sql += ") VALUES("; sql += values; sql += ")";
							std::string papername = name; papername += "-"; papername += author; papername += ".txt";
							cleardevice();
							Upload(sql,papername);
							run = false;
							break;
						}
						else
						{
							m.SetMsg("添加失败，请输入数据！");
						}
					}
					else
					{
						//存在数据，不可插入
						m.SetMsg("上传失败，论文已存在");
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					ManagePaper();
					run = false;
					break;
				}
			}
		}
	}
	//释放空间
	for (TextBox* t : textboxs)
	{
		delete t;
		t = nullptr;
	}
}

void User::Upload(const std::string& sql,const std::string& name)
{
	TextBox t = TextBox(0, m_window->m_pros.Height / 3, m_window->m_pros.Width, m_window->m_pros.Height / 3 + 40, "文件路径");
	t.Creat();
	Button b = Button(m_window->m_pros.Width / 2 - 120, m_window->m_pros.Height / 2, m_window->m_pros.Width / 2 - 80, m_window->m_pros.Height / 2 + 40, "上传");
	Button b1= Button(m_window->m_pros.Width / 2 + 80, m_window->m_pros.Height / 2, m_window->m_pros.Width / 2 + 120, m_window->m_pros.Height / 2 + 40, "返回");
	b.Creat(); b1.Creat();
	Message m = Message(0, m_window->m_pros.Height - 40, m_window->m_pros.Width , m_window->m_pros.Height);
	ExMessage msg;
	std::string from, to;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (t.Check(msg.x, msg.y))
			{
				t.OnMessage();
			}
			if (b.IsPressed(msg.x, msg.y))
			{
				//根据文件路径传递文件
				from = t.Gettext();
				to = "\\root\\Paper\\"; to += name;
				File f;
				f.Add(to);
				if (f.Upload(from, to))
				{
					//论文上传成功将其插入表中
					DataBase db;
					if (db.Insert(sql))
					{
						m.SetMsg("上传成功！");
						Sleep(500);
						cleardevice();
						UploadPaper();
						break;
					}
					else
					{
						m.SetMsg("上传失败！");
					}
				}
				else
				{
					m.SetMsg("路径错误，请重新输入！");
				}
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				cleardevice();
				UploadPaper();
				break;
			}
		}
	}
}

void User::DownloadPaper()
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += "Paper"; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*> buttons;
	for (int i = 0; i < r.size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
		columns.push_back(m);
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += "Paper"; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小

	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 40, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 40, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
				messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		bool run1 = true;
		while (run1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					ManagePaper();
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						pqxx::row m_row = r[i];
						cleardevice();
						Download(m_row);
						run = false;
						run1 = false;
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

void User::Download(const pqxx::row&r)
{
	std::vector<Message*>culomn;
	std::vector<Message*>values;
	int width = (m_window->m_pros.Width - 40) / r.size();
	int height = m_window->m_pros.Height / 12;
	int count = 0;
	for (int i = 0; i < r.size(); i++)
	{
		if (!r[i].is_null())
		{
			count++;
		}
		Message* m = new Message(i * width + 20, 0, (i + 1) * width + 20, height, r[i].name());
		Message* m1 = new Message(i * width + 20, height, (i + 1) * width + 20, 2 * height, r[i].c_str());
		culomn.push_back(m);
		values.push_back(m1);
		culomn[i]->Creat();
		values[i]->Creat();
	}
	Button b = Button(m_window->m_pros.Width / 2 - 200, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 - 120, 2 * m_window->m_pros.Height / 3 + height, "下载");
	Button b1 = Button(m_window->m_pros.Width / 2 + 120, 2 * m_window->m_pros.Height / 3, m_window->m_pros.Width / 2 + 200, 2 * m_window->m_pros.Height / 3 + height, "返回");
	b.Creat(); b1.Creat();
	//信息提示
	Message m = Message(0, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height);
	std::string sql;
	bool is_ok = true;
	DataBase db;
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (b.IsPressed(msg.x, msg.y))
				{
					bool finish = true;
					std::cout << b.Getname() << std::endl;
					//添加下载次数到论文信息表中
					sql = "SELECT * FROM \"PaperMsg\" WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
					pqxx::result res = db.Select(sql);
					//为空则说明第一次下载，将该数据插入到表中
					if (res.empty())
					{
						sql = "INSERT INTO \"PaperMsg\" VALUES('"; sql += r[0].c_str(); sql += "','"; sql += r[1].c_str(); sql += "',1)";
						if (db.Insert(sql))
						{
							std::cout << "插入下载次数表成功！" << std::endl;

						}
						else
						{
							std::cout << "插入下载次数表失败！" << std::endl;
							finish = false;
						}
					}
					//不为空则更新即可
					else
					{
						sql = "UPDATE \"PaperMsg\" SET number=number+1 WHERE name='"; sql += r[0].c_str(); sql += "' AND author='"; sql += r[1].c_str(); sql += "'";
						if (db.Update(sql))
						{
							std::cout << "更新下载次数表成功！" << std::endl;
						}
						else
						{
							std::cout << "更新下载次数表失败！" << std::endl;
							finish = false;
						}
					}
					//从根目录下载到用户目录
					if (finish) {
						std::string name = r[0].c_str(); name += "-"; name += r[1].c_str(); name += ".txt";
						std::string target = "\\"; target += m_account; target += "-"; target += m_password; target += "\\Paper\\";
						File f;
						f.Download(name, target);
						m.SetMsg("下载成功！");
						Sleep(500);
						cleardevice();
						DownloadPaper();
						break;
					}
				}
				if (b1.IsPressed(msg.x, msg.y))
				{
					std::cout << b1.Getname() << std::endl;
					cleardevice();
					DownloadPaper();
					break;
				}
			}
		}
	}
	//释放空间
	for (int i = 0; i < r.size(); i++)
	{
		delete culomn[i]; culomn[i] = nullptr;
		delete values[i]; values[i] = nullptr;
	}
}

void Visit::Login()
{
	Main();
}

void Visit::Main()
{
	Button b(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 4 + 20, "浏览图书");
	Button b1(m_window->m_pros.Width / 2 - 100, 2 * m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 100, 2 * m_window->m_pros.Height / 4 + 20, "浏览论文");
	Button b2(m_window->m_pros.Width / 2 - 100, 3 * m_window->m_pros.Height / 4 - 20, m_window->m_pros.Width / 2 + 100, 3 * m_window->m_pros.Height / 4 + 20, "返回主界面");
	b.Creat(); b1.Creat(); b2.Creat();
	bool run = true;
	ExMessage msg;
	while (run)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (b.IsPressed(msg.x, msg.y))
			{
				std::cout << b.Getname() << std::endl;
				ShowAll("Books");
				run = false;
				break;
			}
			if (b1.IsPressed(msg.x, msg.y))
			{
				std::cout << b1.Getname() << std::endl;
				ShowAll("Paper");
				run = false;
				break;
			}
			if (b2.IsPressed(msg.x, msg.y))
			{
				std::cout << b2.Getname() << std::endl;
				m_loginmunefn();
				run = false;
				break;
			}

		}
	}
}

void Visit::ShowAll(const std::string& tablename)
{
	DataBase db;
	std::string sql = "SELECT column_name FROM information_schema.columns WHERE table_name=";
	sql += "'"; sql += tablename; sql += "'";
	pqxx::result r = db.Select(sql);
	int column = r.size();
	int width = (m_window->m_pros.Width - 40) / column;
	int height = m_window->m_pros.Height / 12;
	std::vector<Message*>columns;
	std::vector<Message*> messages;
	std::vector<Button*>buttons;
	for (int i = 0; i < r.size(); i++)
	{
		Message* m = new Message(20 + i * width, 0, 20 + (i + 1) * width, height, r[i].front().c_str());
		columns.push_back(m);
	}
	//一页显示10行数据
	sql = "SELECT * FROM \""; sql += tablename; sql += "\"";
	r = db.Select(sql);
	//左右留出20大小

	//数据为空时显示
	Message empty = Message(m_window->m_pros.Width / 2 - 100, m_window->m_pros.Height / 2 - 40, m_window->m_pros.Width / 2 + 100, m_window->m_pros.Height / 2 + 40, "找不到数据！");
	int maxpage = 0;
	if (!r.empty())
	{
		if (r.size() < 10)
		{
			maxpage = 1;
		}
		else
		{
			maxpage = r.size() / 10 + (bool)(r.size() % 10);
		}
		for (int i = 0; i < r.size(); i++)
		{
			for (int j = 0; j < r.front().size(); j++)
			{
				if (j == 0)
				{
					Button* b = new Button(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
					b->SetStyle(BLACK, GREEN);
					buttons.push_back(b);
				}
				Message* m = new Message(20 + j % column * width, (i % 10 + 1) * height, 20 + (j % column + 1) * width, (i % 10 + 2) * height, r[i][j].c_str());
				messages.push_back(m);
			}
		}

	}
	bool run = true;
	int page = 0;
	while (run)
	{
		cleardevice();
		if (r.empty())
		{
			//无数据
			empty.Creat();
		}
		else
		{
			//有数据
			for (Message* m : columns)
			{
				m->Creat();
			}
			for (int i = 10 * page * column; i < messages.size() && i < 10 * (page + 1) * column; i++)
			{
				messages[i]->Creat();
			}
			for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
			{
				buttons[i]->Creat();
			}

		}
		//其他操作
		Button pre(0, m_window->m_pros.Height - height, width / 2, m_window->m_pros.Height, "上一页");
		Button next(m_window->m_pros.Width - width / 2, m_window->m_pros.Height - height, m_window->m_pros.Width, m_window->m_pros.Height, "下一页");
		Button exit(m_window->m_pros.Width / 2 - width / 4, m_window->m_pros.Height - height, m_window->m_pros.Width / 2 + width / 4, m_window->m_pros.Height, "返回");
		pre.Creat(); next.Creat(); exit.Creat();
		Sleep(300);
		ExMessage msg;
		while (1)
		{
			msg = getmessage(EX_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (pre.IsPressed(msg.x, msg.y))
				{
					if (page != 0)
					{
						page--;
					}
					else
					{
						page = 0;
					}
					break;
				}
				if (next.IsPressed(msg.x, msg.y))
				{
					if (page < maxpage - 1)
					{
						page++;
					}
					else
					{
						page = maxpage - 1;
					}
					break;
				}
				if (exit.IsPressed(msg.x, msg.y))
				{
					cleardevice();
					Main();
					run = false;
					break;
				}
				for (int i = 10 * page; i < buttons.size() && i < 10 * (page + 1); i++)
				{
					if (buttons[i]->IsPressed(msg.x, msg.y))
					{
						std::cout << buttons[i]->Getname() << std::endl;
						//打开对应文件
						if (tablename == "Books" || tablename == "Paper")
						{
							File f;
							std::string str = "\\root\\"; str += tablename; str += "\\"; str += buttons[i]->Getname(); str += "-"; str += messages[i * column + 1]->Getmsg(); str += ".txt";
							f.Open(str);
						}
						break;
					}
				}
			}
		}
	}
	for (Message* m : messages)
	{
		delete m;
		m = nullptr;
	}
	for (Message* m : columns)
	{
		delete m;
		m = nullptr;
	}
	for (Button* b : buttons)
	{
		delete b;
		b = nullptr;
	}
}

