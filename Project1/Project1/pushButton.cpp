#include "pushButton.h"

pushButton::pushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{

}

void pushButton::show()
{
	setfillcolor(cur_c);
	::fillrectangle(m_x, m_y, m_x + m_w, m_y + m_h);

	settextcolor(BLACK);
	settextstyle(18,0,"Microsoft YaHei");
	int tx, ty;
	tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

bool pushButton::isin()
{
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
		return true;
	return false;
}

bool pushButton::isclicked()
{
	if (isin())
	{
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}
	}
	return false;
}

void pushButton::eventloop(const EASYXMSG& msg)
{
	m_msg = msg;
	if (isin())
	{
		cur_c = hover_c;
	}
	else
	{
		cur_c = normal_c;
	}
}
