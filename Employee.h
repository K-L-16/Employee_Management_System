#pragma once
#include<string>
class Employee
{
	using uint32 = unsigned;
public:
	Employee();
	Employee(uint32 number);
	Employee(uint32 number,const std::string& name,const std::string& company,
		int level,int year,int salary);
	void display();
	std::string formatInfo();
	void formatWrite(const std::string& str);
public:
	bool operator==(const Employee& right) const;
	bool operator>(const Employee& right) const;
	bool operator<(const Employee& right) const;
public:
	uint32 number;
	std::string name;
	std::string company;
	int level;
	int year;
	int salary;
};

