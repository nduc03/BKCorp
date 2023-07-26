#pragma once
#include <string>
#include <vector>

#include "Staff.h"
#include "ChildCompany.h"

struct Department
{
	std::string name;
	ChildCompany childCompany;
	Staff head;
	Staff deputyHead;
	std::vector<Staff> staffs;
};