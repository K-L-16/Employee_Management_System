#pragma once
#include"BasicWidget.h"
#include"pushButton.h"
#include<vector>
class Table :public BasicWidget
{
public:
	Table(int row = 1, int col = 0);
	void setRowCount(int row);
	void setColCount(int col);

	void setHeader(const std::string& data);
	void insert(const std::string& data);
	void clear();

	void eventLoop(const ExMessage& msg);


	void show();
	std::vector<std::string> split(std::string str, char  separator = '\t');
private:
	void drawTableGrid();
	void drawTableText();
	void drawHeader();
	void updateData();		
	

	void initPageBtnPos();

private:
	size_t m_rows;
	size_t m_cols;

	int m_gridw;
	int m_gridh;

	std::string m_header;
	std::vector<std::string> m_datas;
private:	
	int m_curPage;	
	int m_maxPage;	
	int m_extraData;	

	PushButton m_prevPageBtn;		
	PushButton m_nextPageBtn;		
	PushButton m_beginPageBtn;		
	PushButton m_endPageBtn;		
};

