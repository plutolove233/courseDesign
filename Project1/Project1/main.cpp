#include "management.h"
#include "Window.h"

int main() {
	management m;
	Window w(960,640,EW_SHOWCONSOLE);
	w.setWinTitle("ͼ�Ĵ洢�ͻ��������Ķ�����ʾ");
	m.run();
	return 0;
}