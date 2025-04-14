#include"pch.h"
#include<graphics.h>
#include<iostream>
#include<random>
#include"Login.h"
#include"File.h"
using namespace std;
int main()
{

	Login* l = new Login();
	initgraph(l->m_window->m_pros.Width, l->m_window->m_pros.Height, EX_SHOWCONSOLE);
	l->Init();
	delete l;
	l = nullptr;
	return 0;
}
