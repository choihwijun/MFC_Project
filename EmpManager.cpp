#include "pch.h"
#include "EmpManager.h"
#include "Employee.h"
#include <iostream>
#include <sstream>
using namespace std;

EmpManager EmpManager::em;

EmpManager& EmpManager::GetEmpManager() {
	return em;
}

EmpManager::EmpManager()
{

}

Employee* EmpManager::GetEmp(CString num) {	
	return employee_map[	num];	
}

void EmpManager::GetEmpNumList(NList* num_list) {
	Employee* emp = 0;
	EIter seek = employee_map.begin();
	EIter end = employee_map.end();
	
	for (; seek != end; ++seek) {
		emp = (*seek).second;
		if (emp) {
			num_list->push_back((*seek).first);
		}
	}
}

bool  EmpManager::AddEmployee(CString num, CString name, CString posit, CString dept, CString image, CString phone, CString ext, CString address, CString starttime, CString endtime)	
{	
	Employee* employee = new Employee(num, name, posit, dept, image, phone, ext, address, starttime, endtime);
	employee_map[num] = employee;

	//사원 추가한 정보를 알고자 하는 새끼들에게 통보
	AEIter seek = aehandlers.begin();
	AEIter end = aehandlers.end();

	for (; seek != end; ++seek)
	{
		(*seek)->AddedEmployee(employee);
	}

	return true;
}

bool EmpManager::RemoveEmp(CString num) {
	Employee* emp = employee_map[num];
	if (emp) {
		delete emp;
		employee_map[num] = 0;

		REIter seek = rehandlers.begin();
		REIter end = rehandlers.end();
		for (; seek != end; ++seek) {
			(*seek)->RemovedEmployee(num);
		}

		return true;
	}
	return false;
}

bool EmpManager::UpdateEmp(CString num, CString image, CString dept, CString posit, CString phone, CString ext, CString address) {
	Employee* emp = employee_map[num];
	if (emp)
	{
		emp->SetImage(image);
		emp->SetDept(dept);
		emp->SetPosit(posit);
		emp->SetPhone(phone);
		emp->SetExt(ext);
		emp->SetAddress(address);
		UEIter seek = uehandlers.begin();
		UEIter end = uehandlers.end();
		for (; seek != end; ++seek)
		{
			(*seek)->UpdatedEmployee(emp);
		}
		return true;
	}
	return false;
}

void EmpManager::AddAEEventHandler(AddEmployeeEventHandler* aeeh) {
	aehandlers.push_back(aeeh);
}
void EmpManager::AddREEventHandler(RemoveEmployeeEventHandler* reeh) {
	rehandlers.push_back(reeh);
}
void EmpManager::AddUEEventHandler(UpdateEmployeeEventHandler* ueeh) {
	uehandlers.push_back(ueeh);
}

void EmpManager::Save() { // 직렬화
	CFile cf(TEXT("data.txt"), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&cf, CArchive::store);

	EIter seek = employee_map.begin();
	EIter end = employee_map.end();
	Employee* employee = 0;
	for (; seek != end; ++seek) {
		employee = (*seek).second;
		if (employee) {
			employee->Serialize(ar);
		}
	}
	ar.Close();
	cf.Close();
}

void EmpManager::Load() { // 역직렬화
	CFile* pcf;
	try {
		pcf = new CFile(TEXT("data.txt"), CFile::modeRead);
	}
	catch (...) {
		return;
	}

	CArchive ar(pcf, CArchive::load);
	int length = pcf->GetLength();

	while (true) {
		try {
			Employee* emp = new Employee(ar);

			employee_map[emp->Getnum()] = emp;

			AEIter seek = aehandlers.begin();
			AEIter end = aehandlers.end();
			for (; seek != end; ++seek)
			{
				(*seek)->AddedEmployee(emp);
			}
		}
		catch (...) {
			break;
		}
	}


	ar.Close();
	pcf->Close();
	delete(pcf);

}