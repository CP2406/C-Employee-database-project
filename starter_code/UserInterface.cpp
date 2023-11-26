#include <iostream>
#include <stdexcept>
#include <exception>
#include "my_debugger.h"
#include "Database.h"
#include <cstddef>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace Records;
const string Logger::msDebugFileName="debugfile.txt";

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);
void doEdit(Database& db);
void loginMenu(Database& db);

Database makeNewDatabase();
Database newUserDatabase();

int main()
    {
        log("started");
        Database employeeDB;
        Database userDB;

        bool done = false;
        while (!done) {
            int selection = displayMenu();
            switch (selection) {
            case 0:
                log("case 0");
                done = true;
                break;
            case 1:
                doHire(employeeDB);
                log("case 1");
                break;
            case 2:
                doFire(employeeDB);
                break;
            case 3:
                doPromote(employeeDB);
                break;
            case 4:
                employeeDB.displayAll();
                break;
            case 5:
                employeeDB.displayCurrent();
                break;
            case 6:
                employeeDB.displayFormer();
                break;
            case 7:
                employeeDB=makeNewDatabase();
                break;
            case 8:
                employeeDB.saveToFile();
                break;
            case 9:
                employeeDB.loadFromFile();
                break;
            case 10:
                doEdit(employeeDB);
                break;
            case 11:
            employeeDB.searchMenu();
                break;
            case 12:
                 userDB=newUserDatabase();
                 loginMenu(userDB);
                break;
            default:
                cerr << "Unknown command." << endl;
                log("case default");
                break;
            }
        }

        return 0;
    
    }

int displayMenu()
    {
        // Note:
        //		One important note is that this code assumes that the user will
        //		"play nice" and type a number when a number is requested.
        //		When you read about I/O in Chapter 13, you will learn how to
        //		protect against bad input.

        int selection;

        cout << endl;
        cout << "Employee Database" << endl;
        cout << "-----------------" << endl;
        cout << "1) Hire a new employee" << endl;
        cout << "2) Fire an employee" << endl;
        cout << "3) Promote an employee" << endl;
        cout << "4) List all employees" << endl;
        cout << "5) List all current employees" << endl;
        cout << "6) List all former employees" << endl;
        cout << "7) Make new database" << endl;
        cout << "8) Save database to file" << endl;
        cout << "9) Load database from file" << endl;
        cout << "10) Edit employee" << endl;
        cout << "11) Search employee" << endl;
        cout << "12) login menu" << endl;
        cout << "0) Quit" << endl;
        cout << endl;
        cout << "---> ";
        
        cin >> selection;
        
        return selection;
    }

void doHire(Database& db)
    {   
        log("start");
        string firstName;
        string lastName;

        cout << "First name? ";
        cin >> firstName;
        cout << "Last name? ";
        cin >> lastName;
        
        db.addEmployee(firstName, lastName);
        log("end");
    }

void doFire(Database& db)
    {  
        int employeeNumber;

        cout << "Employee number? ";
        cin >> employeeNumber;
    

        try {
            Employee& emp = db.getEmployee(employeeNumber);
            emp.fire();
            cout << "Employee " << employeeNumber << " terminated." << endl;
        } catch (const std::logic_error& exception) {
            cerr << "Unable to terminate employee: " << exception.what() << endl;
        }
    }

void doPromote(Database& db)
    {
        int employeeNumber;
        int raiseAmount;

        cout << "Employee number? ";
        cin >> employeeNumber;
        cout << "How much of a raise? ";
        cin >> raiseAmount;

        try {
            Employee& emp = db.getEmployee(employeeNumber);
            emp.promote(raiseAmount);
            emp.display();
        } catch (const std::logic_error& exception) {
            cerr << "Unable to promote employee: " << exception.what() << endl;
        }
    }


void doEdit(Database& db)
    {
        int employeeNumber;
        cout << "Employee number? ";
        cin >> employeeNumber;


        try 
        {
            Employee& emp = db.getEmployee(employeeNumber);
            bool done = false;

            while(!done)
            {
                emp.display();
                int intOption;
                cout << "1) Edit by salary" << endl;
                cout << "2) Edit by address" << endl;
                cout << "3) Edit hired" << endl;
                cout << "0) Quit" << endl;
                cin>>intOption;
                int newSalary;
                string newAddress; 
                bool hireStatus;            
                switch(intOption)
                {
                    case 0:
                        cout<<"Quit editing"<<endl;
                        done=true;
                        break;
                    case 1:   
                        cout<<"Enter New Salary: "<<endl;
                        cin>>newSalary;         
                        emp.setSalary(newSalary);
                        break; 

                    case 2:
                        cout<<"Enter New Address: "<<endl; 
                        cin.ignore();
                        getline(cin,newAddress);                  
                        emp.setAddress(newAddress);
                        break;  
                    case 3: 
                        cout << "Edit to: Enter '1' to hire or '0' to fire: ";
                        cin >> hireStatus; 
                        if (hireStatus) {
                            emp.hire();
                            cout<<"Hire Status Updated to : Hired" << endl;
                        } else {
                            emp.fire();
                            cout << "Hire Status Updated to : Fired" << endl;
                        }  
                        break;
                        
                    emp.display();

                }

            }

        } 
        catch (const std::logic_error& exception) 
            {
                cerr << "Unable to promote employee: " << exception.what() << endl;
            }

    }


Database makeNewDatabase()
    {
        vector<string> arrFirst{

            "first1","Ann","Bob","first2","Cathy",
            "first3","Ann2","Bob2","first10","Cathy2",
            "first4","3Ann3","Bob3","first11","Cathy3",
            "first5","Ann4","Bob4","first12","Cathy4",
        
        };
        vector<string> arrMiddle{

            "middle1","Don","Bob","first2","Cathy",
            "middle3","Don2","Bob2","first10","Cathy2",
            "middle4","Don3","Bob3","first11","Cathy3",
            "middle5","Don4","Bob4","first12","Cathy4",
        
        };

        vector<string> arrLast{

            "last1","Smith","Lily","Steven","Jim",
            "last2","Smith2","Lily1","Steven1","Jim1",
            "last3","Smith3","Lily2","Steven2","Jim2",
            "last4","Smith4","Lily3","Steven3","Jim3",
        };

        Database db;
        int count=0;

        for (const string& firstName:arrFirst){
            for (const string& middleName:arrMiddle){
                for (const string& lastName:arrLast){
                count++;
                //random streetNumber
                string countStr =to_string(count);
                Employee& empl=db.addEmployee(firstName, middleName,lastName);
                //random address
                string address =countStr + " street# " + "Cairns";
                empl.setAddress(address);
                
   
                }
            }
        }
        return db;
    }


		void loginMenu(Database& db)
		{
			int managerPassword{1}; // manager default password
			int employeePassword{0}; // employee default password
            db.displayAll();

            int userInput;
			int loginOption;
			cout<<"Enter following option number"<<endl;
			cout<<" 0) login by Employee"<<endl;
			cout<<" 1) login by Manager"<<endl;
			cin>>loginOption;
			

					switch(loginOption){			
						// case 0:
						// 	cout<<"Employee login  "<<endl;				
						// 	cout << "Employee password? ";
						// 	cin >> userInput;
						// 	if (userInput==employeeId){
								

						// 	}


						// 	break;
						case 1:
							cout<<"Manager login "<<endl;
							cout << "Manager Password? ";
							cin >> userInput;
							if (userInput==managerPassword){
								// which user you want to edit?
								// user Id ?
								// user Id match(get user iD from mUser)
								//EDIT password or id?
								// User.set ID 
								// User.set password

							}

							break;
						default:
							cerr << "Unknown command." << endl;
							break;			

					}


    //     void doFire(Database& db)
    // {  
    //     int employeeNumber;

    //     cout << "Employee number? ";
    //     cin >> employeeNumber;
    

    //     try {
    //         Employee& emp = db.getEmployee(employeeNumber);
    //         emp.fire();
    //         cout << "Employee " << employeeNumber << " terminated." << endl;
    //     } catch (const std::logic_error& exception) {
    //         cerr << "Unable to terminate employee: " << exception.what() << endl;
    //     }
    // }


		}



	Database newUserDatabase()

     {
        vector<string> arrFirst{

            "first1","Ann","Bob","first2","Cathy",
        };
        vector<string> arrMiddle{

            "middle1","Don","Bob","first2","Cathy",            
        };

        vector<string> arrLast{

            "last1","Smith","Lily","Steven","Jim",
        };
        Database dbUser;
        int count=0;

        for (const string& firstName:arrFirst){
            for (const string& middleName:arrMiddle){
                for (const string& lastName:arrLast){
                count++;
                //random streetNumber
                string countStr =to_string(count); //countStr = password string
    
                Employee& empl=dbUser.addEmployee(firstName, middleName,lastName,count,countStr);// count=id 
                string address =countStr + " street# " + "Cairns";
                empl.setAddress(address);
                
   
                }
            }
        }
        return dbUser;

}