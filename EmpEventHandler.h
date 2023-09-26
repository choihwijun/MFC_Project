#pragma once

class Employee;

class AddEmployeeEventHandler
{
public:
	virtual void AddedEmployee(Employee* emp) = 0;
};

class UpdateEmployeeEventHandler
{
public :
	virtual void UpdatedEmployee(Employee* emp) = 0;
};

class RemoveEmployeeEventHandler 
{
public :
	virtual void RemovedEmployee(CString number) = 0;
};

