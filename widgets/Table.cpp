#include "Table.h"
#include<iostream>
using namespace std;
Table::Table(int row, int col) 
	:m_rows(row), m_cols(col),  m_curPage(0), m_maxPage(0)
	,BasicWidget(0,0,0,0)
{
	m_prevPageBtn.setText("Previous");
	m_nextPageBtn.setText("Next");
	m_beginPageBtn.setText("First");
	m_endPageBtn.setText("End");

}

void Table::setRowCount(int row)
{
	m_rows = row;
}

void Table::setColCount(int col)
{
	m_cols = col;
}


void Table::setHeader(const std::string& data)
{
	m_header = data;
	m_cols = std::count(m_header.begin(), m_header.end(), '\t') - 1;


	int textw = ::textwidth("Company");
	int texth = ::textheight(m_header.c_str());

	m_gridw = textw + 15;
	m_gridh = texth + 10;

	m_h = m_rows * m_gridh;
	m_w = m_cols* m_gridw;
}

void Table::insert(const std::string& data)
{
	m_datas.push_back(data);
	updateData();
}

void Table::clear()
{
	m_datas.clear();
	updateData();
}

void Table::eventLoop(const ExMessage& msg)
{
	m_prevPageBtn.eventLoop(msg);
	m_nextPageBtn.eventLoop(msg);
	m_beginPageBtn.eventLoop(msg);
	m_endPageBtn.eventLoop(msg);

	if (m_prevPageBtn.isClicked())
	{
		//cout << "m_prevPageBtn" << endl;
		if (m_curPage != 0)
		{
			m_curPage--;
		}
		//cout << "m_extraData:" << m_extraData << endl;
	}
	if (m_nextPageBtn.isClicked())
	{
		//cout << "m_nextPageBtn" << endl;
		if (m_curPage != m_maxPage)
		{
			m_curPage++;
		}
	}
	if (m_beginPageBtn.isClicked())
	{
		m_curPage = 0;
		//cout << "m_beginPageBtn" << endl;
	}
	if (m_endPageBtn.isClicked())
	{
		m_curPage = m_maxPage;
		//cout << "m_endPageBtn" << endl;
	}
	//cout << "m_curPage:" << m_curPage << "/" << m_maxPage << endl;
}

void Table::drawTableGrid()
{
	if (m_rows == 0)
	{
		m_rows = m_datas.size();
	}
	drawHeader();
	setlinestyle(PS_SOLID, 1);

	for (size_t i = 0; i < m_rows + 1; i++)
	{

		int resy = m_y + m_gridh * i;
		line(m_x, resy, m_x + m_cols * m_gridw, resy);
	}

	for (size_t k = 0; k < m_cols+1; k++)
	{
		line(m_x + k * m_gridw, m_y, m_x + k * m_gridw, m_y + m_gridh * m_rows);
	}

	if (m_maxPage > 0)
	{
		initPageBtnPos();
	}
}

void Table::drawTableText()
{

	if (m_rows > m_datas.size() &&m_datas.size()!=0)
	{
		m_rows = m_datas.size();
	}

	int begPos = m_curPage * m_rows;			
	int endPos = m_rows + m_curPage * m_rows;	

	if (m_curPage == m_maxPage)
	{
		endPos = begPos + m_extraData;
	}

	if (m_datas.size() == 0)
	{
		endPos = 0;
	}

	for (int beg = begPos,i =0; beg < endPos; beg++,i++)
	{
		std::vector<std::string> line_data = split(m_datas[beg]);

		for (size_t k = 0; k < line_data.size(); k++)
		{
			int tx = m_x + k * m_gridw;
			int ty = m_y + i * m_gridh;
			BasicWidget::show();
			outtextxy(tx,ty+5, line_data[k].c_str());
		}	
	}
}

void Table::drawHeader()
{

	setlinestyle(PS_SOLID, 2);
	rectangle(m_x, m_y - 30, m_x + m_gridw * m_cols, m_y);
	for (size_t i = 0; i < m_cols + 1; i++)
	{
		line(m_x + i * m_gridw, m_y - 30, m_x + i * m_gridw, m_y);
	}

	std::vector<std::string> header = split(m_header);
	for (auto it = header.begin(); it != header.end();)
	{
		if (it->empty())
		{
			it = header.erase(it);
		}
		else
		{
			it++;
		}
	}
	int space = 0;
	for (size_t i = 0; i < header.size(); i++)
	{
		space = (m_gridw - textwidth(header[i].c_str())) / 2;	
		outtextxy(m_x + i * m_gridw + space, m_y - m_gridh+5, header[i].c_str());
	}
}

void Table::updateData()
{

	if (m_rows >= m_datas.size())
	{
		m_maxPage = 0;
		m_extraData = m_datas.size();
	}
	else
	{	
		m_extraData = m_datas.size() % m_rows;	
		m_maxPage = m_datas.size() / m_rows;	
	}
}

void Table::initPageBtnPos()
{
	m_prevPageBtn.move(m_x, m_y + m_gridh * m_rows + 20);
	m_nextPageBtn.move(m_x + 100, m_y + m_gridh * m_rows + 20);
	m_beginPageBtn.move(m_x + 200, m_y + m_gridh * m_rows + 20);
	m_endPageBtn.move(m_x + 300, m_y + m_gridh * m_rows + 20);

	m_prevPageBtn.show();
	m_nextPageBtn.show();
	m_beginPageBtn.show();
	m_endPageBtn.show();

	std::string pageInfo("Total: " + std::to_string(m_maxPage + 1) + "Pages,The" + std::to_string(m_curPage + 1) + "Page");
	outtextxy(m_x + 450, m_y + m_gridh * m_rows + 20, pageInfo.c_str());
}

std::vector<std::string> Table::split(std::string str,char  separator)
{
	std::vector<std::string> res;
	for (size_t pos = 0; pos != std::string::npos ; )
	{
		if (pos != 0)
			pos++;
		pos = str.find(separator);
		res.push_back(str.substr(0, pos));
		str = std::string(str.data() + pos+1);	
	}	
	return res;
}

void Table::show()
{
	BasicWidget::show();
	drawTableGrid();
	drawTableText();
}

