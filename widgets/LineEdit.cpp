#include "LineEdit.h"
#include"Window.h"
#include<conio.h>

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), textw(2), m_isPopUp(false)
	, m_title("Please Enter:")
{}

void LineEdit::show()
{
	BasicWidget::show();
	setfillcolor(RGB(232, 232, 236));
	fillrectangle(m_x, m_y, m_x+m_w, m_y+m_h);

	setlinecolor(RED);
	line(m_x + textw + 2, m_y + 2, m_x + textw + 2, m_y + m_h - 2);

	outtextxy(m_x, m_y+(m_h - textheight(m_text.c_str())) / 2,m_text.c_str());


	if (m_isPopUp)
	{
		m_pretext = m_text;
		popInputBox();
		m_isPopUp = false;
	}
}
void LineEdit::eventLoop(const ExMessage& msg)
{
	if (msg.x > m_x && msg.x < m_x + m_w && msg.y > m_y && msg.y < m_y + m_h
		&& msg.message == WM_LBUTTONDOWN)
	{
		m_isPopUp = true;
	}
}
void LineEdit::popInputBox()
{
	char str[128] = { 0 };
	InputBox(str, 128, nullptr, m_title.c_str(), m_text.c_str());
	m_text = str;
	textw = ::textwidth(m_text.c_str());
}
void LineEdit::setInputBoxTitle(const std::string& title)
{
	m_title = title;
}

std::string  LineEdit::text()
{
	return m_text;
}

void LineEdit::clear()
{
	m_text.clear();
	textw = 0;
}

bool LineEdit::textChanged()
{
	if (m_pretext == m_text)
	{
		return false;
	}
	m_pretext = m_text;	//update
	return true;
}
