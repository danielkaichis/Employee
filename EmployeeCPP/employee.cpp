/*
* File:   employee.cpp
* Author: Daniel Kaichis
* Purpose: An object oriented program designed to proccess information of employees 
           in a company from a file and print three reports summarizing their personal 
           information and pay related information. The program will also print a summary
           of the companies weekly payout and the number of employees they have.
* Status: DONE
*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// max num of each employee type
const int MAX_MANAGERS = 4;
const int MAX_ACCOUNTANTS = 3;
const int MAX_SECRETARIES = 7;
const int MAX_HR = 2;
const int MAX_SALESPEOPLE = 30;
// maximum number of employees
const int MAX_EMPLOYEES = MAX_MANAGERS + MAX_ACCOUNTANTS + MAX_SECRETARIES + MAX_HR + MAX_SALESPEOPLE;
// hours an employee works in a standard work week
const double STANDARD_WEEKLY_HOURS = 40;
const double HOURS_IN_A_WEEK = 24 * 7;

// constants for the commission rates of different types of salespeople
const double JUNIOR_COMMISSION_RATE = 0.02;
const double SENIOR_COMMISSION_RATE = 0.03;



// strings for each position at the company
const string managerPos = "manager";
const string accountantPos = "accountant";
const string secretaryPos = "secretary";
const string HRPos = "human resource";
const string juniorSalesPos = "junior salesperson";
const string seniorSalesPos = "senior salesperson";

/* 
* Class: Name
* Purpose: A class that contains attributes of a name
          and methods to utilize the name in other contexts
*/
class Name {
private:
    // strings for first and last name
    string firstName;
    string lastName;

public:
    /* 
    * Purpose: To construct/initialize a Name object given values for its member variables
    * Parameters: firstName - the first name of a person
    *             lastName - the last name of a person
    * Returns: Not Applicable
    * Side Effects: the first and last name member variables 
    *               are set to the passed in values.
    */
    Name(string firstName, string lastName) {
        this->firstName = firstName;
        this->lastName = lastName;
    }

    // get methods
    virtual string getFirstName() const {return firstName;}
    virtual string getLastName() const {return lastName;}

    /* 
    * Purpose: To print a Name
    * Parameters: lastNameFirst - an bool for whether the last name will be printed before the first name or not
    *             seperator - a character that will seperate the last and first names when printed (if last name is first) 
    * Returns: NONE
    * Side Effects: NONE - method is constant
    */
    virtual void print(bool lastNameFirst, char seperator) const {
        // if last name is first, print name with last name first followed by seperator and first name
        if (lastNameFirst) {
            cout << lastName << seperator << " " << firstName;
        // first name is printed first, followed by the last name
        } else {
            cout << firstName << " " << lastName;
        }
    }
}; // Class Name

/* 
* Class: Date
* Purpose: A class that contains the elements of a Date
           and methods to perform certain actions on/with
           these elements
*/
class Date {
private:
    // variables for the month, day, and year of a date
    string month;
    int day;
    int year;

public:
    /* 
    * Purpose: To construct/initialize a Date object given values for its member variables
    * Parameters: month - the month of the Date
    *             day - the day of the Date
    *             year - the year of the Date
    * Returns: Not Applicable
    * Side Effects: setDate() is called to set the date and modify the member variables of the Date
    */
    Date(string month, int day, int year) {
        // set date with the values passed into the constructor
        setDate(month, day, year);
    }

    // get methods
    virtual string getMonth() const {return month;}
    virtual int getDay() const {return day;}
    virtual int getYear() const {return year;}

    /* 
    * Purpose: To set the values of the member variables of a Date
    * Parameters: month - the month of the Date
    *             day - the day of the Date
    *             year - the year of the Date
    * Returns: NONE
    * Side Effects: The member variables of the Date are updated
    *               with the passed in values
    */
    virtual void setDate(string month, int day, int year) {
        // set month day and year with the values passed into the method
        this->month = month;
        this->day = day;
        this->year = year;
    }

    /* 
    * Purpose: To print a Date
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE - function is constant
    */
    virtual void print() const {
        // print date in the format of month day, year.
        cout << month << " " << day << ", " << year;
    }
}; // Class Date

/* 
* Class: PersonalInfo
* Purpose: A class that contains a persons personal work information
           and methods to perform certain actions on/with this information
*/
class PersonalInfo {
private:
    // name, birthday and SIN make up a persons personal work information
    Name name;
    Date birthday;
    string SIN;
public:
    /* 
    * Purpose: To construct/initialize a PersonalInfo object given values for its member variables
    * Parameters: firstName - a persons first name
    *             lastName - a persons last name
    *             birthMonth - a persons birth month
    *             birthDay - a persons birth day
    *             birthYear - a persons birth year
    *             SIN - a persons Social Insurance Number
    * Returns: Not Applicable
    * Side Effects: Name and Birthday objects (name and birthday) constructors are called to initialize them
    *               in the initializers list and the member variable SIN is set to the passed in value.
    */
    PersonalInfo(string firstName, string lastName, string birthMonth, int birthDay, int birthYear, string SIN) :
                name(firstName, lastName), birthday(birthMonth, birthDay, birthYear) {
        // set the SIN of this object to the SIN passed in to the constructor
        this->SIN = SIN;
    }

    // get methods
    // getName and getDate return pointers to a name and date so
    // methods from each class can be called
    virtual const Name *getName() const {return &name;}
    virtual const Date *getDate() const {return &birthday;}
    virtual string getSIN() const {return SIN;}
};

/* 
* Class: PayInfo
* Purpose: A class that contains a persons work pay information
           and methods to perform certain actions on/with this information
*/
class PayInfo {
private:
// variables for a person/workers pay rate and the number of hours they worked in a week
    double payRate;
    double hoursWorked;
public:
    // the minimum legal wage for work as specified by Canadian/Tam labour laws
    static const double minimumWage;

public:
    /* 
    * Purpose: To construct/initialize a PayInfo object given values for its member variables
    * Parameters: payRate - a persons hourly pay rate
    *             hoursWorked - the hours a person worked in a week
    * Returns: Not Applicable
    * Side Effects: setPayRate and setHoursWorked are called which modify member variables
    *               if the passed in values are valid
    */
    PayInfo(double payRate, double hoursWorked) {
        // set pay rate and hours worked
        setPayRate(payRate);
        setHoursWorked(hoursWorked);
    }

    // get methods
    virtual double getPayRate() const {return payRate;}
    virtual double getHoursWorked() const {return hoursWorked;}

    /* 
    * Purpose: To set a persons hourly pay rate
    * Parameters: payRate - the persons hourly pay rate
    * Returns: false if payRate is less than the legal minimum wage, true if it is greater than or equal to the minimum wage
    * Side Effects: the payRate member variable is modified if the passed in payRate is greater than or equal to the minimum wage
    */
    virtual bool setPayRate(double payRate) {
        // if pay rate is less than minimum wage return false so other classes 
        // that call this function can perform actions depending on the context
        if (payRate < minimumWage) {
            return false;
        }
        // set pay rate and return true
        this->payRate = payRate;
        return true;
    }

    /* 
    * Purpose: To set the number of hours a person worked in a week
    * Parameters: hoursWorked - the number of hours a person worked in a week
    * Returns: false if the number of hours worked is not between 0 and the maximum number of hours
    *          a week, true if the number of hours is between this range
    * Side Effects: 
    */
    virtual bool setHoursWorked(double hoursWorked) {
        // if hours worked is less than 0 or greater than the number of hours in a week
        // return false so other classes that call this function can perform actions depending on the context
        if ((hoursWorked < 0) || (hoursWorked > (HOURS_IN_A_WEEK) )) {
            return false;
        } 
        // set hours worked and return true
        this->hoursWorked = hoursWorked;
        return true;
    }

}; // Class PayInfo
// set minimum wage of PayInfo to $14/hour
const double PayInfo::minimumWage = 14;

/* 
* Class: Employee
* Purpose: A class to store the information of an employee in a company
           and methods to perform actions on/with this information
*/
class Employee {
private:
    // privatemember variables for an employees position, personalInfo (see class PersonalInfo),
    // and payInfo (see class PayInfo). These only need to be accessed by the employee class and 
    // should not be changed without any validation by any child classes that do not understand the context
    string position;
    PersonalInfo personalInfo;
    PayInfo payInfo;
    // variable for an employees weekly pay
    double weeklyPay;

public:
    // class variable for the maximum hourly wage the company will pay an employee 
    static const double maximumCompanyWage;

public:
    /* 
    * Purpose: To construct/initialize an Employee object with values for the member variables passed in to the constructor
    * Parameters: position - an employees position/job in the company
    *             firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    * Returns: Not Applicable
    * Side Effects: position member variable is set, setPayRate and setHoursWorked are called which 
    *               modify member variables to set the payRate and hoursWorked member variables. In the
    *               initializers list personalInfo and payInfos constructors are called which modify member 
    *               variables of those classes
    */
    Employee(string position, string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked):
            personalInfo(firstName, lastName, birthMonth, birthDay, birthYear, SIN), payInfo(payRate, hoursWorked) {
        // set position to the position passed into the constructor
        this->position = position;
        // set the employees pay rate 
        setPayRate(payRate);
        // set the hours the employee worked
        setHoursWorked(hoursWorked);
    };

    // get methods
    virtual string getPosition() const {return position;}
    virtual PayInfo *getPayInfo() {return &payInfo;}
    virtual const PersonalInfo *getPersonalInfo() const {return &personalInfo;}
    virtual double getWeeklyPay() const {return weeklyPay;}

public:
    /* 
    * Purpose: To set the employees hourly pay rate
    * Parameters: payRate - the employees hourly pay rate
    * Returns: NONE
    * Side Effects: payRate member variable is set the the inputted value or 
    *               minimum wage if it is invalid.
    */
    virtual void setPayRate(double payRate) {
        // if pay rate is greater than the maximum company wage or is deemed invalid/illegal by
        // payInfos setPayRate method, print an error and set pay rate to minimum wage
        // if payInfos setPayRate returns true then the pay rate has been set so
        // it does not need to be set again outside this if statement
        if ((payRate > maximumCompanyWage) || (!payInfo.setPayRate(payRate))) {
            cout << "ERROR: " << position << " ";
            personalInfo.getName()->print(false, 'x');
            cout << " is earning $" << payRate << " per hour. Pay rate will be set to $" << PayInfo::minimumWage << " per hour." << endl;
            payInfo.setPayRate(PayInfo::minimumWage);
        }
        // calculate the employees weekly pay from scratch as the pay rate has changed
        calcWeeklyPay();
    }

    /* 
    * Purpose: To set the number of hours an employee worked in a week
    * Parameters: hoursWorked - the number of hours an employee worked in a week
    * Returns: NONE
    * Side Effects: hoursWorked member variable is modified and set the passed in value 
    *               or 0 if the value is determined to be invalid 
    */
    virtual void setHoursWorked(double hoursWorked) {
        // if payInfos setHoursWorked method returns false, the hours
        // worked passed into the function are not valid/possible to have been worked.
        // Print error message and set hours worked to 0 so the employee will 
        // know to approach management (C*O Tam) about the issue.
        if(!payInfo.setHoursWorked(hoursWorked)) {
            cout << "ERROR: " << position << " ";
            personalInfo.getName()->print(false, 'x');
            cout << " has worked " << hoursWorked << " hours. Hours will be set to 0." << endl;
            payInfo.setHoursWorked(0);
        }
        // calculate the employees weekly pay from scratch as the employees hours worked in the week has changed
        calcWeeklyPay();
    }

protected:
    /* 
    * Purpose: To set the employees weeklyPay
    * Parameters: weeklyPay - the employees weeklyPay
    * Returns: NONE
    * Side Effects: weeklyPay member variable is set to the inputted value if it is valid
    *               or 0 if it is not so employee knows to approach management
    */
   virtual void setWeeklyPay(double weeklyPay) {
       if (weeklyPay >= 0) {
           this->weeklyPay = weeklyPay;
       } else {
           this->weeklyPay = 0;
       }
   }

    /* 
    * Purpose: To act as a function to be overriden due to the limitations
               of using virtual functions in a constructor. This cannot be pure
               virtual as when the employee constructor is created at the top 
               of the heirarchy, this calcWeeklyPay is the only method of this name
               that the created object is aware of
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE
    */
    virtual void calcWeeklyPay() {};

public:
    /* 
    * Purpose: To reset the parts of an employees payment information that can vary week by week
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: setHoursWorked is called which modifies member variables of Employee objects
    */
    virtual void reset() {
        // setHoursWorked to 0 to reset an employees hours worked. This will also reset an employees
        // weeklyPay as this function calls weeklyPay once the hoursWorked has been changed to ensure
        // the weeklyPay always reflects the pay an employee has earned for the hours they worked.
        // Pay rate is not reset as this is something that does not change often.
        setHoursWorked(0);
    }

public:
    /* 
    * Purpose: To print the pay information report of an employee
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE - function is constant
    */
    virtual void printPayInformationReport() const {
        // print employee position, name, pay rate, hours worked, and weekly pay
        cout << "Position: " << position << endl;
        cout<< "Name: ";
        personalInfo.getName()->print(true, ',');
        cout << endl;
        cout << "Pay Rate: $" << payInfo.getPayRate() << "/hour" << endl;
        cout << "Hours Worked: " << payInfo.getHoursWorked() << endl;
        cout << "Weekly Pay: $" << weeklyPay << endl;
    }

    /* 
    * Purpose: To print the employee information report of an employee
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE - function is constant
    */
    virtual void printEmployeeInformationReport() const {
        // print employee name, position, birthday, SIN, and hourly pay rate
        cout << "Name: ";
        personalInfo.getName()->print(1, ',');
        cout << endl;
        cout << "Position: " << position << endl;
        cout << "Birthday: ";
        personalInfo.getDate()->print();
        cout << endl;
        cout << "SIN: " << personalInfo.getSIN() << endl;
        cout << "Hourly Pay Rate: $" << payInfo.getPayRate() << "/hour" << endl;
    }

    /* 
    * Purpose: To print a cheque for an employee
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE  function is constant 
    */
    virtual void printCheque() const {
        // if weekly pay is greater than $0, print an employee a cheque using the standard cheque format as specified by C*O Tam
        if (weeklyPay > 0) {
            cout << "Payable to ";
            // print first name first with filler seperator because seperator is only used for when last name is printed first
            personalInfo.getName()->print(0, 'x');
            cout << " in the amount of $" << weeklyPay << "." << endl;
        }
    }
}; // Class Employee
// set maximum company wage to $100 as specified by the C*O
const double Employee::maximumCompanyWage = 100;

/* 
* Class: SalaryBasedEmploye
* Purpose: A class to store the information of a salary based employee
           and methods to perform actions specific to this type of employee
           NOTE: SalaryBasedEmployee inherits from the Employee class
*/
class SalaryBasedEmployee : public Employee {
private:
    // a class variable for the standard number of hours per week
    // a salary based employee has included in their weekly pay
    static const double hoursForSalary;
public:
    /* 
    * Purpose: To construct/initialize a SalaryBasedEmployee object with values for the member variables passed into the constructor
               This constructor also constructs its parent class Employee with the values passed into the SalaryBasedEmployee constructor
    * Parameters: position - an employees position/job in the company
    *             firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    * Returns: Not Applicable
    * Side Effects: calcWeeklyPay is called when an object is constructed which sets the member variable
    *               Employee::weeklyPay to the value calculated by other methods of SalaryBasedEmployee.
    *               Employee object is constructed
    */
    SalaryBasedEmployee(string position, string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked) :
                        Employee(position, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked) {
        // call calcWeeklyPay when an object is constructed because the calcWeeklyPay called by methods in employees constructor
        // will not use inheritence as calcWeeklyPay in SalaryBasedEmployee will not exist when the Employee object is constructed
        calcWeeklyPay();
    }

protected:
    /* 
    * Purpose: To calculate the weekly pay of a salary based employee
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: Employee::weeklyPay is set
    */
    virtual void calcWeeklyPay() {
        // the weekly pay of a salary based employee is their pay rate
        // multiplied by the number of hours in a week they are paid for working
        setWeeklyPay(hoursForSalary * getPayInfo()->getPayRate());
    }
}; // Class SalaryBasedEmployee
// set the hours a salary based employee is paid for as part of their salary
const double SalaryBasedEmployee::hoursForSalary = STANDARD_WEEKLY_HOURS;

/* 
* Class: Manager
* Purpose: A class to store the information and methods
         of a Manager. Actions/calculations specific
         to only a manager are performed here
*/
class Manager : public SalaryBasedEmployee {
public:
    /* 
    * Purpose:  To construct/initialize a Manager object with the values passed into the constructor, and to construct
                the managers parent class SalaryBasedEmployee using the values passed into the constructor and managerPos
                which is the variable storing the string of the managers official title.
    * Parameters: firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    * Returns: Not Applicable
    * Side Effects: SalaryBasedEmployee object is constructed
    */
    Manager(string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked) :
            SalaryBasedEmployee(managerPos, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked) {}
}; // Class Manager

/* 
* Class: Accountant
* Purpose: A class to store the information and methods
         of an Accountant. Actions/calculations specific
         to only an accountant are performed here
*/
class Accountant : public SalaryBasedEmployee {
public:
    /* 
    * Purpose: To construct/initialize an Accountant object with the values passed into the constructor, and to construct
               the accountants parent class SalaryBasedEmployee using the values passed into the constructor and accountantPos
               which is the variable storing the string of the accountants official title.
    * Parameters: firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    * Returns: Not Applicable
    * Side Effects: SalaryBasedEmployee object is constructed
    */
    Accountant(string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked) :
            SalaryBasedEmployee(accountantPos, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked) {}
}; // Class Accountant

/* 
* Class: HourlyBasedEmployee
* Purpose: A class to store the information of an hourly based employee
           and methods to perform actions specific to this type of employee
           NOTE: HourlyBasedEmployee inherits from the Employee class
*/
class HourlyBasedEmployee : public Employee {
private:
    // member variables for an hourly based employees normal pay (pay without overtime),
    // hours for overtime (hours worked before overtime applies), overtime (pay earned from overtime),
    // and overtimeMultiplier (pay increase for working overtime).
    double normalPay;
    double hoursForOvertime;
    double overtime;
    double overtimeMultiplier;

public:
    /* 
    * Purpose: To construct/initialize an HourlyBasedEmployee object with values for the member variables passed into the constructor
               This constructor also constructs its parent class Employee with the values passed into the HourlyasedEmployee constructor
    * Parameters: position - an employees position/job in the company
    *             firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    *             hoursForOvertime - the number of hours an hourly based employee must work to start earning overtime
    *             overtimeMultiplier - the pay multiplier for an hourly based employee when they are earning overtime
    * Returns: Not Applicable
    * Side Effects: setHoursWorked is called when an object is constructed which sets some member variables
    *               of Employee. Employee object is also constructed and hoursForOvertime and overtimeMultiplier variables
    *               are set in the initializers list using the values passed into the constructor
    */
    HourlyBasedEmployee(string position, string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked, double hoursForOvertime, double overtimeMultiplier) :
                        Employee(position, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked), hoursForOvertime(hoursForOvertime), overtimeMultiplier(overtimeMultiplier) {
        // call setHoursWorked upon construction of an HourlyBasedEmployee object to work around constructor virtualness limitation
        setHoursWorked(hoursWorked);
    }

protected:
    /* 
    * Purpose: To calculate the weekly pay of an hourly based employee
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: Employee::weeklyPay is set by setWeeklyPay when it is called.
    *               calcNormalPay and calcOvertime set member variables of this class
    *               when they finish their calculations
    */
    virtual void calcWeeklyPay() {
        // calculate normal pay and overtime of an hourly based employee
        calcNormalPay();
        calcOvertime();
        // an hourly based employees weekly pay is equal to the sum of their normal pay and overtime
        setWeeklyPay(normalPay + overtime);
    }

public:
    /* 
    * Purpose: To set the number of hours worked in a week by an hourly based employee
    * Parameters: hoursWorked - the number of hours the hourly based employee worked in a week
    * Returns: NONE
    * Side Effects: Employee::hoursWorked is set by the method, and methods it calls for further validation
    */
    virtual void setHoursWorked(double hoursWorked) {
        // if hourly based employee worked over 60 hours
        // print an error message and set hours to 0
        if (hoursWorked > 60) {
            cout << "ERROR: " << getPosition() << " ";
            getPersonalInfo()->getName()->print(false, 'x');
            cout << " has worked " << hoursWorked << " hours which is greater than the legal limit. Hours will be set to 0." << endl;
            hoursWorked = 0;
        }
        // set hours worked to value passed in to method
        Employee::setHoursWorked(hoursWorked);
    }

private:
    /* 
    * Purpose: To calculate the amount of overtime pay an employee earned 
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: the overtime member variable is modified 
    */
    virtual void calcOvertime() {
        // variable for number of hours worked overtime
        double overtimeHours = 0;
        // variable for the difference between an employees hours worked and the hours they need to have worked to get overtime pay
        double tmpOvertime = getPayInfo()->getHoursWorked() - hoursForOvertime;
        // if they have worked greater than the amount of overtime hours needed, 
        // set overtimeHours to the number of hours they worked overtime
        if (tmpOvertime > 0) {
            overtimeHours = tmpOvertime;
        }
        // overtime is equal to the product of the number of hours worked overtime and
        // the employees pay rate times their overtime multiplier
        overtime = overtimeHours * (getPayInfo()->getPayRate() * overtimeMultiplier);
    }

    /* 
    * Purpose: To calculate the amount of normal pay (pay without overtime) an employee is owed 
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: the normalPay member variable is modified 
    */
    virtual void calcNormalPay() {
        // variable for the number of hours an employee worked while not being paid overtime
        // set to the total number of hours they have worked to start
        double hoursWithoutOvertime = getPayInfo()->getHoursWorked();;
        // if the employee has worked greater than or equal to the number of hours than needed to get overtime,
        // the number of hours they worked without overtime is equal to the minimum
        // number of hours needed to receive overtime. Ie if they get paid overtime after
        // 44 hours worked and have worked 46 hours, they are paid for 44 hours without overtime
        if (hoursWithoutOvertime >= hoursForOvertime) {
            hoursWithoutOvertime = hoursForOvertime;
        }
        // normal pay equals the number of hours worked without overtime times their
        // pay rate
        normalPay = hoursWithoutOvertime * getPayInfo()->getPayRate();
    }

public:
    /* 
    * Purpose: To print the pay information report of an hourly based employee
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE - function is constant
    */
    virtual void printPayInformationReport() const {
        // get Employee to print the information from the pay report that is common among all employee types
        Employee::printPayInformationReport();
        // if normal pay is greater than 0, print the pay breakdown. One can only earn overtime
        // if working over a certain number of hours but because normal pay is the amount of 
        // pay earned before overtime, it is impossible to have overtime pay if normal pay is 0.
        if (normalPay > 0) {
            // print the normal and overtime pay breakdown, using a tab (\t) for spacing to show
            // that they make up the weekly pay
            cout << "\tNormal Pay: $" << normalPay << endl;
            cout << "\tOvertime: $" << overtime << endl;
        }
    }

}; // Class HourlyBasedEmployee

/* 
* Class: Secretary
* Purpose: A class to store the information and methods
         of a secretary. Actions/calculations specific
         to only a secretary are performed here
*/
class Secretary : public HourlyBasedEmployee {
public:
    /* 
    * Purpose: To construct/initialize a Secretary object with the values passed into the constructor, and to construct
               the secretaries parent class HourlyBasedEmployee using the values passed into the constructor and secretaryPos
               which is the variable storing the string of the secretaries official title.
    * Parameters: firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    * Returns: Not Applicable
    * Side Effects: HourlyBasedEmployee object is constructed with unique values for secretary being 40 for hours to earn overtime
    *               and 1.5 for overtime multiplier
    */
    Secretary(string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked) :
            HourlyBasedEmployee(secretaryPos, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked, 40, 1.5) {}
}; // Class Secretary

/* 
* Class: HumanResourcePerson
* Purpose: A class to store the information and methods
         of a human resource person. Actions/calculations specific
         to only a human resource person are performed here
*/
class HumanResourcePerson : public HourlyBasedEmployee {
public:
    /* 
    * Purpose: To construct/initialize a HumanResourcePerson object with the values passed into the constructor, and to construct
               the human resource persons parent class HourlyBasedEmployee using the values passed into the constructor and HRPos
               which is the variable storing the string of the human resource persons official title.
    * Parameters: firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    * Returns: Not Applicable
    * Side Effects: HourlyBasedEmployee object is constructed with unique values for secretary being 44 for hours to earn overtime
    *               and 2 for overtime multiplier
    */
    HumanResourcePerson(string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked) :
            HourlyBasedEmployee(HRPos, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked, 44, 2) {}
}; // Class HumanResourcePerson

/* 
* Class: Salesperson
* Purpose: A class to store the information of an salesperson
           and methods to perform actions specific to this type of employee
           NOTE: Salesperson inherits from the Employee class
*/
class Salesperson : public Employee {
private:
    // member variables for a Salesperson sales, normal pay, commission, and commission rate
    double sales;
    double normalPay;
    double commission;
    double commissionRate;

public:
    /* 
    * Purpose: To construct/initialize a Salesperson object with values for the member variables passed into the constructor
               This constructor also constructs its parent class Employee with the values passed into the Salesperson constructor
    * Parameters: position - an employees position/job in the company
    *             firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    *             sales - the total amount ($) of sales a salesperson had in the week
    *             commissionRate - the percentage of sales the salesperson makes in commission
    * Returns: Not Applicable
    * Side Effects: setSales is called when an object is constructed which sets the member variable
    *               sales. calcWeeklyPay is called because due to limitations of virtualness in constructors,
    *               Salesperson::calcWeeklyPay does not exist until the Salesperson object is created after if
    *               constructs its parent.
    */
    Salesperson(string position, string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked, double sales, double commissionRate):
                Employee(position, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked), commissionRate(commissionRate) {
        // set sales and calculate salespersons weekly pay when creating a Saleperson object
        setSales(sales);
        calcWeeklyPay();
    }

protected:
    /* 
    * Purpose: To calculate the weekly pay of a Salesperson
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: Employee::weeklyPay is set by setWeeklyPay when it is called.
    *               calcNormalPay and calcCommission set member variables of this class
    *               when they finish their calculations
    */
    virtual void calcWeeklyPay() {
        // calculate normal pay and commission of the salesperson
        calcNormalPay();
        calcCommission();
        // set the salespersons weekly pay to their normal pay plus the amount they earned in commission
        setWeeklyPay(normalPay + commission);
    }

private:
    /* 
    * Purpose: To calculate the amount of commission a salesperson made 
               off of their sales
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: commission member variable is set
    */
    virtual void calcCommission() {
        // commission equals sales times the commission rate of the salesperson
        commission = sales * commissionRate;
    }

    /* 
    * Purpose: To calculate the normal pay (pay without commission) of a Salesperson 
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: normalPay member variable is set
    */
    virtual void calcNormalPay() {
        // set paidHoursWorked to the amount of hours the salesperson worked
        double paidHoursWorked = getPayInfo()->getHoursWorked();
        // if salesperson worked greater than or equal to the standard weekly hours they are paid for
        // set the number of hours they are paid for to this maximum value 
        if (getPayInfo()->getHoursWorked() >= STANDARD_WEEKLY_HOURS) {
            paidHoursWorked = STANDARD_WEEKLY_HOURS;
        }
        // normal pay is equal to the number of paid hours worked times the 
        // salespersons pay rate
        normalPay = paidHoursWorked * getPayInfo()->getPayRate();
    }

public: 
    /* 
    * Purpose: To set the sales of a salesperson
    * Parameters: sales - the amount of sales ($) a salesperson had in a week
    * Returns: NONE
    * Side Effects: sales member variable is modified
    */
    virtual void setSales(double sales) {
        // if sales is less than $0, print an error message and set to 0
        if (sales < 0) {
            cout << "ERROR: " << getPosition() << " ";
            // print name with first name first and use a random character because the seperator perameter
            // of print is only used when last name is first
            getPersonalInfo()->getName()->print(false, 'x');
            cout << " has $" << sales << " in sales. Sales will be set to $0." << endl;
            this->sales = 0;
        // set sales using the value passed into the method
        } else {
            this->sales = sales;
        }
        // calculate commission on the new sales amount
        calcCommission();
    }

    /* 
    * Purpose: To print the pay information report of a salesperson
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: NONE - function is constant
    */
    virtual void printPayInformationReport() const {
        // let Employee print the information in the pay information report 
        // that is common among all employee types
        Employee::printPayInformationReport();
        // print normal pay and commission breakdown using tabs
        // to make it clear that they are the components of weekly pay
        // which is printed last by the previous method call
        // since normal pay could be 0 but commission could be positive
        // due to sales contracts being signed at the start of a week
        // (ie if a salesperson sends a contract one week but it is signed 
        // and the sale is completed the next week when hours worked is at 0 for the week,
        // the salesperson still would make commission and so the breakdown is printed)
        cout << "\tNormal Pay: $" << normalPay << endl;
        cout << "\tCommision: $" << commission << endl;
    }

    /* 
    * Purpose: To reset the parts of a salespersons pay information that can change week by week
    * Parameters: NONE
    * Returns: NONE
    * Side Effects: sales member variable is set. Employee::reset also modified member variables
    *               of the Employee parent object
    */
    virtual void reset() {
        // set sales to 0 for the new week
        setSales(0);
        // call Employee::reset() to reset the salespersons hours worked and consequently their weekly pay
        Employee::reset();
    }

}; // Class Salesperson

/* 
* Class: JrSalesperson
* Purpose: A class to store the information and methods
         of a junior salesperson. Actions/calculations specific
         to only a junior salesperson person are performed here
*/
class JrSalesperson : public Salesperson {
public:
    /* 
    * Purpose: To construct/initialize a JrSalesperson object with the values passed into the constructor, and to construct
               the junior salespersons parent class Salesperson using the values passed into the constructor and juniorSalesPos
               which is the variable storing the string of the junior salespersons official title.
    * Parameters: firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    *             sales - the amount of sales ($) a junior salesperson made in a week
    * Returns: Not Applicable
    * Side Effects: Salesperson object is constructed with the unique commission rate of a junior saleperson
    */
    JrSalesperson(string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked, double sales):
                  Salesperson(juniorSalesPos, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked, sales, JUNIOR_COMMISSION_RATE) {}
}; // Class JRSalesperson

/* 
* Class: SrSalesperson
* Purpose: A class to store the information and methods
         of a senior salesperson. Actions/calculations specific
         to only a senior salesperson person are performed here
*/
class SrSalesperson : public Salesperson {
public:
    /* 
    * Purpose: To construct/initialize a SrSalesperson object with the values passed into the constructor, and to construct
               the senior salespersons parent class Salesperson using the values passed into the constructor and seniorSalesPos
               which is the variable storing the string of the senior salespersons official title.
    * Parameters: firstName - an employees first name
    *             lastName - an employees last name
    *             SIN - an employee social insurance number
    *             birthMonth - the month an employee was born in
    *             birthDay - the day of the month an employee was born on
    *             birthYear - the year an employee was born in
    *             payRate - the employees hourly pay rate
    *             hoursWorked - the number of hours the employee worked in a week
    *             sales - the amount of sales ($) a senior salesperson made in a week
    * Returns: Not Applicable
    * Side Effects: Salesperson object is constructed with the unique commission rate of a senior saleperson
    */
    SrSalesperson(string firstName, string lastName, string SIN, string birthMonth, int birthDay, int birthYear, double payRate, double hoursWorked, double sales):
                  Salesperson(seniorSalesPos, firstName, lastName, SIN, birthMonth, birthDay, birthYear, payRate, hoursWorked, sales, SENIOR_COMMISSION_RATE) {}
}; // Class SRSalesperson

int main() {
    // variables to store the information read in from the file
    string junk;
    string filename;
    string position;
    string firstName;
    string lastName;
    string SIN;
    string birthMonth;
    int birthDay;
    int birthYear;
    double payRate;
    double hoursWorked;
    int salesMade;
    // create pointer to employee array
    Employee *employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int employeeNumber = 0;
    double totalWeeklyPay;
    ifstream inputFile; // C++ object that represents a file

    // set output of doubles to 2 decimal places
    cout << std::setprecision(2) << std::fixed;

    // welcome message
    cout << "Welcome to Daniel's employee HR management system!" << endl;

    // get the name of the data file
    cout << "Please enter the name of the data file: ";
    getline( cin, filename );

    // open the file for reading
    inputFile.open( filename );
    getline( inputFile, position );

    // process the data file to read in an employee's information, and create
    // the appropriate employees to store within our array.
    while (( position != "END" ) && (numEmployees < MAX_EMPLOYEES)) {
        getline( inputFile, lastName );
        getline( inputFile, firstName );
        getline( inputFile, SIN );
        getline( inputFile, birthMonth );
        inputFile >> birthDay;
        getline( inputFile, junk );
        inputFile >> birthYear;
        getline( inputFile, junk );
        inputFile >> payRate;
        getline( inputFile, junk );
        inputFile >> hoursWorked;
        getline( inputFile, junk );
        if ( position == managerPos ) {
            employees[numEmployees] = new Manager(firstName, lastName, SIN, birthMonth,
                birthDay, birthYear, payRate, hoursWorked);
        } else if ( position == accountantPos ) {
            employees[numEmployees] = new Accountant(firstName, lastName, SIN, birthMonth,
                birthDay, birthYear, payRate, hoursWorked);
        } else if ( position == secretaryPos ) {
            employees[numEmployees] = new Secretary(firstName, lastName, SIN, birthMonth,
                birthDay, birthYear, payRate, hoursWorked);
        } else if ( position == HRPos ) {
            employees[numEmployees] = new HumanResourcePerson(firstName, lastName, SIN, birthMonth,
                birthDay, birthYear, payRate, hoursWorked);
        } else if ( position == juniorSalesPos ) {
            inputFile >> salesMade;
            getline( inputFile, junk );
            employees[numEmployees] = new JrSalesperson(firstName, lastName, SIN, birthMonth,
                birthDay, birthYear, payRate, hoursWorked, salesMade);
        } else if ( position == seniorSalesPos ) {
            inputFile >> salesMade;
            getline( inputFile, junk );
            employees[numEmployees] = new SrSalesperson(firstName, lastName, SIN, birthMonth,
                birthDay, birthYear, payRate, hoursWorked, salesMade);
        } else {
            cout << "(U): Unknown employee position '" << position << "'... aborting." << endl;
            return 99;
        }
        numEmployees++;
        getline( inputFile, position );
    }

    // counter variable to be used in for loops
    int i = 0;

    // add a line break before printing reports
    cout << endl;
    cout << "-------- Printing Pay Information Report --------" << endl;
    // loop through employee array and print pay information report for each employee
    for ( i = 0; i < numEmployees; i++ ) {
        employees[i]->printPayInformationReport();
        cout << endl;
    }

    cout << "-------- Printing Employee Information Report --------" << endl; 
    // loop through employee array and print employee information report for each employee
    for ( i = 0; i < numEmployees; i++ ) {
        employees[i]->printEmployeeInformationReport();
        cout << endl;
    }

    cout << "-------- Printing Cheques --------" << endl;
    // loop through employee array and print a cheque for each employee who earned one
    for ( i = 0; i < numEmployees; i++ ) {
        employees[i]->printCheque();
        // add up total weekly company pay when printing cheques 
        totalWeeklyPay += employees[i]->getWeeklyPay();
    }

    // start of a new week
    for ( i = 0; i < numEmployees; i++ ) {
        employees[i]->reset();
    }

    // for ( i = 0; i < numEmployees; i++ ) {
    //     employees[i]->printPayInformationReport();
    //     cout << endl;
    // }

    // line break for spacing
    cout << endl;
    // print company summary with number of employees and total weekly pay out.
    cout << "-------- Company Summary --------" << endl;
    cout << "Number of Employees: " << numEmployees << endl;
    cout << "Total Weekly Pay: $" << totalWeeklyPay << endl; 
    
    cout << endl;
    
    // closing message
    cout << "Thank you for using this employee HR management system!" << endl;

    return 0;
}
