#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Staff {
	int ID;
	string surname;
	string givenName;
	string subCompany;
	string department;
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

// BKCorperation info
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
	if (name == "BKCorperation") return;
	for (auto& subCompany : subCompanies) {
		if (subCompany.name == name) return;
	}
	SubCompany newComp;
	newComp.name = name;
	subCompanies.push_back(newComp);
}

void checkDepartment(const string& name) {
	for (auto& department : departments) {
		if (department.name == name) return;
	}
	Department newDepartment;
	newDepartment.name = name;
	departments.push_back(newDepartment);
}

void checkPosition(Staff& staff) {
	// Todo: check position then add information to the corresponding corp/sub company/department
	// switch 
	// case Chủ tịch
	// case Phó chủ tịch
	// case Giám đốc
	// case Phó giám đốc
	// case Trưởng phòng
	// case Phó phòng
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
		getline(file, employee.subCompany);
		getline(file, employee.position);
		getline(file, employee.birth);
		getline(file, employee.hometown);
		getline(file, employee.address);
		getline(file, employee.email);
		getline(file, employee.phoneNumber);
		getline(file, employee.startDate);

		string worktimeLine;
		while (getline(file, buff) && !isID(buff)) {
			employee.worktime.push_back(buff);
		}

		staffs.push_back(employee);
		// TODO: check department
		checkSubCompany(employee.subCompany);
		checkPosition(employee);

		if (file.peek() == EOF) break;
	}

	file.close();
}

void addnewStaff() {
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
	getline(cin, newEmployee.subCompany);
	
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
	checkSubCompany(newEmployee.subCompany);
	// TODO: check department
	checkPosition(newEmployee);
}



string getStaffFullName(const Staff& staff) {
	return staff.surname + " " + staff.givenName;
}

void printDepartmentInfo(const Department& department) {
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "Department name: " << department.name;
	cout << "\Head: " << department.head.givenName;
	cout << "\nDeputy Head: " << department.deputyHead.givenName;
	cout << endl;
}

void printSubCompanyInfo(const SubCompany& subCompany) {
	cout << "-------------------------------------------------\n";
	cout << "Subsidiary company name: " << subCompany.name;
	cout << "\nDirector: " << subCompany.director.givenName;
	cout << "\nCo-Director: ";
	for (auto& coDirector : subCompany.coDirectors) {
		cout << coDirector.givenName;
		if (coDirector.ID != subCompany.coDirectors.back().ID) cout << " ,";
	}
	cout << endl;
}

void getBKCorpInfo() {
	cout << "Chairman name: " << chairman.givenName << "\nVice-Chairmen: ";
	for (auto& viceChairman : viceChairmen) {
		cout << viceChairman.givenName;
		if (viceChairman.ID != viceChairmen.back().ID) cout << " ,";
	}
	for (auto& subCompany : subCompanies) {
		printSubCompanyInfo(subCompany);
	}
	for (auto& department : departments) {
		printDepartmentInfo(department);
	}
	cout << "Total staff: " << staffs.size() << endl;
}


int main() {

}