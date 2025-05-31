#include "Employee.h"
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
Employee::Employee():number(0),level(0),year(0),salary(0)
{}

Employee::Employee(uint32 number):Employee()
{
	this->number = number;
}

Employee::Employee(uint32 number, const std::string& name, const std::string& company, int level, int year, int salary)
	: number(number),name(name),company(company), level(level), year(year), salary(salary)
{}

void Employee::display()
{
	cout << this->number << "\t" << this->name << "\t" << this->company << "\t" << this->level << "\t" << this->year << "\t" << this->salary << endl;
}

std::string Employee::formatInfo()
{
	stringstream ss;
	ss<< this->number << "\t" << this->name << "\t" << this->company << "\t" << this->level << "\t" << this->year << "\t" << this->salary << endl;
	return ss.str();
}

void Employee::formatWrite(const std::string& str)
{
	stringstream ss(str);
	ss >> this->number  >> this->name  >> this->company  >> this->level  >> this->year  >> this->salary;
}

bool Employee::operator==(const Employee& right) const
{
	return this->number == right.number;
}

bool Employee::operator>(const Employee& right) const
{
	return this->number > right.number;
}

bool Employee::operator<(const Employee& right) const
{
	return this->number < right.number;
}
