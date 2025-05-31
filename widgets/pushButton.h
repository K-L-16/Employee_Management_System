//button
#ifndef __PUSHBUTTON_H_
#define __PUSHBUTTON_H_
#include"Configure.h"
#include"image.h"
#include"BasicWidget.h"

class PushButton:public BasicWidget
{
public:
	PushButton(std::string text ="PushButton",int x=0,int y=0,int w =100,int h = 30);
	void show();
	
	void setText(std::string text);
	void setBackgroundImage(std::string imgPath);
	void setBackgroundColor(Color color);

	void setHover(COLORREF c);
	void setHover(std::string imgPath);
	//event loop
	void eventLoop(const ExMessage&);

	//check if the monse is on it
	bool isin();
	//if click
	bool isClicked();
	

	~PushButton();

public:
	std::string text;
	bool  isshow = false;			
	ExMessage _msg;					
public:	//current
	Image* cur_img = nullptr;
	COLORREF cur_color = RGB(128, 128, 128);

public:	//normal
	Image* nor_img = nullptr;
	COLORREF nor_color = RGB(128, 128, 128);

public:	//hover
	Image* h_img = nullptr;
	COLORREF h_color = RGB(173, 216, 230);
};
#endif