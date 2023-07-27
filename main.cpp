#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#define CHUA_HOI_THAY_VE_DEPARTMENT true

using namespace std;

struct Staff {
	int ID;
	string surname;
	string givenName;
	string subCompanyName;
	string departmentName;
	string position;
	string birth;
	string hometown;
	string address;
	string email;
	string phoneNumber;
	string startDate;
	vector<string> worktime;
};

struct Department
{
	string name;
	Staff head;
	Staff deputyHead;
	vector<Staff> staffs;
};

struct SubCompany
{
	string name;
	Staff director;
	vector<Staff> coDirectors;
	vector<Department> departments;
};

// BKCorporation info
Staff chairman;
vector<Staff> viceChairmen;
vector<SubCompany> subCompanies;
vector<Department> departments;
vector<Staff> staffs;

// Check if the string is a valid staff id
bool isID(const string& str)
{
	// if the worktime date format always the same, we should change algorithm to:
	// return !(str.size() > 3 && str[2] == '/')
	// this is more efficient if format always the same
	return all_of(str.begin(), str.end(), ::isdigit);
}

// Check if a sub company existed, if not, add new
void checkSubCompany(const string& name) {
	if (name == "BKCorporation") return;
	for (auto& subCompany : subCompanies) {
		if (subCompany.name == name) return;
	}
	SubCompany newComp;
	newComp.name = name;
	subCompanies.push_back(newComp);
}

// add staff to the corresponding department, if department does not exist, create new then add
void addToDepartment(const string& name, const Staff& staff) {
	if (CHUA_HOI_THAY_VE_DEPARTMENT) return;
	for (auto& department : departments) {
		if (department.name == name) department.staffs.push_back(staff);
	}
	Department newDepartment;
	newDepartment.name = name;
	departments.push_back(newDepartment);
	newDepartment.staffs.push_back(staff);
}

// This will check the special position of the staff and add position info to the corresponding 
// sub company or department if missing
void checkPosition(Staff& staff) {
	auto& position = staff.position;

	if (position == "Chủ tịch") {
		chairman = staff;
	}
	else if (position == "Phó chủ tịch") {
		viceChairmen.push_back(staff);
	}
	else if (position == "Giám đốc") {
		for (auto& subCompany : subCompanies) {
			if (subCompany.name == staff.subCompanyName) {
				subCompany.director = staff;
			}
		}
		throw exception("SubCompany not found when adding director. Check add new staff logic and put checkSubCompany before checkPosition.");
	}
	else if (position == "Phó giám đốc") {
		for (auto& subCompany : subCompanies) {
			if (subCompany.name == staff.subCompanyName) {
				subCompany.coDirectors.push_back(staff);
			}
		}
		throw exception("SubCompany not found when adding co-director. Check add new staff logic and put checkSubCompany before checkPosition.");
	}
	else if (position == "Trưởng phòng") {
		for (auto& department : departments) {
			if (department.name == staff.departmentName) {
				department.head = staff;
			}
		}
		throw exception("Deparment not found when adding head. Check add new staff logic and put addToDepartment before checkPosition.");
	}
	else if (position == "Phó phòng") {
		for (auto& department : departments) {
			if (department.name == staff.departmentName) {
				department.deputyHead = staff;
			}
		}
		throw exception("Deparment not found when adding deputy head. Check add new staff logic and put addToDepartment before checkPosition.");
	}
}

void readFileAndAddStaff(const string& filename) {
	ifstream file(filename);

	if (!file) {
		cerr << "Can't open " << filename << "\n";
		return;
	}

	string buff;
	// Get the first line, which is ID, since while loop should not contain getline for ID
	getline(file, buff);
	while (true) {
		if (buff.empty()) {
			continue;
		}

		Staff employee;
		employee.ID = stoi(buff);

		getline(file, employee.surname);
		getline(file, employee.givenName);
		getline(file, employee.subCompanyName);
		getline(file, employee.position);
		getline(file, employee.birth);
		getline(file, employee.hometown);
		getline(file, employee.address);
		getline(file, employee.email);
		getline(file, employee.phoneNumber);
		getline(file, employee.startDate);

		while (getline(file, buff) && !isID(buff)) {
			employee.worktime.push_back(buff);
		}

		staffs.push_back(employee);
		checkSubCompany(employee.subCompanyName);
		addToDepartment(employee.departmentName, employee);
		checkPosition(employee);

		if (file.peek() == EOF) break;
	}

	file.close();
}

void addNewStaff() {
	Staff newEmployee;

	string input;

	cout << "Nhap ma so nhan vien: ";
	getline(cin, input);
	newEmployee.ID = stol(input);

	cout << "Nhap ho va ten dem: ";
	getline(cin, newEmployee.surname);

	cout << "Nhap ten: ";
	getline(cin, newEmployee.givenName);

	cout << "Nhap don vi: ";
	getline(cin, newEmployee.subCompanyName);
	
	cout << "Nhap chuc vu: ";
	getline(cin, newEmployee.position);

	cout << "Nhap ngay thang nam sinh: ";
	getline(cin, newEmployee.birth);

	cout << "Nhap que quan: ";
	getline(cin, newEmployee.hometown);

	cout << "Nhap dia chi: ";
	getline(cin, newEmployee.address);

	cout << "Nhap email: ";
	getline(cin, newEmployee.email);

	cout << "Nhap so dien thoai: ";
	getline(cin, newEmployee.phoneNumber);

	cout << "Nhap ngay bat dau lam viec: ";
	getline(cin, newEmployee.startDate);


	string worktimeLine;
	cout << "Nhap thong tin ve cong viec (ngay, thoi gian den, thoi gian ve).\n";
	cout << "Nhan Enter sau khi nhap xong. De ket thuc viec nhap, nhap 'END' va Enter.\n";
	cin.ignore();
	while (true) {
		getline(cin, worktimeLine);
		if (worktimeLine == "END") {
			break;
		}
		newEmployee.worktime.push_back(worktimeLine);
	}

	staffs.push_back(newEmployee);
	checkSubCompany(newEmployee.subCompanyName);
	addToDepartment(newEmployee.departmentName, newEmployee);
	checkPosition(newEmployee);
}

string getStaffFullName(const Staff& staff) {
	return staff.surname + " " + staff.givenName;
}

void printDepartmentInfo(const Department& department) {
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "Department name: " << department.name;
	cout << "\Head: " << getStaffFullName(department.head);
	cout << "\nDeputy Head: " << getStaffFullName(department.deputyHead);
	cout << endl;
}

void printSubCompanyInfo(const SubCompany& subCompany) {
	cout << "-------------------------------------------------\n";
	cout << "Subsidiary company name: " << subCompany.name;
	cout << "\nDirector: " << getStaffFullName(subCompany.director);
	cout << "\nCo-Director: ";
	for (auto& coDirector : subCompany.coDirectors) {
		cout << getStaffFullName(coDirector);
		if (coDirector.ID != subCompany.coDirectors.back().ID) cout << " ,";
	}
	cout << endl;
}

void getBKCorpInfo() {
	cout << "Chairman name: " << getStaffFullName(chairman) << "\nVice-Chairmen: ";
	for (auto& viceChairman : viceChairmen) {
		cout << getStaffFullName(viceChairman);
		if (viceChairman.ID != viceChairmen.back().ID) cout << " ,";
	}
	cout << "\n";
	for (auto& subCompany : subCompanies) {
		printSubCompanyInfo(subCompany);
	}
	cout << "\n";
	for (auto& department : departments) {
		printDepartmentInfo(department);
	}
	cout << "Total staff: " << staffs.size() << endl;
}


int main() {
	addNewStaff();
	getBKCorpInfo();
}