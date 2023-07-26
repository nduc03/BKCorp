#include <iostream>
#include <vector>
#include <string>

#include "ChildCompany.h"
#include "Department.h"
#include "Staff.h"

using namespace std;

struct BKCorp {
	Staff chairman;
	vector<Staff> viceChairmen;
	vector<ChildCompany> childCompanies;
	vector<Department> departments;
	vector<Staff> staffs;
};

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

void printChildCompanyInfo(const ChildCompany& childCompany) {
	cout << "-------------------------------------------------\n";
	cout << "Child company name: " << childCompany.name;
	cout << "\nDirector: " << childCompany.director.givenName;
	cout << "\nCo-Director: ";
	for (auto& coDirector : childCompany.coDirectors) {
		cout << coDirector.givenName;
		if (coDirector.ID != childCompany.coDirectors.back().ID) cout << " ,";
	}
	cout << endl;
}

void getBKCorpInfo(const BKCorp& bkCorp) {
	cout << "Chairman name: " << bkCorp.chairman.givenName << "\nVice-Chairmen: ";
	for (auto& viceChairman : bkCorp.viceChairmen) {
		cout << viceChairman.givenName;
		if (viceChairman.ID != bkCorp.viceChairmen.back().ID) cout << " ,";
	}
	for (auto& childCompany : bkCorp.childCompanies) {
		printChildCompanyInfo(childCompany);
	}
	for (auto& department : bkCorp.departments) {
		printDepartmentInfo(department);
	}
	cout << "Total staff: " << bkCorp.staffs.size() << endl;
}


int main() {

}