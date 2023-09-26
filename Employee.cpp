#include "pch.h"
#include "Employee.h"

Employee::Employee(CString num, CString name, CString posit, CString dept,
	CString image, CString phone, CString ext, CString address, CString starttime, CString endtime)  {
	this->image = image;
	this->num = num;
	this->name = name;
	this->dept = dept;
	this->posit = posit;
	this->phone = phone;
	this->ext = ext;
	this->address = address;
	this->StartTime = _T("");
	this->EndTime = _T("");
}

CString Employee::Getimage() {
	return image;
}
CString Employee::Getnum() {
	return num;
}
CString Employee::Getname() {
	return name;
}
CString Employee::Getdept() {
	return dept;
}
CString Employee::Getposit() {
	return posit;
}
CString Employee::Getphone() {
	return phone;
}
CString Employee::Getext() {
	return ext;
}
CString Employee::Getaddress() {
	return address;
}
CString Employee::GetStartTime() {
	return StartTime;
}
CString Employee::GetEndTime() {
	return EndTime;
}

void Employee::SetImage(CString image) {
	this->image = image;
}
void Employee::SetNum(CString num) {
	this->num = num;
}
void Employee::SetName(CString name) {
	this->name = name;
}
void Employee::SetDept(CString dept) {
	this->dept = dept;
}
void Employee::SetPosit(CString posit) {
	this->posit = posit;
}
void Employee::SetPhone(CString phone) {
	this->phone = phone;
}
void Employee::SetExt(CString ext) {
	this->ext = ext;
}
void Employee::SetAddress(CString address) {
	this->address = address;
}

void Employee::SetStartTime(CString StartTime) {
	this->StartTime = StartTime;
}
void Employee::SetEndTime(CString EndTime) {
	this->EndTime = EndTime;
}

Employee::Employee(CArchive& ar) {
	Serialize(ar);
}

void Employee::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
			ar << name;
			ar << num;
			ar << dept;
			ar << posit;
			ar << phone;
			ar << ext;
			ar << address;
			ar << image;
			ar << StartTime;
			ar << EndTime;
	}
	else
	{	// loading code
			ar >> name;
			ar >> num;
			ar >> dept;
			ar >> posit;
			ar >> phone;
			ar >> ext;
			ar >> address;
			ar >> image;
			ar >> StartTime;
			ar >> EndTime;
	}
}
