#pragma once
class Employee :public CObject
{
	CString image;
	CString num;
	CString name;
	CString dept;
	CString posit;
	CString phone;
	CString ext;
	CString address;

	CString StartTime;
	CString EndTime;

public :
	Employee(CString image, CString num, CString name, CString dept,
		CString posit, CString phone, CString ext, CString address, CString starttime, CString endtime);

	Employee(CArchive& ar);
	
	CString Getimage();
	CString Getnum();
	CString Getname();
	CString Getdept();
	CString Getposit();
	CString Getphone();
	CString Getext();
	CString Getaddress();
	CString GetStartTime();
	CString GetEndTime();

	void SetImage(CString image);
	void SetNum(CString num);
	void SetName(CString name);
	void SetDept(CString dept);
	void SetPosit(CString posit);
	void SetPhone(CString phone);
	void SetExt(CString ext);
	void SetAddress(CString address);

	void SetStartTime(CString StartTime);
	void SetEndTime(CString EndTime);

	virtual void Serialize(CArchive& ar);
};

