#pragma once
#include "Employee.h"
#include "EmpEventHandler.h"
#include <map>
#include <list>
using std::list;
using std::map;

typedef list<CString>NList;
typedef NList::iterator NIter;

typedef map<CString, Employee*> EMap;
typedef EMap::iterator EIter;

typedef list<AddEmployeeEventHandler*>AEHList;
typedef AEHList::iterator AEIter;

typedef list<RemoveEmployeeEventHandler*>REHList;
typedef REHList::iterator REIter;

typedef list<UpdateEmployeeEventHandler*> UEHList;
typedef UEHList::iterator UEIter;

class EmpManager
{
	EMap employee_map;

	AEHList aehandlers;
	REHList rehandlers;
	UEHList uehandlers;

	static EmpManager em;

	

	EmpManager();

public :
	static EmpManager& GetEmpManager();
	Employee* GetEmp(CString num);
	void GetEmpNumList(NList* num_list);
	bool AddEmployee(CString num, CString name, CString posit, CString dept, CString image, CString phone, CString ext, CString address, CString starttime, CString endtime);
	bool UpdateEmp(CString num, CString image, CString dept, CString posit, CString phone, CString ext, CString address);
	bool RemoveEmp(CString num);
	void AddUEEventHandler(UpdateEmployeeEventHandler* ueeh);
	void AddREEventHandler(RemoveEmployeeEventHandler* reeh);
	void AddAEEventHandler(AddEmployeeEventHandler* aeeh);

	void Save();
	void Load();

};

