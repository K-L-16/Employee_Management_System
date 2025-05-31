#pragma once
#include<conio.h>
#include"Configure.h"

class Window
{
public:
	Window(int w, int h,int flag = 0);
	~Window();
	void setWindowTitle(const std::string& title);
	void setWindowColor(COLORREF c);
	void setCursor(LPSTR curSorStyle);
	inline int exec() { system("pause"); return 0; };
public://static
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	inline static bool hasMsg() { return peekmessage(&s_message, EX_MOUSE | EX_KEY); }
	inline static const ExMessage& getMsg() { return s_message; }

private:
	HWND handle;
	static ExMessage s_message;
};

