#pragma once
#include"Configure.h"
class Image :public IMAGE
{
public:
	Image();
	Image(const std::string& imgPath,int w = 0,int h =0);
	//example: Image("./res/images/jumpMask.jpg","./res/images/jumpSrc.jpg")
	Image(const std::string& maskImgPath, const std::string& srcImgPath,int w = 0,int h =0);
	//example: Image("./res/images/","jumpMask.jpg","jumpSrc.jpg")
	Image(const std::string& prefixPath,const std::string& maskImgPath, const std::string& srcImgPath,int w = 0,int h = 0);
	void draw();
	void draw(DWORD maskdwRop, DWORD srcdwRop);
	void move(int x, int y);

	void save(const std::string& savePath);
	static void save(const std::string& savePath, Image* img);
	Image* getimage(int x, int y, int w, int h);

	DWORD* ImageBuffer();			//get pointer
	
private:
	void SetDefault() override;						//set default
	static void putimage_alapha(int x, int y, IMAGE* src);

	int x;
	int y;
private://
	Image *pMaskImg;
};

