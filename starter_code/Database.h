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
		Employee& addEmployee(Employee& emp1);	
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
		void saveToFile() const;
		void loadFromFile();
		void searchMenu() const;
		// Database searchByFirstName() const;
	
	

	private:
		std::vector<Employee> mEmployees;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
		enum class SearchOption{
			BY_FIRST,BY_MIDDLE,BY_LAST,BY_ADDRESS

		};
		Database searchBy(SearchOption op) const;
	};
}
