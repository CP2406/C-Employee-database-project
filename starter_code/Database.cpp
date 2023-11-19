#include <iostream>
#include <stdexcept>
#include "my_debugger.h"
#include "Database.h"
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>

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

	void Database::saveToFile() const 
		{
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
				outFile << quoted(employee.getFirstName())
						<< quoted(employee.getMiddleName())
						<< quoted(employee.getLastName())<<endl;
				}

			if(is_overwrite) {
					cout << "File overwritten successfully " << endl;
				}

				else {
					cout << "Data appended to the file. No overwriting."<<endl;
				}
		}

	void Database::loadFromFile() 
		{
			string loadFile;
			vector<Employee> nEmployees;  // Create vector type employees container
			cout << "Enter the name of load file: " << endl;
			cin >> loadFile;
			ifstream inFile{ loadFile.data() };
			if (!inFile) {
				string errorString = "Cannot open file: ";
				throw runtime_error(errorString);
				}

			while (inFile) 
				{
					// Read line by line
					//skip empty lines.
					string line;
					getline(inFile, line);
					if (!inFile && !inFile.eof()) {
						throw runtime_error{ "Failed to read line from file." };
						}

					if (line.empty()) { // Skip empty lines
						continue;
						}
					// Make a string stream and parse it.
					
					istringstream inLine(line);
					string nfirstName, nmiddleName, nlastName;
					inLine >> quoted(nfirstName) >> quoted(nmiddleName) >> quoted(nlastName);

					if (inLine.bad()) {
							throw runtime_error{ "Error reading person. Ignoring." };
							continue;
						}
						// Create a employee and add it to the database nEmployees.
					nEmployees.push_back(Employee{nfirstName, nmiddleName, nlastName});
				}

			if (inFile.bad()) 
				{
					throw runtime_error{ "Error reading employee. Ignoring." };
				}
			
			int count=0; // Loading index
			// loading all the employees
			for (const auto& employee : nEmployees) 
				{
					count+=1;
					cout << "Employee Loading "<<count<<": "<< employee.getFirstName() << " " 
					<< employee.getMiddleName() << " " << employee.getLastName() << endl;
				}

		} 

}