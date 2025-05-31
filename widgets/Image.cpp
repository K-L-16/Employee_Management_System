#include "Image.h"
#include"Window.h"

Image::Image():x(0),y(0),pMaskImg(nullptr)
{
	
}

Image::Image(const std::string& imgPath, int w, int h): Image()
{
	::loadimage(this, imgPath.c_str(), w, h);
	if (this->getwidth() == 0 && this->getheight() == 0)
	{
		plog("[error] %s load failed\n", imgPath.c_str());
	}
}

Image::Image(const std::string& maskImgPath, const std::string& srcImgPath, int w, int h)
	:pMaskImg(new Image(maskImgPath,w,h))
{
	::loadimage(this, srcImgPath.c_str(), w, h);
	if (this->getwidth() == 0 && this->getheight() == 0)
	{
		plog("[error] %s load failed\n", srcImgPath.c_str());
	}
}

Image::Image(const std::string& prefixPath, const std::string& maskImgPath, const std::string& srcImgPath, int w, int h)
	:Image(prefixPath+maskImgPath, prefixPath+srcImgPath,w,h)
{
}

void Image::draw()
{
	putimage_alapha(this->x, this->y, this);
}

void Image::draw(DWORD maskdwRop,DWORD srcdwRop)
{
	::putimage(this->x, this->y, pMaskImg, maskdwRop);
	::putimage(this->x, this->y, this, srcdwRop);
}

void Image::move(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Image::save(const std::string& savePath)
{
	::saveimage(savePath.c_str(), this);
}

void Image::save(const std::string& savePath, Image* img)
{
	::saveimage(savePath.c_str(), img);
}

Image* Image::getimage(int x, int y, int w, int h)
{
	Image* img = new Image;
	::getimage(img, x, y, w, h);
	return img;
}

DWORD* Image::ImageBuffer()
{
	return ::GetImageBuffer(this);
}

void Image::SetDefault()
{
}


//private
void Image::putimage_alapha(int x, int y, IMAGE* src)
{
	
	DWORD* pwin = GetImageBuffer();			
	DWORD* psrc = GetImageBuffer(src);		
	int win_w = Window::width();				
	int win_h = Window::height();
	int src_w = src->getwidth();				
	int src_h = src->getheight();

	int real_w = (x + src_w > win_w) ? win_w - x : src_w;			
	int real_h = (y + src_h > win_h) ? win_h - y : src_h;			
	if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	
	if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	


	pwin += (win_w * y + x);

	for (int iy = 0; iy < real_h; iy++)
	{
		for (int ix = 0; ix < real_w; ix++)
		{
			byte a = (byte)(psrc[ix] >> 24);
			if (a > 100)
			{
				pwin[ix] = psrc[ix];
			}
		}
		pwin += win_w;
		psrc += src_w;
	}
}
