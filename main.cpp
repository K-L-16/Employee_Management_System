#include"ManageMent_gui.h"
#include"widgets/Window.h"
#include"widgets/Table.h"
#include"widgets/Timer.h"
int main()
{
	Window w(960, 640, EX_NOCLOSE);
	w.setWindowTitle("Employee Management System");

	ManageMent m;
	m.run();

	return w.exec();
}