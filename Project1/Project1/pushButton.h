#pragma once
#include "BasicWidget.h"
#include "configure.h"
class pushButton :
    public BasicWidget
{
public:
    pushButton(const std::string& text, int x = 0, int y = 0, int w = 100, int h = 30);
    void show() override;
    bool isin();
    bool isclicked();

    void eventloop(const EASYXMSG& msg);

private:
    std::string m_text;
    EASYXMSG m_msg;

    COLORREF normal_c = RGB(217, 217, 217);
    COLORREF hover_c = RGB(224,248,250);
    COLORREF cur_c = RGB(217, 217, 217);
};

