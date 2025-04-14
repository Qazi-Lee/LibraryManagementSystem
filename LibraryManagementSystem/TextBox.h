#pragma once
#include"Translate.h"
#include"Message.h"
#define TB_PUBLIC 1
#define TB_PRIVATE 0
class TextBox
{
public:
	TextBox(int left,int top,int right,int bottom,const std::string&str="TextBox");
	~TextBox();
	bool Check(int x,int y);
	void OnMessage(const bool& model=true);
	std::string Gettext()const { return text; }
	std::string Getname()const { return m_name; }
	void Creat();
public:
	std::string text;
	std::string text_hide;
	RECT* r;
	std::string m_name;
	std::stack<int>strcode;
};

