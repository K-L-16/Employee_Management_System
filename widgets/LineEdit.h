#pragma once
#include"BasicWidget.h"
#include<thread>
#pragma comment(lib,"Imm32.lib")
class LineEdit:public BasicWidget
{
public:
	LineEdit(int x = 0, int y = 0, int w = 100, int h = 30);
	void show();

	void eventLoop(const ExMessage& msg);


	void popInputBox();
	void setInputBoxTitle(const std::string& title);
	std::string text();
	void clear();
	
	bool textChanged();
private:
	std::string m_pretext;	
	std::string m_text;		
	int textw;

	std::string m_title;	

	bool m_isPopUp;	//
};

