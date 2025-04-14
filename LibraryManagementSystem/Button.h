#pragma once
#include"Translate.h"
class Button
{
public:
	Button(int lx, int ly, int rx, int ry, const std::string &str="Button");
	~Button();
	bool IsPressed(int x,int y);
	std::string Getname()const { return m_name; }
	void Creat();
	void SetStyle(const int& fillcolor = WHITE, const int& textcolor = BLACK, const int& mode = DT_CENTER | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS) { m_fillcolor = fillcolor; m_textcolor = textcolor; m_textmode = mode; };
public:
	RECT *r;
	std::string m_name;
	int m_fillcolor = WHITE;
	int m_textcolor = BLACK;
	int m_textmode = DT_CENTER | ODT_BUTTON | DT_SINGLELINE;
};

