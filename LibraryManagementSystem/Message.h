#pragma once
#include"Translate.h"
class Message
{
public:
	Message(int left, int top, int right, int bottom,const std::string&str="");
	~Message();
	//用来显示错误信息，渐变消失
	 void SetMsg(const std::string& str);
	 //显示默认信息，不消失
	 void Creat();
	 std::string Getmsg()const { return msg; }
	 void SetStyle(const int& fillcolor = BLACK, const int& textcolor = WHITE, const int& mode = DT_CENTER | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS) { m_fillcolor = fillcolor; m_textcolor = textcolor; m_textmode = mode; };
public:
	RECT* r;
	std::string msg;
	int m_fillcolor = BLACK;
	int m_textcolor = WHITE;
	int m_textmode = DT_CENTER | ODT_BUTTON | DT_SINGLELINE;
};
