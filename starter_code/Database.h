#pragma once

#include <iostream>
#include <vector>
// #include "my_debugger.h"
#include "Employee.h"

namespace Records {
	const int kFirstEmployeeNumber = 1000;
	const int kFirstUerId =0;
	const std::string KFirstPassword{"admin"};

	class Database
	{
	public:
		Employee& addEmployee(Employee& emp1);	
			

		Employee& addEmployee(const std::string& firstName,
							  const std::string& lastName);	

		Employee& createUser(const int& id, const std::string& password);//稍后删除

		Employee& addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName);
		Employee& addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName,const int& id, const std::string& password);

		Employee& getEmployee(int employeeNumber);

		Employee& getUser(int UserIdNumber);
		
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;
		void saveToFile() const;
		void loadFromFile();
		void searchMenu() const;
		void loginMenu();
	

	private:
		std::vector<Employee> mEmployees;
		std::vector<Employee> mUsers;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
		int mNextUserId = kFirstUerId;
		std::string mNextUserPassword=KFirstPassword;
		enum class SearchOption{
			BY_FIRST,BY_MIDDLE,BY_LAST,BY_ADDRESS

		};
		Database searchBy(SearchOption op) const;
	};
}
