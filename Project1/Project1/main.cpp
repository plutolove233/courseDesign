#include "management.h"
#include "Window.h"

int main() {
	management m;
	Window w(960,640,EW_SHOWCONSOLE);
	w.setWinTitle("图的存储和基本操作的动画演示");
	m.run();
	return 0;
}