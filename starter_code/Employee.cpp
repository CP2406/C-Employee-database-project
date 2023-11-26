#include <iostream>
#include "Employee.h"

using namespace std;

namespace Records {

	Employee::Employee(const int& id, const std::string& password):m_id(id),mpassWord(password)
		{
		
		}
	Employee::Employee(const std::string& firstName, const std::string& middleName,
		const std::string& lastName,const int& id, const std::string& password):mFirstName(firstName), mMiddleName(middleName),
		mLastName(lastName),m_id(id),mpassWord(password)
		{

		}

	Employee::Employee(const std::string& firstName, const std::string& lastName)
		: mFirstName(firstName)
		, mLastName(lastName)
		{
		}
	Employee::Employee(const std::string& firstName, const std::string& middleName,const std::string& lastName)
		: mFirstName(firstName), mMiddleName(middleName),
		mLastName(lastName)
		{
		}

	


	void Employee::promote(int raiseAmount)
		{
			setSalary(getSalary() + raiseAmount);
		}

	void Employee::demote(int demeritAmount)
		{
			setSalary(getSalary() - demeritAmount);
		}

	void Employee::hire()
		{
			mHired = true;
		}

	void Employee::fire()
		{
			mHired = false;
		}

	void Employee::display() const
		{ 
			cout << "Employee: "<< getLastName() << ", "<< getFirstName() << endl;
			cout << "Middle Name: "<< getMiddleName() << endl;
			cout << "Address: "<< getAddress() << endl;
			cout << "-------------------------" << endl;
			cout << (isHired() ? "Current Employee hired " : "Former Employee Fired") << endl;
			cout << "Employee Number: " << getEmployeeNumber() << endl;
			cout << "Salary: $" << getSalary() << endl;	
			cout << "User Id: " <<getId()<< endl;
			cout << "Get Password: " <<getPassword()<< endl;
			cout << endl;
		}

	// Getters and setters
	void Employee::setFirstName(const string& firstName)
		{
			mFirstName = firstName;
		}

	const string& Employee::getFirstName() const
		{
			return mFirstName;
		}

	void Employee::setMiddleName(const string& middleName)
		{
			mMiddleName = middleName;
		}

	const string& Employee::getMiddleName() const
		{
			return mMiddleName;
		}


	void Employee::setLastName(const string& lastName)
		{
			mLastName = lastName;
		}

	const string& Employee::getLastName() const
		{
			return mLastName;
		}

	void Employee::setEmployeeNumber(int employeeNumber)
		{
			mEmployeeNumber = employeeNumber;
		}

		int Employee::getEmployeeNumber() const
		{
			return mEmployeeNumber;
		}

	void Employee::setAddress(const string& address)
		{
			mAddress= address;
		}

	const string& Employee::getAddress() const
		{
			return mAddress;
		}


	void Employee::setSalary(int salary)
		{
			mSalary = salary;
		}

	int Employee::getSalary() const
		{
			return mSalary;
		}

	bool Employee::isHired() const  
		{
			return mHired;
		}

	void Employee::setPassword(const string& passWord)
		{
			mpassWord=passWord;

		}
		const std::string& Employee::getPassword() const
		{

			return mpassWord;
		}

	void Employee::setId(const int& id)
		{
			m_id=id;

		}
	const int& Employee::getId() const
		{
			return m_id;

		}

}
