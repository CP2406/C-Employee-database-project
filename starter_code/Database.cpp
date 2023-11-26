#include <iostream>
#include <stdexcept>
#include "my_debugger.h"
#include "Database.h"
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <algorithm>


using namespace std;

namespace Records {
		Employee& Database::addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName,const int& id, const std::string& password){
			log("started");
			Employee theEmployee(firstName, middleName,lastName,id,password);
			theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
			theEmployee.hire();
			theEmployee.setId(mNextUserId++);
			theEmployee.setPassword(mNextUserPassword);//set all password same as default
			mEmployees.push_back(theEmployee);
			log("end");
			return mEmployees[mEmployees.size() - 1];//暂时不改到mUser
			}

	Employee& Database::createUser(const int& id, const std::string& password)
		{
			log("started");
			Employee theUser(id, password);
			theUser.setId(mNextUserId++);
			theUser.setPassword(mNextUserPassword);//set all password same as default
			mUsers.push_back(theUser);
			log("end");
			return mUsers[mUsers.size() - 1];
		}

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

	Employee& Database::getUserFromId(int userId)
	{
		for (auto& user : mUsers) {
			if (user.getId()==userId) {
				return user;
			}
		}
		throw logic_error("No User found.");
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

	void Database::removeEmployee(int employeeNumber) {
        auto it = std::remove_if(mUsers.begin(), mUsers.end(),
            [employeeNumber](const Employee& emp) { return emp.getId() == employeeNumber; });

        if (it != mUsers.end()) {
            mUsers.erase(it, mUsers.end());
        } else {
            throw std::logic_error("Employee not found");
        }
    }

	string getSearchString(){
		string searchTag;
		cout << "Enter search string here-->" << endl;
		cin >> searchTag;
		return searchTag;

	}
	

	int displayseachMenu()
		{
			int selection;

			cout << endl;
			cout << "Search Employee Database" << endl;
			cout << "-----------------" << endl;
			cout << "1) Search by first name" << endl;
			cout << "2) Search by middle name" << endl;
			cout << "3) Search by last name" << endl;
			cout << "4) Search by address" << endl;
			cout << "0) Quit" << endl;
			cout << endl;
			cout << "---> ";
			
			cin >> selection;
			
			return selection;
		}

	void Database::searchMenu() const{
	bool done = false;
	Database searchResults;
	while (!done) {
		int selection = displayseachMenu();
		switch (selection) {
		case 0:
            log("case 0");
			done = true;
			break;
		case 1:
			searchResults=searchBy(SearchOption::BY_FIRST);
			break;
		case 2:
			searchResults=searchBy(SearchOption::BY_MIDDLE);
			break;
		case 3:
			searchResults=searchBy(SearchOption::BY_LAST);
			break;
		case 4:
			searchResults=searchBy(SearchOption::BY_ADDRESS);
			break;
				
        default:
			cerr << "Unknown command." << endl;
            log("case default");
			break;
		}
	}

	}
   //Database Database::searchByFirstName() const
	Database Database::searchBy(SearchOption option) const
		{
			string searchTag=getSearchString();
			Database result;
			bool done = false;
			bool foundMatch = false;
			for (const auto& e:mEmployees)
			{
				string targetString;
				switch (option) 
					{
					case SearchOption::BY_FIRST:
						targetString=e.getFirstName();	
						break;
					case SearchOption::BY_MIDDLE:
						targetString=e.getMiddleName();
						break;
					case SearchOption::BY_LAST:
						targetString=e.getLastName();
						break;	
					case SearchOption::BY_ADDRESS:
						targetString=e.getAddress();
						break;	
					}

				size_t pos = targetString.find(searchTag, 0);
				
				if (pos != string::npos) 
					{
						cout << targetString << endl;
						e.display();
						foundMatch = true;
						// result.addEmployee(e);
					}
			}
			if (!foundMatch) 
				{
					cout << "No match" << endl;
				}
		return result;
		

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