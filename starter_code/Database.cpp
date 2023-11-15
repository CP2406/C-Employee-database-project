#include <iostream>
#include <stdexcept>
#include "my_debugger.h"
#include "Database.h"
#include <iomanip>

using namespace std;

namespace Records {

	Employee& Database::addEmployee(const string& firstName,
		const string& lastName)
	{
		log("started");
		Employee theEmployee(firstName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);
		log("end");
		return mEmployees[mEmployees.size() - 1];
	}
		
	Employee& Database::addEmployee(const string& firstName,
	const string& middleName,const string& lastName)
		{
			log("started");
			Employee theEmployee(firstName,middleName, lastName);
			theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
			theEmployee.hire();
			mEmployees.push_back(theEmployee);
			log("end");
			return mEmployees[mEmployees.size() - 1];
		}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : mEmployees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee& Database::getEmployee(const string& firstName, const string& lastName)
	{
		for (auto& employee : mEmployees) {
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto& employee : mEmployees) {
			employee.display();
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : mEmployees) {
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : mEmployees) {
			if (!employee.isHired())
				employee.display();
		}
	}

	void Database::saveToFile() const {
		string filename;
		cout << "Enter the filename: " << endl;
		cin >> filename;

	bool is_overwrite = false;
		cout << "Is overwriting? Enter 1 for Yes, 0 for No: "<< endl;
		cout << "Enter: ";
		cin >> is_overwrite;

		ofstream outFile{ filename.data(), is_overwrite ? ios_base::trunc : ios_base::app };		
		

		if (!outFile.is_open()) {
			cerr << "Unable to open file!" << endl;
			return;
		}

		for (const auto& employee : mEmployees) {
			// Quote all parts of the name to support spaces in names
			outFile << std::quoted(employee.getFirstName())
					<< std::quoted(employee.getMiddleName())
					<< std::quoted(employee.getLastName()) << std::endl;
		}
		if(is_overwrite){
			cout << "File overwritten successfully " << endl;
		}
		else
		{
			cout << "Data appended to the file. No overwriting performed." << endl;
		}
		
	}


	void Database::loadFromFile() const {
		string loadFile;
		cout << "Enter the name of load file: " << endl;
		cin >> loadFile;
		




	}



}
