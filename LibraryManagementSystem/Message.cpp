#include"pch.h"
#include "Message.h"

Message::Message(int left, int top, int right, int bottom, const std::string& str)
{
	r = new RECT;
	r->left = left;
	r->top = top;
	r->right = right;
	r->bottom = bottom;
	msg = str;
}

Message::~Message()
{
	if (r != nullptr)
	{
		delete r;
		r = nullptr;
	}
}

 void Message::SetMsg(const std::string& str)
{
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();
	int oldtextcolor = gettextcolor();
	msg = str;
	setfillcolor(m_fillcolor);
	solidrectangle(r->left, r->top, r->right, r->bottom);
	drawtext(StringtoWString(msg).c_str(), r,m_textmode);
	Sleep(500);
	solidrectangle(r->left, r->top, r->right, r->bottom);
	setfillcolor(oldfillcolor);
}

 void Message::Creat()
 {
	 int oldfillcolor = getfillcolor();
	 int oldtextcolor = gettextcolor();
	 setfillcolor(m_fillcolor);
	 settextcolor(m_textcolor);
	 fillrectangle(r->left, r->top, r->right, r->bottom);
	 drawtext(StringtoWString(msg).c_str(), r, m_textmode);
	 setfillcolor(oldfillcolor);
	 settextcolor(oldtextcolor);
 }
