#pragma once
#include "configure.h"
class Window
{
public:
	Window(int w, int h, int flag);
	void setWinTitle(const std::string& title);
	int exec();
	static int width();
	static int height();

	static void clear();
	static void beginDraw();
	static void endDraw();
	static void flushDraw();

	//�������� ������
	inline static bool hasMsg() { return  ::peekmessage(&m_msg,EM_MOUSE | EM_KEY); }//��̬����
	inline static const EASYXMSG& getMsg() { return m_msg; }
private:
	HWND m_handle;//���ھ��
	inline static EASYXMSG m_msg;//��Ϣ
};

