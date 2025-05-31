#include "ManageMent.h"
#include<sstream>
#include<fstream>
#include<string>
#include<iostream>
#include<algorithm>
#include"widgets/Window.h"
#include<conio.h>
#include"widgets/Timer.h"
#include<sstream>

using namespace std;

ManageMent::ManageMent():m_key(0)
{
	readData("./resource/Employee.txt");

	m_bk = Image("./images/bk.png",Window::width(),Window::height());
	
	menu_btns.push_back(new PushButton("Overview"));
	menu_btns.push_back(new PushButton("Add"));
	menu_btns.push_back(new PushButton("Delete"));
	menu_btns.push_back(new PushButton("Modify"));
	menu_btns.push_back(new PushButton("Find"));
	menu_btns.push_back(new PushButton("Exit"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		menu_btns[i]->setHover(LIGHTBLUE);

		int x = (Window::width() - menu_btns[i]->width()) / 2;
		int topMargin = (Window::height() - menu_btns.size() * menu_btns[0]->height()) / 2;
		int y = topMargin + i * menu_btns[i]->height();
		menu_btns[i]->move(x,y);
	}

	m_insertTable.setHeader(tableHeader);
	m_insertTable.move((Window::width()-m_insertTable.width())/2, 50);
	m_insertTable.setRowCount(16);
	for (auto val : vec_stu)
	{
		m_insertTable.insert(val.formatInfo());
	}
	Font font = m_insertTable.font();
	font.setItalic(false);
	m_insertTable.setFont(font);


	m_insertEdit.setFixedSize(400, 30);
	m_insertEdit.move((Window::width() - m_insertEdit.width()) / 2, (Window::height() - m_insertEdit.height()) / 2);
	m_insertBtn.setFixedSize(50, 30);
	m_insertBtn.move(m_insertEdit.x() + m_insertEdit.width()+20, m_insertEdit.y());
	m_insertBtn.setText("ok");

	searchEdit = new LineEdit(0,0,200,30);
	searchIdBtn = new PushButton("By id",0,0,200,30);
	searchNameBtn = new PushButton("By name", 0, 0, 200, 30);
	searchTable = new Table;
	searchTable->setRowCount(6);
	searchTable->setHeader(tableHeader);

	font = searchTable->font();
	font.setItalic(true);
	font.setHeight(20);
	searchTable->setFont(font);



	searchIdBtn->move((Window::width() - searchIdBtn->width()) / 2, Window::height() / 4);
	searchNameBtn->move((Window::width() - searchNameBtn->width()) / 2, Window::height() / 4 + searchNameBtn->height());
	searchEdit->move((Window::width() - searchEdit->width()) / 2, Window::height() / 3);
	searchTable->move((Window::width() - searchTable->width()) / 2, Window::height() / 3 + 100);

	delEdit = new LineEdit(0, 0, 200, 30);;
	delBtn = new PushButton("Delete", 0, 0, 200, 30);
	delTable = new Table;
	delTable->setRowCount(6);
	delTable->setHeader(tableHeader);
	delEdit->setInputBoxTitle("Please enter the id");

	delEdit->move((Window::width() - (delEdit->width()*2+20)) / 2, Window::height() / 3);
	delBtn->move(delEdit->x() + delEdit->width()+20, Window::height() / 3);
	delTable->move((Window::width() - delTable->width()) / 2, Window::height() / 3 + 100);

}

void ManageMent::run()
{
	int opt = 66;

	Window::beginDraw();
	while (true)
	{		
		Window::clear();
		drawBackground();

		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:		
				switch (m_msg.vkcode)
				{
				case VK_ESCAPE:		
					opt = 66;
					break;
				}
				break;
			default:				
				this->eventLoop();
				break;
			}
		}


		switch (opt)
		{
		case 66:
			opt = mainMenu(m_msg);
			break;
		case ManageMent::ShowAll:
			displayAll();
			break;
		case ManageMent::Insert:
			insert();
			break;
		case ManageMent::Erase:
			erase();
			break;
		case ManageMent::Modify:
			modify();
			break;
		case ManageMent::Find:
			find();
			break;
		case ManageMent::Exit:
			writeData("./resource/Employee.txt");
			exit(666);
			break;
		default:
			break;
		}	
		Window::flushDraw();
	}
	Window::endDraw();
}

void ManageMent::menu()
{
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
	}
}

void ManageMent::eventLoop()
{
	m_insertTable.eventLoop(m_msg);
	m_insertBtn.eventLoop(m_msg);
	m_insertEdit.eventLoop(m_msg);

	searchIdBtn->eventLoop(m_msg);
	searchNameBtn->eventLoop(m_msg);
	searchEdit->eventLoop(m_msg);

	delBtn->eventLoop(m_msg);
	delEdit->eventLoop(m_msg);
}

void ManageMent::drawBackground()
{
	m_bk.draw();

}

int ManageMent::mainMenu(const ExMessage& msg)
{
	settextstyle(50, 0, "Arial");
	char title[50] = "Employee Management System";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);

	settextstyle(25, 0, "Arial");
	outtextxy(550, 480, "Author: KK");

	for (auto btn : menu_btns)
	{
		btn->show();
	}
	for (size_t i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->eventLoop(msg);
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return 66;
}

void ManageMent::updateTableData()
{
	m_insertTable.clear();
	for (auto val : vec_stu)
	{
		m_insertTable.insert(val.formatInfo());
	}
}

void ManageMent::displayAll()
{
	m_insertTable.show();
}

void ManageMent::insert()
{
	settextstyle(50, 0, "Arial");
	char title[50] = "Add Employee";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);

	m_insertEdit.show();
	m_insertBtn.show();
	settextstyle(30, 0, "Arial");
	outtextxy(m_insertEdit.x()-50, m_insertEdit.y()-150, "Please enter: <id,name,Company,level,year,salary>");

	if (m_insertBtn.isClicked() && Timer::startTimer(200,0))
	{
		std::string newData = m_insertEdit.text();
		if (newData.empty() || std::count(newData.begin(),newData.end(),' ')!=5)
		{
			printf("Fail! re-input\n");
			return;
		}
		
	
		std::replace(newData.begin(), newData.end(), ' ', '\t');

		m_insertTable.insert(newData);	

		Employee t;
		t.formatWrite(newData);
		vec_stu.push_back(t);
		m_insertEdit.clear();
		
		printf("Success\n");
	}

}

void ManageMent::erase()
{
	settextstyle(50, 0, "Arial");
	char title[50] = "Delete Employee";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);

	delEdit->show();
	delBtn->show();
	delTable->show();

	static std::vector<Employee>::iterator delIt = vec_stu.end();
	if (delEdit->textChanged())
	{
		std::string info = delEdit->text();
		if (info.empty())
			return;

		Employee stu;
		stringstream stream(info);
		stream >> stu.number;
		delIt = std::find(vec_stu.begin(), vec_stu.end(), stu);
		if (delIt != vec_stu.end())
		{
			delTable->insert(delIt->formatInfo());
		}
	}
	
	if (delBtn->isClicked() && delIt != vec_stu.end() && Timer::startTimer(200,1))
	{
		std::cout << "delete" << std::endl;
		vec_stu.erase(delIt);
		delTable->clear();
		delIt = vec_stu.end();

		updateTableData();
	}
	
}

void ManageMent::modify()
{
	settextstyle(50, 0, "Arial");
	char title[50] = "Modify information";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);
}

void ManageMent::find()
{
	settextstyle(50, 0, "Arial");
	char title[50] = "Find Employee";
	outtextxy((Window::width() - textwidth(title)) / 2, 50, title);
	
	int where = -1;		
	if (searchIdBtn->isClicked())
	{
		std::cout << "numberBtn->isClickedQAQ~" << std::endl;
		searchEdit->setInputBoxTitle("Enter id:");
		searchEdit->popInputBox();
		where = 0;
	}
	if (searchNameBtn->isClicked())
	{
		searchEdit->setInputBoxTitle("Enter name:");
		searchEdit->popInputBox();
		where = 1;
	}

	searchIdBtn->show();
	searchNameBtn->show();
	searchTable->show();
	

	std::string res = searchEdit->text();
	if (!res.empty())
	{
		Employee stu;
		std::stringstream stream(res);
		if (where == 0)
		{
			stream >> stu.number ;
			auto findIt = std::find(vec_stu.begin(), vec_stu.end(), stu);
			if (findIt != vec_stu.end())
			{
				cout << "Success!";
				searchTable->insert(findIt->formatInfo());
				findIt->display();
			}
		}
		else if (where == 1)
		{
			stream >> stu.name;
			for (Employee& s : vec_stu)
			{
				if (s.name == stu.name)
				{
					cout << "Success!";
					searchTable->insert(s.formatInfo());
					s.display();
				}
			}
		}
	}
	
}

void ManageMent::sort()
{
	std::sort(vec_stu.begin(), vec_stu.end());
	std::cout << "Sorted!" << std::endl;
}


void ManageMent::readData(const std::string& fileName)
{
	fstream stream(fileName.c_str(), ios::in);
	if (!stream.is_open())
	{
		cerr << fileName << "file open failed" << endl;
		return;
	}
	Employee stu;
	char buf[1024] = { 0 };
	stream.getline(buf, 1024);
	tableHeader = buf;

	while (!stream.eof())
	{
		memset(buf, 0, sizeof(buf));
		stream.getline(buf, 1024);

		if (strlen(buf) == 0)
			break;
	
		stringstream ss(buf);
		ss >> stu.number >> stu.name >> stu.company >> stu.level >> stu.year >> stu.salary;
		vec_stu.push_back(stu);
	}
	stream.close();
}

void ManageMent::writeData(const std::string& fileName)
{
	fstream write(fileName.c_str(), ios::trunc | ios::out);
	if (!write.is_open())
	{
		cerr << fileName << " file open failed [save]";
		return;
	}
	tableHeader += '\n';
	write.write(tableHeader.c_str(), tableHeader.size());
	for (auto& val : vec_stu)
	{
		string info = val.formatInfo();
		write.write(info.c_str(),info.size());
	}
	write.close();
}
