#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
#include <iomanip>

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
const int INDEX_NOT_FOUND = -1;

// Nhat Duc
// Check if the string is a valid staff id
bool checkDigit(string str) {
	for (const char& ch : str) {
		if (std::isdigit(ch) == 0)
			return false;
	}
	return true;
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
string trim(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

// Nhat Duc
string normalizeString(const string& str) {
	return trim(getLower(str));
}

// Nhat Duc
string getStaffFullName(const Staff& staff) {
	return staff.surname + " " + staff.givenName;
}

vector<string> toVecName(set<string> stringSet) {
	vector<string> vec;
	vec.assign(stringSet.begin(), stringSet.end());
	return vec;
}

// Nhat Duc
// Use to split the string format "BKCorperation/SubCompany/Department" to vector for easy parsing data
vector<string> splitComDepartment(string str) {
	vector<string> result;
	size_t pos = str.find('/');
	while (pos != string::npos) {
		result.push_back(str.substr(pos));
		str.erase(0, pos + 1);
		pos = str.find('/');
	}
	if (result.empty()) result.push_back(str);
	return result;
}

// Nhat Duc
Staff findStaffById(int id) {
	//for (const auto& staff : staffs) {
	//	if (staff.ID == id) return staff;
	//}
	//return INVALID_STAFF;
	try {
		return staffs.at(id - 1);
	}
	catch (out_of_range) {
		return INVALID_STAFF;
	}
}

// Nguyen Cong Duy
// Return empty vector if not found
vector<Staff> findStaffByName(string name) {
	vector<Staff> staffNameFound;
	for (int i = 0; i < staffs.size(); i++) {
		if (name == normalizeString(staffs[i].surname))
			staffNameFound.push_back(staffs[i]);
		else if (name == normalizeString(staffs[i].givenName))
			staffNameFound.push_back(staffs[i]);
		else if (name == normalizeString(getStaffFullName(staffs[i])))
			staffNameFound.push_back(staffs[i]);
	}
	return staffNameFound;
}

// Nguyen Duc Trong
// Return index -1 if staff is not exist
int getIndexByStaffID(int id) {
	for (int i = 0; i < staffs.size(); i++) {
		if (staffs.at(i).ID == id) return i;
	}
	return -1;
}

// Nhat Duc
// Return empty vec if not found
vector<string> getAllSubCompanyName() {
	set<string> result;
	for (const auto& staff : staffs) {
		if (staff.subCompanyName.empty()) continue;
		result.insert(staff.subCompanyName);
	}
	return toVecName(result);
}

// Nhat Duc
// Return empty vec if not found
vector<string> getAllDepartmentName() {
	set<string> result;
	for (const auto& staff : staffs) {
		if (staff.departmentName.empty()) continue;
		result.insert(staff.departmentName);
	}
	return toVecName(result);
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
		if (staff.subCompanyName == companyName && normalizeString(staff.position) == "co-director")
			result.push_back(staff);
	}
	return result;
}

// Nhat Duc
Staff findDirector(string companyName) {
	for (const auto& staff : staffs) {
		if (staff.subCompanyName == companyName && normalizeString(staff.position) == "director")
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
		if (staff.departmentName == departmentName && normalizeString(staff.position) == "deputy head")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
Staff findHead(string departmentName) {
	for (const auto& staff : staffs) {
		if (staff.departmentName == departmentName && normalizeString(staff.position) == "head")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
Staff findChairman() {
	for (const auto& staff : staffs) {
		if (normalizeString(staff.position) == "chairman")
			return staff;
	}
	return INVALID_STAFF;
}

// Nhat Duc
// Return empty vector if not found
vector<Staff> getAllViceChairmen() {
	vector<Staff> result;
	for (const auto& staff : staffs) {
		if (normalizeString(staff.position) == "vice chairman")
			result.push_back(staff);
	}
	return result;
}

// Nhat Duc
bool staffExisted(int id) {
	return !compareStaff(findStaffById(id), INVALID_STAFF);
}

// Ng Quang Son
void readFileAndAddStaff(const string& filename) {
	ifstream file(filename);

	if (!file) {
		cout << "Can not open file " << filename << endl;
		return;
	}
	bool flag = true;
	int id;
	string line;
	while (file.eof() == false) {
		Staff employee;

		// Save the ID of the first employee
		if (flag) {
			getline(file, line);
			employee.ID = stoi(line);
			flag = false;
		}
		else {
			employee.ID = id;
		}

		getline(file, employee.surname);
		getline(file, employee.givenName);

		getline(file, line);
		int numSlashes = count(line.begin(), line.end(), '/');

		// No subcompany and department
		if (numSlashes == 0) {
			employee.subCompanyName = "";
			employee.departmentName = "";
		}
		// Either subcompany or department
		else if (numSlashes == 1) {
			string temp = "";
			// Index 14 is the position of the first letter after the first '/'
			for (int i = 14; i < line.size(); i++) {
				temp += line[i];
			}
			// Determine if the string after the first '/' is subcompany or department
			if (temp.find("BK") != string::npos) {
				employee.subCompanyName = temp;
				employee.departmentName = "";
			}
			else {
				employee.subCompanyName = "";
				employee.departmentName = temp;
			}
		}
		// Both subcompany and department
		else {
			string subcompany = "";
			string department = "";
			int i;
			for (i = 14; line[i] != '/'; i++) {
				subcompany += line[i];
			}
			// 'i' is now at the position of '/' so we need to +1
			for (i = i + 1; i < line.size(); i++) {
				department += line[i];
			}
			employee.subCompanyName = subcompany;
			employee.departmentName = department;
		}

		getline(file, employee.position);
		getline(file, employee.birth);
		getline(file, employee.hometown);
		getline(file, employee.address);
		getline(file, employee.email);
		getline(file, employee.phoneNumber);
		getline(file, employee.startDate);

		while (getline(file, line) && !line.empty()) {
			// Check if the line contains work time
			if (line.find(',') != string::npos) {
				employee.worktime.push_back(line);
			}
			// If not, it's an ID
			else {
				// Don't save directly to employee.ID because the new employee object hasn't been created yet
				if (checkDigit(line)) {
					id = stoi(line);
				}
				break;
			}
		}

		staffs.push_back(employee);
	}

	file.close();

}

// Ng Quang Son
void addNewStaff(string filename) {
	Staff newEmployee;

	string input;

	newEmployee.ID = staffs.size() + 1;
	cout << "Adding infomation for staff ID: " << newEmployee.ID << endl;

	cout << "Enter surname: ";
	getline(cin, newEmployee.surname);

	cout << "Enter given name: ";
	getline(cin, newEmployee.givenName);

	cout << "Enter company: ";
	getline(cin, newEmployee.subCompanyName);

	if (newEmployee.subCompanyName == "BKCorporation") {
		newEmployee.subCompanyName = "";
	}

	cout << "Enter department: ";
	getline(cin, newEmployee.departmentName);

	cout << "Enter position: ";
	getline(cin, newEmployee.position);

	cout << "Enter birth date: ";
	getline(cin, newEmployee.birth);

	cout << "Enter hometown: ";
	getline(cin, newEmployee.hometown);

	cout << "Enter address: ";
	getline(cin, newEmployee.address);

	cout << "Enter email: ";
	getline(cin, newEmployee.email);

	cout << "Enter phone number: ";
	getline(cin, newEmployee.phoneNumber);

	cout << "Enter start date: ";
	getline(cin, newEmployee.startDate);

	string worktimeLine;
	cout << "Enter work time information (date, start time, end time).\n";
	cout << "Press Enter after each input. To finish, enter 'END' and press Enter.\n";

	while (true) {
		getline(cin, worktimeLine);
		if (worktimeLine == "END") {
			break;
		}
		newEmployee.worktime.push_back(worktimeLine);
	}

	staffs.push_back(newEmployee);
/*  Tính năng thêm vào file này đang bàn bạc, xóa comment nếu muốn thử
	ofstream file(filename, ios::app | ios::binary);
	// Use \r\n instead of \n to make the file format consistant when using CRLF
	if (file.is_open()) {
		file << newEmployee.ID << "\r\n";
		file << newEmployee.surname << "\r\n";
		file << newEmployee.givenName << "\r\n";

		file << "BKCorporation";
		if (newEmployee.subCompanyName == "" && newEmployee.departmentName == "") {
			file << "\r\n";
		}
		else if (newEmployee.subCompanyName == "") {
			file << "/" << newEmployee.departmentName << "\r\n";
		}
		else if (newEmployee.departmentName == "") {
			file << "/" << newEmployee.subCompanyName << "\r\n";
		}
		else {
			file << "/" << newEmployee.subCompanyName << "/" << newEmployee.departmentName << "\r\n";
		}

		file << newEmployee.position << "\r\n";
		file << newEmployee.birth << "\r\n";
		file << newEmployee.hometown << "\r\n";
		file << newEmployee.address << "\r\n";
		file << newEmployee.email << "\r\n";
		file << newEmployee.phoneNumber << "\r\n";
		file << newEmployee.startDate << "\r\n";
		for (int i = 0; i < newEmployee.worktime.size(); i++) {
			file << newEmployee.worktime[i] << "\r\n";
		}
		file.close();
	}
	else {
		cout << "Can not open file " << endl;
	}
*/
}

// Trong
void printDepartmentInfo(const string& department) {
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "Department name: " << department;
	cout << "\nHead: " << getStaffFullName(findHead(department));
	cout << "\nDeputy Head: " << getStaffFullName(findDeputyHead(department));
	cout << endl;
}

// Duy
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

// Duc
void printBKCorpInfo() {
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

// Khanh
// tính số giờ đi muộn
int lateCounter(int ID) {
	int i;
	int res = 0;
	for (string s : staffs[ID - 1].worktime) {
		string giodilam = "";
		string giodive = "";
		string phutdilam = "";
		bool flag = true;
		for (i = 11; s[i] != ','; i++) {
			if (s[i] == ':') {
				flag = false;
				continue;
			}
			if (flag) {
				giodilam += s[i];
			}
			else {
				phutdilam += s[i];
			}
		}
		if (checkDigit(giodilam) && stoi(giodilam) - 8 > 0) {
			res += stoi(giodilam) - 8;
		}
		else if (checkDigit(giodilam) && stoi(giodilam) - 8 == 0 && checkDigit(phutdilam) && stoi(phutdilam) != 0) {
			res++;
		}
		for (i = i + 1; s[i] != ':'; i++) {
			giodive += s[i];
		}
		if (checkDigit(giodive) && 17 - stoi(giodive) > 0) {
			res += 17 - stoi(giodive);
		}
	}
	return res;
}

// Khanh
void printStaffWorkingHours(int ID) {
	for (string s : staffs.at(ID - 1).worktime) {
		cout << s << endl;
	}
}

// Ng Duc Trong
void updateStaff(int staffID) {
	int index = getIndexByStaffID(staffID);
	int update;
	string newInfor;
	char choice;

	if (INDEX_NOT_FOUND == index) {
		cout << "Cannot find the staff ID you've given. Stop updating staff.\n";
		return;
	}

	// print staff info
	cout << " Staff information: " << endl;
	cout << " 1. Staff surname: " << staffs.at(index).surname << endl;
	cout << " 2. Staff givenname: " << staffs.at(index).givenName << endl;
	cout << " 3. Staff subcompanyname: " << staffs.at(index).subCompanyName << endl;
	cout << " 4. Staff departmentname: " << staffs.at(index).departmentName << endl;
	cout << " 5. Staff position: " << staffs.at(index).position << endl;
	cout << " 6. Staff birth: " << staffs.at(index).birth << endl;
	cout << " 7. Staff hometown: " << staffs.at(index).hometown << endl;
	cout << " 8. Staff address: " << staffs.at(index).address << endl;
	cout << " 9. Staff email: " << staffs.at(index).email << endl;
	cout << " 10. Staff phonenumber: " << staffs.at(index).phoneNumber << endl;
	cout << " 11. Staff startDate: " << staffs.at(index).startDate << endl;
	cout << " 12. Staff worktime: \n"; 
	printStaffWorkingHours(staffID);

	// ask which staff info to update
	do {
		cout << " What information do you want to update? : " << endl;
		cout << " 1.SurName" << endl;
		cout << " 2.GivenName" << endl;
		cout << " 3.SubCompanyName" << endl;
		cout << " 4.DepartmentName" << endl;
		cout << " 5.Position" << endl;
		cout << " 6.Birth" << endl;
		cout << " 7.Hometown" << endl;
		cout << " 8.Address" << endl;
		cout << " 9.Email" << endl;
		cout << " 10.PhoneNumber" << endl;
		cout << " 11.StartDate" << endl;
		cout << " 12.Worktinme" << endl;
		cin >> update;
		cin.ignore();
		switch (update) {
		case 1:
			cout << " Enter new surName ";
			getline(cin, newInfor);
			staffs.at(index).surname = newInfor;
			break;
		case 2:
			cout << " Enter new givenName ";
			getline(cin, newInfor);
			staffs.at(index).givenName = newInfor;
			break;
		case 3:
			cout << " Enter new subCompanyName ";
			getline(cin, newInfor);
			staffs.at(index).subCompanyName = newInfor;
			break;
		case 4:
			cout << " Enter new departmentName ";
			getline(cin, newInfor);
			staffs.at(index).departmentName = newInfor;
			break;
		case 5:
			cout << " Enter new position ";
			getline(cin, newInfor);
			staffs.at(index).position = newInfor;
			break;
		case 6:
			cout << " Enter new birth ";
			getline(cin, newInfor);
			staffs.at(index).birth = newInfor;
			break;
		case 7:
			cout << " Enter new hometown ";
			getline(cin, newInfor);
			staffs.at(index).hometown = newInfor;
			break;
		case 8:
			cout << " Enter new address ";
			getline(cin, newInfor);
			staffs.at(index).address = newInfor;
			break;
		case 9:
			cout << " Enter new email ";
			getline(cin, newInfor);
			staffs.at(index).email = newInfor;
			break;
		case 10:
			cout << " Enter new phoneNumber ";
			getline(cin, newInfor);
			staffs.at(index).phoneNumber = newInfor;
			break;
		case 11:
			cout << " Enter new startDate ";
			getline(cin, newInfor);
			staffs.at(index).surname = newInfor;
			break;
		case 12: { // vector causes some problem for normal switch case, so curly brace is needed here
			cout << " Enter new worktime and type 'END' then enter to finish: ";
			string buff;
			vector<string> worktimes;
			while (buff != "END") {
				if (!buff.empty()) worktimes.push_back(buff);
				getline(cin, buff);
			}
			staffs.at(index).worktime = worktimes;
			break;
		}
		default:
			cout << "Invalid choice!\n";
			break;
		}
		cout << " Do you want to continue to update information? (y = Yes, n = no)" << endl;
		cin >> choice;
		cin.ignore();
	} while (choice == 'y' || choice == 'Y');

	// print the info to check the new updated info
	cout << " Update staff information: " << endl;
	cout << " 1. Staff surname: " << staffs.at(index).surname << endl;
	cout << " 2. Staff givenname: " << staffs.at(index).givenName << endl;
	cout << " 3. Staff subcompanyname: " << staffs.at(index).subCompanyName << endl;
	cout << " 4. Staff departmentname: " << staffs.at(index).departmentName << endl;
	cout << " 5. Staff position: " << staffs.at(index).position << endl;
	cout << " 6. Staff birth: " << staffs.at(index).birth << endl;
	cout << " 7. Staff hometown: " << staffs.at(index).hometown << endl;
	cout << " 8. Staff address: " << staffs.at(index).address << endl;
	cout << " 9. Staff email: " << staffs.at(index).email << endl;
	cout << " 10. Staff phonenumber: " << staffs.at(index).phoneNumber << endl;
	cout << " 11. Staff startDate: " << staffs.at(index).startDate << endl;
	cout << " 12. Staff worktime: \n";
	printStaffWorkingHours(staffID);
}


// Ng Cong Duy
void showStaffInfo(string staffName) {
	vector<Staff> found = findStaffByName(staffName);
	if (found.size() == 0)
		cout << "The employee you are looking for does not exist!!!\n";
	else {
		for (auto& x : found) {
			cout << "ID: " << x.ID << endl;
			cout << "Surname: " << x.surname << endl;
			cout << "Given Name: " << x.givenName << endl;
			cout << "Subsidiary Company: " << x.subCompanyName << endl;
			cout << "Departement: " << x.departmentName << endl;
			cout << "Position: " << x.position << endl;
			cout << "Date of Birth: " << x.birth << endl;
			cout << "Hometown: " << x.hometown << endl;
			cout << "Address: " << x.address << endl;
			cout << "Email: " << x.email << endl;
			cout << "Phone Number: " << x.phoneNumber << endl;
			cout << "Working starts at " << x.startDate << endl;
		}
	}
}

// Phuong
void showUnitInfo() {
	string unitName;
	// Clear the console screen
	system("cls");

	// Get lists of subsidiary companies and departments
	vector<string> subsidiaryCompanies = getAllSubCompanyName();
	vector<string> departments = getAllDepartmentName();

	// Sort the lists in alphabetical order
	sort(subsidiaryCompanies.begin(), subsidiaryCompanies.end());
	sort(departments.begin(), departments.end());

	// Set column width for the table
	int columnWidth = 50;

	// Display the header for the table
	cout << "+--------------------------------------------------+--------------------------------------------------+" << endl;
	cout << "|   Available Subsidiary Companies                 |   Available Departments                          |" << endl;
	cout << "+--------------------------------------------------+--------------------------------------------------+" << endl;

	// Calculate the maximum number of rows needed
	size_t maxRows = max(subsidiaryCompanies.size(), departments.size());

	for (size_t i = 0; i < maxRows; i++) {
		cout << "|";
		if (i < subsidiaryCompanies.size()) {
			cout << " " << setw(columnWidth - 2) << left << subsidiaryCompanies[i];
		}
		else {
			cout << " " << setw(columnWidth - 2) << left << "";
		}

		cout << " | ";

		if (i < departments.size()) {
			cout << " " << setw(columnWidth - 2) << left << departments[i];
		}
		else {
			cout << " " << setw(columnWidth - 2) << left << "";
		}
		cout << "|" << endl;
	}
	cout << "+--------------------------------------------------+--------------------------------------------------+" << endl;

	// Ask user to enter a choice
	string choice;
	cout << "1. Search subsidiary company \n"
		<< "2. Search department \n"
		<< "Enter your choice: ";
	cin >> choice;
	cin.ignore();

	if (choice == "1") {
		cout << "Enter a subsidiary company: ";
		getline(cin, unitName);
		printSubCompanyInfo(unitName);
	}
	else if (choice == "2") {
		cout << "Enter a Department Name: ";
		getline(cin, unitName);
		printDepartmentInfo(unitName);
	}
	else {
		cout << "Invalid choice \n";
	}
}

int main() {
	readFileAndAddStaff("employee_data.txt");
	string input;
	int inputID;
	while (true) {
		cout << "EMPLOYEE MANAGEMENT SYSTEM OF BKCORPORATION \n" \
			<< "1. Display information about BKCorporation \n" \
			<< "2. Find the information of employee \n" \
			<< "3. Show the employee's working status \n" \
			<< "4. Show information about a subsidiary company or department \n" \
			<< "5. Add new employee \n" \
			<< "6. Update information of employee \n" \
			<< "7. Exit \n"; \
			cout << "Enter the choice: ";
		getline(cin, input);
		if (input == "1") {
			system("cls");
			printBKCorpInfo();
		}
		else if (input == "2") {
			cout << "Enter the name of employee you want to find: ";
			getline(cin, input);
			showStaffInfo(input);
		}
		else if (input == "3") {
			cout << "Enter the id of the employee you want to show status: ";
			cin >> inputID;
			printStaffWorkingHours(inputID);
			cout << "Total hour(s) late: " << lateCounter(inputID) << endl;
		}
		else if (input == "4") {
			showUnitInfo();
		}
		else if (input == "5") {
			system("cls");
			addNewStaff("employee_data.txt");
		}
		else if (input == "6") {
			cout << "Enter the id of the employee you want to update: ";
			cin >> inputID;
			updateStaff(inputID);
		}
		else if (input == "7") {
			exit(0);
		}
		else {
			cout << "Invalid choice \n";
		}
		cout << "Press any key to continue...";
		cin.ignore();
		system("cls");
	}
}