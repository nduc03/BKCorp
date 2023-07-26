#pragma once
#include <string>
#include <vector>

#include "Staff.h"
#include "Department.h"

struct ChildCompany
{
    std::string name;
    Staff director;
    std::vector <Staff> coDirectors;
    std::vector<Department> departments;
};
