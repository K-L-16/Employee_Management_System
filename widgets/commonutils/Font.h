#pragma once
#include"TypeDefine.h"
#include<string>
#include"Color.h"
class Font
{
public:
    Font();
    Font(const std::string& family, int Weight = 0, bool italic = false);

    void setHeight(int height);
    void setWidth(int width);
    void setBold(bool enable);
    void setItalic(bool enable);
    void setWeight(int weight);
    void setQuality(int Quality);
    void setFamily(const std::string& family);
    void setColor(const Color& color);

    const Color& color();

    int Height();
    int Width();
    bool Bold();
    bool Italic();
    int Weight();
    int Quality();
    std::string Family();

private:
    int32      lfHeight = 0;            
    int32      lfWidth = 0;             
    int32      lfEscapement = 0;        
    int32      lfOrientation = 0;       
    int32      lfWeight = 0;           
    Byte      lfItalic = 0;            
    Byte      lfUnderline = 0;         
    Byte      lfStrikeOut = 0;         
    Byte      lfCharSet = 0;            
    Byte      lfOutPrecision = 0;      
    Byte      lfClipPrecision = 0;      
    Byte      lfQuality = 0;           
    Byte      lfPitchAndFamily = 0;    
    char      lfFaceName[32] = { 0 };  
    Color     lfcolor;
};