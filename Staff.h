#pragma once
#include <string>
#include <vector>

#include "ChildCompany.h"
#include "Department.h"

struct Staff {
    int ID;
    std::string surname;
    std::string givenName;
    ChildCompany childCompany;
    Department department;
    std::string position;
    std::string birth;
    std::string hometown;
    std::string address;
    std::string email;
    std::string phoneNumber;
    std::string startDate;
    std::vector<std::string> worktime;
};
