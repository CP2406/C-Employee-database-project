#pragma once

#include <iostream>
#include <vector>
// #include "my_debugger.h"
#include "Employee.h"

namespace Records {
	const int kFirstEmployeeNumber = 1000;

	class Database
	{
	public:
		Employee& addEmployee(const std::string& firstName,
							  const std::string& lastName);						  		  
		Employee& addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName);

		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;
		// void makeNewDatabase();

	private:
		std::vector<Employee> mEmployees;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
	};
}
