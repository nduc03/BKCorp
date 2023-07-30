#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Ng Quang Son
struct Staff {
	int ID = -1;
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

vector<Staff> staffs;
const Staff INVALID_STAFF = Staff();

// Nhat Duc
// Check if the string is a valid staff id
bool isID(const string& str)
{
	// if the worktime date format always the same, we should change algorithm to:
	// return !(str.size() > 3 && str[2] == '/')
	// this is more efficient if format always the same
	return all_of(str.begin(), str.end(), ::isdigit);
}

// Nhat Duc
// Used to check if they are the same staff
// To check whether findStaffByID() can found Staff or not, use this statement:
// comparesStaff(findStaffByID(some_id_here), INVALID_STAFF)
// Return true means that Staff does not exist
bool compareStaff(const Staff& staff1, const Staff& staff2) {
	return staff1.ID == staff2.ID;
}

// Nhat Duc
string getLower(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
 
// Nhat Duc
string trim(const string& value) {
	string result = value;
	result.erase(0, result.find_first_not_of(' '));
	auto offset = result.find_first_of(' ');
	result.erase(offset, result.size() - offset);
	return result;
}

// Nhat Duc
string normalizeString(const string& str) {
	return trim(getLower(str));
}

// Nhat Duc
string getStaffFullName(const Staff& staff) {
	return staff.surname + " " + staff.givenName;
}

// Nhat Duc
// Use to split the string format "BKCorperation/SubCompany/Department" to vector for easy parsing data
vector<string> splitComDepartment(string str) {
	vector<string> result;
	size_t pos;
	do {
		pos = str.find('/');
		result.push_back(str.substr(pos));
		str.erase(0, pos + 1);
	} while (pos != string::npos);
	return result;
}

// Nhat Duc
Staff findStaffById(int id) {
	for (const auto& staff : staffs) {
		if (staff.ID == id) return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
// Return empty vector if not found
vector<Staff> findStaffByName(const string& name) {
	auto normalizedName = normalizeString(name);
	vector<Staff> result;

	for (const auto& staff : staffs) {
		if (normalizeString(staff.surname) == normalizedName) result.push_back(staff);
		if (normalizeString(staff.givenName) == normalizedName) result.push_back(staff);
		if (normalizeString(getStaffFullName(staff)) == normalizedName) result.push_back(staff);
	}
	return result;
}

// Nhat duc
// Return index -1 if staff is not exist
int getIndexByStaffID(int id) {
	for (int i = 0; i < staffs.size(); i++) {
		if (staffs.at(i).ID == id) return i;
	}
	return -1;
}

// Nhat Duc
// Return empty vector if not found
vector<string> getAllSubCompanyName() {
	vector<string> result;
	for (const auto& staff : staffs) {
		if (find(result.begin(), result.end(), staff.subCompanyName) != result.end())
			result.push_back(staff.subCompanyName);
	}
	return result;
}

// Nhat Duc
// Return empty vector if not found
vector<string> getAllDepartmentName() {
	vector<string> result;
	for (const auto& staff : staffs) {
		if (find(result.begin(), result.end(), staff.departmentName) != result.end())
			result.push_back(staff.departmentName);
	}
	return result;
}

// Nhat Duc
// Return empty vector if not found
vector<Staff> getAllStaffSubCompany(string companyName) {
	vector<Staff> result;
	for (const auto& staff : staffs) {
		if (staff.subCompanyName == companyName) result.push_back(staff);
	}
	return result;
}

// Nhat Duc
// Return empty vector if not found
vector<Staff> getAllCoDirector(string companyName) {
	vector<Staff> result;
	for (const auto& staff : staffs) {
		if (staff.subCompanyName == companyName && normalizeString(staff.position) == "phó giám đốc")
			result.push_back(staff);
	}
	return result;
}

// Nhat Duc
Staff findDirector(string companyName) {
	for (const auto& staff : staffs) {
		if (staff.subCompanyName == companyName && normalizeString(staff.position) == "giám đốc")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
// Return empty vector if not found
vector<Staff> getAllStaffDepartment(string departmentName) {
	vector<Staff> result;
	for (const auto& staff : staffs) {
		if (staff.departmentName == departmentName) result.push_back(staff);
	}
	return result;
}

// Nhat Duc
Staff findDeputyHead(string departmentName) {
	for (const auto& staff : staffs) {
		if (staff.departmentName == departmentName && normalizeString(staff.position) == "phó phòng")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
Staff findHead(string departmentName) {
	for (const auto& staff : staffs) {
		if (staff.departmentName == departmentName && normalizeString(staff.position) == "trưởng phòng")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
Staff findChairman() {
	for (const auto& staff : staffs) {
		if (normalizeString(staff.position) == "chủ tịch")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
// Return empty vector if not found
vector<Staff> getAllViceChairmen() {
	vector<Staff> result;
	for (const auto& staff : staffs) {
		if (normalizeString(staff.position) == "phó chủ tịch")
			result.push_back(staff);
	}
	return result;
}

// Nhat Duc
bool staffNotExisted(int id) {
	return compareStaff(findStaffById(id), INVALID_STAFF);
}

// Ng Quang Son & Nhat Duc
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
		getline(file, buff);
		try {
			auto comDepart = splitComDepartment(buff);
			employee.subCompanyName = comDepart.at(1);
			employee.departmentName = comDepart.at(2);
		}
		catch (out_of_range) {
			// Do nothing, just ignore error.
		}
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

		if (file.peek() == EOF) break;
	}

	file.close();
}

// Ng Quang Son & Nhat Duc
void addNewStaff() {
	Staff newEmployee;

	string input;

	cout << "Nhap ma so nhan vien: ";
	getline(cin, input);
	newEmployee.ID = stoi(input);

	if (staffNotExisted(newEmployee.ID)) {
		cout << "ID staff existed, cannot add";
		return;
	}

	cout << "Nhap ho va ten dem: ";
	getline(cin, newEmployee.surname);

	cout << "Nhap ten: ";
	getline(cin, newEmployee.givenName);

	cout << "Nhap cong ty con: ";
	getline(cin, newEmployee.subCompanyName);

	cout << "Nhap don vi phong ban: ";
	getline(cin, newEmployee.departmentName);

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
}

// Nhat Duc
void printDepartmentInfo(const string& department) {
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "Department name: " << department;
	cout << "\nHead: " << getStaffFullName(findHead(department));
	cout << "\nDeputy Head: " << getStaffFullName(findDeputyHead(department));
	cout << endl;
}

// Nhat Duc
void printSubCompanyInfo(const string& subCompany) {
	cout << "-------------------------------------------------\n";
	cout << "Subsidiary company name: " << subCompany;
	cout << "\nDirector: " << getStaffFullName(findDirector(subCompany));
	cout << "\nCo-Director: ";
	auto allCoDirector = getAllCoDirector(subCompany);
	for (const auto& coDirector : allCoDirector) {
		cout << getStaffFullName(coDirector);
		if (coDirector.ID != allCoDirector.back().ID) cout << " ,";
	}
	cout << endl;
}

// Nhat Duc
void getBKCorpInfo() {
	cout << "Chairman name: " << getStaffFullName(findChairman()) << "\nVice-Chairmen: ";
	auto allViceChairmen = getAllViceChairmen();
	for (const auto& viceChairman : allViceChairmen) {
		cout << getStaffFullName(viceChairman);
		if (viceChairman.ID != allViceChairmen.back().ID) cout << " ,";
	}
	cout << "\n";
	for (const auto& subCompany : getAllSubCompanyName()) {
		printSubCompanyInfo(subCompany);
	}
	cout << "\n";
	for (const auto& department : getAllDepartmentName()) {
		printDepartmentInfo(department);
	}
	cout << "Total staff: " << staffs.size() << endl;
}

// Nhat Duc
void saveAllStaffToFile() {

}

// Someone
void randomTime() {

}

// Nhat Duc & Quang Son
int timeOffset(string timeString) {

}

// Ng Duc Trong
void updateStaff(int staffID) {

}

// Ng Cong Duy
void showStaffInfo(string staffName) {

}

// Khanh
void printStaffWorkingHours(int staffID) {

}

// Phuong
void showUnitInfo(string UnitName) {

}

int main() {
	// làm sau cùng 
	// hoặc làm nháp để test hàm có hoạt động đúng ko
}