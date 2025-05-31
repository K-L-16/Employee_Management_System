#pragma once
#include"Employee.h"
#include<vector>
#include<map>
#include"widgets/pushButton.h"
#include"widgets/Table.h"
#include"widgets/LineEdit.h"
class ManageMent
{
	enum Operator
	{
		ShowAll,
		Insert,
		Erase,
		Modify,
		Find,
		Exit,
	};
public:
	ManageMent();
	void run();
	void menu();

	void eventLoop();
	void drawBackground();

	int mainMenu(const ExMessage& msg);

	void updateTableData();
	void displayAll();
	void insert();
	void erase();
	void modify();
	void find();
	void sort();
private:
	void readData(const std::string& fileName);
	void writeData(const std::string& fileName);
public:
	std::string tableHeader;	
	std::vector<Employee> vec_stu;
	int m_prevStuCnt;	

	std::vector<PushButton*> menu_btns;

	Table		m_insertTable;
	LineEdit	m_insertEdit;		
	PushButton	m_insertBtn;		

	ExMessage m_msg;
	int m_key;
public:
	Image m_bk;
public://find
	LineEdit*		searchEdit;
	PushButton*		searchIdBtn;
	PushButton*		searchNameBtn;
	Table*			searchTable;
public://delete
	LineEdit*	delEdit;
	PushButton* delBtn;
	Table*		delTable;
};

