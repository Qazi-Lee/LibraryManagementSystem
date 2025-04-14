#include"pch.h"
#include "Button.h"

Button::Button(int lx, int ly, int rx, int ry, const std::string& str)
{
    r = new RECT;
    r->left = lx; r->top = ly; r->right = rx; r->bottom = ry;
    m_name = str;
}

Button::~Button()
{
    if (r != nullptr)
    {
        delete r;
        r = nullptr;
    }
}

bool Button::IsPressed(int x, int y)
{
    if (r->left<= x && x <= r->right&& r->top <= y && y <=r->bottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Button::Creat()
{
    int oldfillcolor = getfillcolor();
    int oldtextcolor = gettextcolor();
    setfillcolor(m_fillcolor);
    settextcolor(m_textcolor);
    fillrectangle(r->left, r->top, r->right, r->bottom);
    drawtext(StringtoWString(m_name).c_str(), r, m_textmode);
    setfillcolor(oldfillcolor);
    settextcolor(oldtextcolor);
}
