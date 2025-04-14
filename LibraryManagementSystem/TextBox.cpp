#include"pch.h"
#include "TextBox.h"

TextBox::TextBox(int left, int top, int right, int bottom, const std::string& str)
{
	r = new RECT;
	r->left = left;
	r->top = top;
	r->right = right;
	r->bottom = bottom;
	m_name = str;

}

TextBox::~TextBox()
{
	if (r != nullptr)
	{
		delete r;
		r = nullptr;
	}
	if (!strcode.empty())
	{
		strcode.emplace();
	}
}

bool TextBox::Check(int x, int y)
{
	if (r->left <= x && x <= r->right && r->top <= y && y <= r->bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TextBox::OnMessage(const bool& model)
{
	
	int oldlinecolor = getlinecolor();
	int oldtextcolor = gettextcolor();
	int oldfillcolor = getfillcolor();
	setlinecolor(BLACK);
	settextcolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(r->left, r->top, r->right, r->bottom);
	if (model) {
		drawtext(StringtoWString(text).c_str(), r, DT_LEFT | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
	}
	else
	{
		drawtext(StringtoWString(text_hide).c_str(), r, DT_LEFT | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
	}
	bool input = true;
	std::wstring wstr;
	ExMessage msg;
	while (input)
	{
		//有输入
		if (peekmessage(&msg, EX_MOUSE | EX_CHAR, false))/*不从消息队列取出*/
		{
			//鼠标点击非文本框区域结束输出，消息仍保留在消息队列
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x<r->left || msg.x>r->right || msg.y<r->top || msg.y>r->bottom) {
					input = false;
				}
			}
			else if (msg.message == WM_CHAR)
			{
				switch (msg.ch)
				{
				case'\b':
					std::cout << "删除" << std::endl;
					//中文字符占三个，英文字符占1个
					if (!text.empty()) {
						if (!strcode.empty())
						{
							if (strcode.top()>127) {
								text = text.substr(0, text.length() - 3);								
							}
							else {													    	
								text = text.substr(0, text.length() - 1);
							}
							text_hide = text_hide.substr(0, text_hide.length() - 1);
						}
					}
					fillrectangle(r->left, r->top, r->right, r->bottom);
					if (model) {
						drawtext(StringtoWString(text).c_str(), r, DT_LEFT | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
					}
					else
					{
						drawtext(StringtoWString(text_hide).c_str(), r, DT_LEFT | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
					}
					break;
				case'\r':
					std::cout << "完成" << std::endl;
					input = false;
					break;
				default:
					strcode.push((int)msg.ch);
					wstr = (wchar_t)msg.ch;
					text += WStringtoString(wstr);
					text_hide += WStringtoString(_T("*"));
					fillrectangle(r->left, r->top, r->right, r->bottom);
					if (model) {
						drawtext(StringtoWString(text).c_str(), r, DT_LEFT | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
					}
					else
					{
						drawtext(StringtoWString(text_hide).c_str(), r, DT_LEFT | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
					}
					break;
				}
			}
			//字符信息从队列取出,鼠标点击信息不处理
			peekmessage(NULL, EX_CHAR);
		}
		//光标待实现
		/*........*/
	}
	setlinecolor(oldlinecolor);
	settextcolor(oldtextcolor);
	setfillcolor(oldfillcolor);
}

void TextBox::Creat()
{
	//保存环境值
	int oldfillcolor = getfillcolor();
	int oldtextcolor = gettextcolor();
	//绘制文本框
	setfillcolor(WHITE);
	fillrectangle(r->left, r->top, r->right, r->bottom);
	settextcolor(BLUE);
	drawtext(StringtoWString(m_name).c_str(), r, DT_CENTER | ODT_BUTTON | DT_SINGLELINE| DT_WORD_ELLIPSIS);
	//恢复环境值
	setfillcolor(oldfillcolor);
	settextcolor(oldtextcolor);
}
