#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
    Purpose: To read in the information of several different employees (manager, secretaries, salespeople)
             from a file, procces their information, and print three reports summarizing their personal
             information and pay related information. The program will also print a summary of the companies
             weekly payout and the number of employees they have.
    Author: Daniel Kaichis
    Status: DONE
*/

// the rate at which salespeople earn commission (2% of sales)
const double commissionRate = 0.02; 
// the minimum wage an employee can be paid per hour
const double minimumWage = 14.0;

// variables to store the maximum number of each type of employee at the company
const int maxManagers = 5;
const int maxSecretaries = 7;
const int maxSalespeople = 15;

// the number of hours a manager is paid for working on a weekly basis
const int managerWeeklyHours = 40;

/* ------------------------- START OF STRUCT NAME --------------------------- */

// Purpose: A struct for the name of a person
typedef struct {
    // char array for the persons first name
	char firstName[50];
    // char array for the persons last name
    char lastName[50];
} Name;

/* 
* Purpose: To get a name from a file
* Parameters: file - the pointer to the file the name is being scanned in from
              name - the Name struct being initialized 
* Returns: NONE
* SideEffects: the file pointer is modified because the first and last name are scanned in, the name is initialized
               to an employees first and last name
*/
void getName(FILE* file, Name *name) {
    // scan in first and last name from the file to the name first and last name variables of the Name
    fscanf(file, "%s", name->lastName);
    fgetc(file);
    fscanf(file, "%s", name->firstName);
    fgetc(file);
}

/* 
* Purpose: To print a Name to stdout
* Parameters: name - the Name to be printed
              seperator - the character(s) to seperate the first and last names
              lastNameFirst - an int to store wether to print the last name first or not
* Returns: NONE
* SideEffects: NONE
*/
void printName(const Name *name, const char* seperator, const int lastNameFirst) {
    // if last name first. print the last name, the seperator, and the first name
    if (lastNameFirst) {
        printf("%s%s%s", name->lastName, seperator, name->firstName);
    // first name first. print the first name, the seperator, and the last name   
    } else {
        printf("%s%s%s", name->firstName, seperator, name->lastName);
    }
}
/* ------------------------- END OF STRUCT NAME --------------------------- */

/* ------------------------- START OF STRUCT DATE --------------------------- */

// a struct for a date with a month day and year
typedef struct {
	char month[50];     // the month string of the Date
	int day;            // the day number of the Date
	int year;           // the year number of the Date
} Date;

/* 
* Purpose: To get a Date from a file
* Parameters: file - the pointer to the file the date is being scanned in from
              date - the Date struct being initialized
* Returns: NONE
* SideEffects: the file pointer is modified when the date is scanned in,
               the date is initialized to a date from the file
*/
void getDate(FILE* file, Date *date) {
    // scan in the month day and year to the Date struct
    fscanf(file, "%s", date->month);
    fgetc(file);
    fscanf(file, "%d", &date->day);
    fgetc(file);
    fscanf(file, "%d", &date->year);
}

/* 
* Purpose: To print a Date to sdout
* Parameters: date - the Date to be printed
* Returns: NONE
* SideEffects: NONE
*/
void printDate(const Date *date) {
    // print Date in format month day, year
    printf("%s %d, %d\n", date->month, date->day, date->year);
}
/* ------------------------- END OF STRUCT DATE --------------------------- */

/* ------------------------- START OF STRUCT PERSONALINFO --------------------------- */

// a struct to hold the personal information of an employee
typedef struct {
	Date birthday;      // a Date for the employees birthday
	char SIN[10];       // a character array for the employees 9 digit SIN
} PersonalInfo;

/* 
* Purpose: To get the personal info of an employee from a file
* Parameters: file - the pointer to the file the personal info is being scanned in from
              personalInfo - the PersonalInfo struct being initialized
* Returns: NONE
* SideEffects: file pointer is modified when data is scanned in, personalInfo is initialized
               with the information from the file
*/
void getPersonalInfo(FILE* file, PersonalInfo *personalInfo) {
    // scan in the SIN from the file
	fscanf(file, "%s", personalInfo->SIN);
    fgetc(file);

    // get the employees birthday from the file
    getDate(file, &personalInfo->birthday);
}

/* 
* Purpose: To print an employees personal information
* Parameters: personalInfo - the PersonalInfo struct with the information to be printed
* Returns: NONE
* SideEffects: NONE
*/
void printPersonalInfo(const PersonalInfo *personalInfo) {
    // print birthday and sin of the employee from the personalInfo struct
    printf("Birthday: ");
    printDate(&personalInfo->birthday);
    printf("SIN: %s\n", personalInfo->SIN);
}
/* ------------------------- END OF STRUCT PERSONALINFO --------------------------- */

/* ------------------------- START OF STRUCT PAYINFO --------------------------- */

// struct to hold an employees pay information
typedef struct {
	double hourlyPay;       // the hourly wage of an employee
	double hoursWorked;     // the number of hours an employee worked in a week
	double amountOwed;      // the amount of money owed to an employee for a week
} PayInfo;

/* 
* Purpose: To get the PayInfo of an employee from a file
* Parameters: file - the pointer to the file the pay information is being scanned in from
              payInfo - the PayInfo struct the information is being scanned in to
* Returns: NONE
* SideEffects: file pointer is modified when the information is scanned in,
               payInfo is initialized with the information from the file
*/
void getPayInfo(FILE *file, PayInfo *payInfo) {
	// get the hourly pay of an employee from the file
    fscanf(file, "%lf", &payInfo->hourlyPay);
    fgetc(file);
    // get the hours and employee worked in a week from the file
    fscanf(file, "%lf", &payInfo->hoursWorked);
}

/* 
* Purpose: To print the pay information of an employee
* Parameters: info - the PayInfo to be printed
* Returns: NONE
* SideEffects: NONE
*/
void printPayInfo(const PayInfo *info) {
    // print the hourly wage and hours worked of the employee
    printf("Hourly Wage: $%1.2lf\n", info->hourlyPay);
    printf("Hours Worked: %1.2lf\n", info->hoursWorked);
}

/* 
* Purpose: To calculate the normal pay of an employee (hours worked times wage)
* Parameters: payInfo - the Payinfo struct to be used in the calculation
* Returns: NONE
* SideEffects: NONE
*/
double calcNormalPay(PayInfo *payInfo) {
    // return hours worked times hourly pay which is the base/normal amount owed to an employee for a weeks work
    return payInfo->hoursWorked * payInfo->hourlyPay;
}

/* ------------------------- END OF STRUCT PAYINFO --------------------------- */

/* ------------------------- START OF STRUCT COMMONINFO --------------------------- */

// struct to hold the common info shared by all employees 
typedef struct {
	char position[512];         // the position the employee holds in the company
	Name name;                  // the employees name
	PersonalInfo personalInfo;  // the employees personal information (name and SIN)
	PayInfo payInfo;            // the employees pay information
} CommonInfo;

/* 
* Purpose: To get the common information for an employee from a file
* Parameters: file - the pointer to the file the information is being scanned in from
              commonInfo - the CommonInfo struct being initialized
* Returns: NONE
* SideEffects: commonInfo is initialized with the information from the file,
               file pointer is modified.
*/
void getCommonInfo(FILE *file, CommonInfo *commonInfo) {
    // get the employee name, personal info, and payinfo from the file
    getName(file, &commonInfo->name);
    getPersonalInfo(file, &commonInfo->personalInfo);
    getPayInfo(file, &commonInfo->payInfo);

    // validate hourly pay is between $14-100 per hour inclusive 
    // this is done here where a name can be accessed for better error reporting
    if ((commonInfo->payInfo.hourlyPay > 100) || (commonInfo->payInfo.hourlyPay < 14)) {
        // report error
        printf("ERROR: Employee ");
        printName(&commonInfo->name, " ", 0);
        printf(" is earning $%1.2lf per hour. Pay will be set to $%1.2lf per hour.\n", commonInfo->payInfo.hourlyPay, minimumWage);
        // change hourly pay to $14 so employee will know to come to management to address the problem
        commonInfo->payInfo.hourlyPay = 14;
    }

    // validate employee hours is greater than or equal to 0
    // this is done here where a name can be accessed for better error reporting
    if (commonInfo->payInfo.hoursWorked < 0) {
        printf("ERROR: Employee ");
        printName(&commonInfo->name, " ", 0);
        printf(" is said to have worked '%1.2lf' hours. Hours will be set to 0.\n", commonInfo->payInfo.hoursWorked);
        commonInfo->payInfo.hoursWorked = 0;
    }
}

/* 
* Purpose: To print the common pay information of an employee for the pay information report
           the report has different requirements for all employee types so this function prints the information
           they all have in common
* Parameters: commonInfo - the information to be printed
* Returns: NONE
* SideEffects: NONE
*/
void printCommonPayInformation(const CommonInfo *commonInfo) {
    // print employee position, name, and payinfo
    printf("Position: %s\n", commonInfo->position);
    printf("Name: ");
    printName(&commonInfo->name, ", ", 1);
    printf("\n");
    printPayInfo(&commonInfo->payInfo);
}

/* 
* Purpose: To print the employee information report
* Parameters: commonInfo - the CommonInfo struct with the information to be printed
* Returns: NONE
* SideEffects: NONE
*/
void printEmployeeInformationReport(const CommonInfo *commonInfo) {
    // print employee name, position, personal information, and hourly wage
    // in a user friendly way
    printf("Name: ");
    printName(&commonInfo->name, ", ", 1);
    printf("\n");
    printf("Position: %s\n", commonInfo->position);
    printPersonalInfo(&commonInfo->personalInfo);
    printf("Hourly Wage: $%1.2lf\n", commonInfo->payInfo.hourlyPay);
    printf("\n");
}

/* 
* Purpose: To print a cheque for an employee
* Parameters: commonInfo - the CommonInfo struct containing the information to be printed in the cheque
* Returns: NONE
* SideEffects: NONE
*/
void printCheque(const CommonInfo *commonInfo) {
    // if the employee has earned more than 0 dollars print a cheque
    // this validation is done here to save money on paper if a cheque is
    // attempted to be printed for 0 dollars
    if (commonInfo->payInfo.amountOwed != 0) {
        // print the cheque to the employee for the amount of money they earned in a week
        printf("Payable to ");
        printName(&commonInfo->name, " ", 0);
        printf(" in the amount of $%1.2lf.\n", commonInfo->payInfo.amountOwed);
        printf("\n");
    }
}
/* ------------------------- END OF STRUCT COMMONINFO --------------------------- */

/* ------------------------- START OF STRUCT MANAGER --------------------------- */

// struct to hold the information of a manager in the company
typedef struct {
	CommonInfo commonInfo;     // the CommonInfo of a manager
} Manager;

/* 
* Purpose: To calculate the weekly amount of money owed to a manager
* Parameters: manager - the manager to calculate the pay of
* Returns: the amount of money owed to a manager in a week
* SideEffects: manager amountOwed is modified when it is calculated
*/
double calcManagerAmountOwed(Manager *manager) {
    // multiply the number of hours a manager works by the amount they are paid per hour
    // (hours is constant as they are actually paid on a yearly salary but this has been converted for the purpose of this program)
    manager->commonInfo.payInfo.amountOwed = managerWeeklyHours * manager->commonInfo.payInfo.hourlyPay;
    // return the amount owed to a manager 
    return manager->commonInfo.payInfo.amountOwed;
}

/* 
* Purpose: To get a manager and their information from a file
* Parameters: file - the pointer to the file the information is coming from
              manager - the Manager struct being initialized
* Returns: NONE
* SideEffects: manager is initialized with the information from the file,
               file pointer is modified
*/
void getManager(FILE *file, Manager *manager) {
    // call getCommonInfo to scan the common information into the manager struct
    getCommonInfo(file, &manager->commonInfo);
    // calculate the amount of money owed to the manager 
    calcManagerAmountOwed(manager);
}

/* 
* Purpose: To print the pay information of a manager
* Parameters: manager - the Manager the information is being printed for
* Returns: NONE
* SideEffects: NONE
*/
void printManagerPayInformation(const Manager *manager) {
    // print the common payinformation of a manager and their weekly pay owed
    printCommonPayInformation(&manager->commonInfo);
    printf("Weekly Pay: $%1.2lf\n", manager->commonInfo.payInfo.amountOwed);
    printf("\n");
}
/* ------------------------- END OF STRUCT MANAGER --------------------------- */

/* ------------------------- START OF STRUCT SECRETARY --------------------------- */

// struct to hold the information of a secretary in the company
typedef struct {
	CommonInfo commonInfo;
	double normalPay;
    double overtimePay;
} Secretary;

/* 
* Purpose: To calculate the overtime pay a secretary earns in a week
* Parameters: secretary - the Secretary the overtime pay is being calculated for
              overtimeHours - the hours of overtime a secretary has worked
* Returns: the secretaries overtime pay
* SideEffects: secretary overtimePay is modified when it is calculated
*/
double calcOvertimePay(Secretary *secretary, double overtimeHours) {
    // pay secretary time and a half for every hour they have worked after 40 hours 
    secretary->overtimePay = overtimeHours * (secretary->commonInfo.payInfo.hourlyPay * 1.5);
    
    return secretary->overtimePay;
}

/* 
* Purpose: To calculate the amount of money owed to a secretary for a week of work
* Parameters: secretary - the Secretary to calculate the amount of money owed to them
* Returns: NONE
* SideEffects: secretary is modified 
*/
void calcSecretaryAmountOwed(Secretary *secretary) {
    double overtimeHours = 0;
    
    // if secretary worked over 60 hours print error message and
    // set hours worked to 0 so they can address the issue with management
    if (secretary->commonInfo.payInfo.hoursWorked > 60) {
        printf("ERROR: Secretary ");
        printName(&secretary->commonInfo.name, " ", 0);
        printf(" has worked %1.2lf hours. Hours will be set to 0.\n", secretary->commonInfo.payInfo.hoursWorked);
        secretary->commonInfo.payInfo.hoursWorked = 0;
        // set normal pay to 0 because hours has been set to 0 so they can address the issue with management
        // because 0 hours times any wage is 0
        secretary->normalPay = 0;
    // secretary has worked over 40 hours and less than 60 hours so they have earned overtime
    } else if (secretary->commonInfo.payInfo.hoursWorked > 40) {
        // their normal pay is equal to the 40 base hours times their standard hourly wage
        secretary->normalPay = 40 * secretary->commonInfo.payInfo.hourlyPay;
        // overtime hours is the number of hours they have worked past 40 hours
        overtimeHours = secretary->commonInfo.payInfo.hoursWorked - 40;
    // secretary worked less than 40 hours and earns no overtime
    // their normal pay is their hourly wage times the number of hours they worked
    } else {
        secretary->normalPay = calcNormalPay(&secretary->commonInfo.payInfo);
        overtimeHours = 0;
    }

    // the amount owed to a secretary is their overtime plus their normal pay
    secretary->commonInfo.payInfo.amountOwed = calcOvertimePay(secretary, overtimeHours) + secretary->normalPay;
}

/* 
* Purpose: To get a secretary and their information from a file
* Parameters: file - the pointer to the file the information is coming from
              secretary - the Secretary struct being initialized
* Returns: NONE
* SideEffects: secretary is initialized with the information from the file, file pointer is modified
*/
void getSecretary(FILE *file, Secretary *secretary) {
    // get the common info of a secretary and calculate how much they are owed in a week
    getCommonInfo(file, &secretary->commonInfo);
    calcSecretaryAmountOwed(secretary);
}

/* 
* Purpose: To print the secretaries pay information
* Parameters: secretary - the secretary whos information is printed
* Returns: NONE
* SideEffects: NONE
*/
void printSecretaryPayInformation(const Secretary *secretary) {
    // print secretary common information
    printCommonPayInformation(&secretary->commonInfo);
    // print weekly pay
    printf("Weekly Pay: $%1.2lf\n", secretary->commonInfo.payInfo.amountOwed);
    // print breakdown of secretary normal pay and overtime pay if they have any overtime
    if (secretary->overtimePay > 0) {
        printf("Normal Pay: $%1.2lf\n", secretary->normalPay);
        printf("Overtime Pay: $%1.2lf\n", secretary->overtimePay);
    }
    printf("\n");
}
/* ------------------------- END OF STRUCT SECRETARY --------------------------- */

/* ------------------------- START OF STRUCT SALESPERSON --------------------------- */

// struct to hold the information of a salesperson in the company
typedef struct {
	CommonInfo commonInfo;
	double normalPay;
    double sales;
    double commission;
} Salesperson;

/* 
* Purpose: To calculate the commission earned by a salesperson
* Parameters: salesperson - the Salesperson whos commission is calculated
* Returns: the commission earned by a salesperson
* SideEffects: salesperson is modified with the commission they earned
*/
double calcCommission(Salesperson *salesperson) {
    // salesperson worked more than 0 hours so they have had the opportunity to make sales
    if (salesperson->commonInfo.payInfo.hoursWorked > 0) {
        // commission equals sales times commissionRate (2%)
        salesperson->commission = salesperson->sales * commissionRate;
    // salesperson worked 0 hours so can not have made any sales
    } else {
        // print error
        printf("ERROR: Salesperson ");
        printName(&salesperson->commonInfo.name, " ", 0); 
        printf(" has worked 0 hours but is said to have earned $%1.2lf in sales.\n", salesperson->sales);
        printf("Commission has been set to 0.\n");
        salesperson->commission = 0;
    }

    // return commission
    return salesperson->commission;
}

/* 
* Purpose: To calculate the amount of money owed to a salesperson in a week
* Parameters: salesperson - the Salesperson who's amount owed is calculated
* Returns: NONE
* SideEffects: salesperson is modified when the calculations are done
*/
void calcSalespersonAmountOwed(Salesperson *salesperson) {
    // if salesperson worked greater than or equal 40 hours, only pay them for the 40 they worked because
    // they cannot earn overtime
    if (salesperson->commonInfo.payInfo.hoursWorked >= 40) {
        // normal pay is 40 hours times their hourly wage
        salesperson->normalPay = 40 * salesperson->commonInfo.payInfo.hourlyPay;
    // salesperson worked less than 40 hours so normal pay is their total hours times their hourly pay
    } else {
        salesperson->normalPay = calcNormalPay(&salesperson->commonInfo.payInfo);
    }
    // amount owed is commission plus normal pay
    salesperson->commonInfo.payInfo.amountOwed = calcCommission(salesperson) + salesperson->normalPay;
}

/* 
* Purpose: To get a salesperson from a file
* Parameters: file - the pointer to the file the information is coming from
              salesperson - the Salesperson struct being initialized
* Returns: NONE
* SideEffects: file pointer is modified,
               salesperson is initialized with the information from the file
*/
void getSalesperson(FILE *file, Salesperson *salesperson) {
    // get salesperson common info, sales, and calculate their amount owed for a week
    getCommonInfo(file, &salesperson->commonInfo);
    fscanf(file, "%lf", &salesperson->sales);
    fgetc(file);
    calcSalespersonAmountOwed(salesperson);
}

/* 
* Purpose: To print the pay information of a salesperson
* Parameters: salesperson - the Salesperson whos information is being printed
* Returns: NONE
* SideEffects: NONE
*/
void printSalespersonPayInformation(const Salesperson *salesperson) {
    // print the common pay information of the salesperson, their weekly pay
    // and a breakdown of their normal pay and commission earned if they have earned any.
    printCommonPayInformation(&salesperson->commonInfo);
    printf("Weekly Pay: $%1.2lf\n", salesperson->commonInfo.payInfo.amountOwed);
    if (salesperson->commission > 0) {
        printf("Normal Pay: $%1.2lf\n", salesperson->normalPay);
        printf("Commission Earned: $%1.2lf\n", salesperson->commission);
    }
    printf("\n");
}
/* ------------------------- END OF STRUCT SALESPERSON --------------------------- */

/* 
* Purpose: To open a file from the user for reading
* Parameters: filename - the user inputtted filename of the file to be opened for reading
* Returns: file - the pointer to the file that is opened
* SideEffects: NONE
*/
FILE* openUserReadFile(const char* filename) {
    // open a file of the name filename for reading
    FILE *file;
    file = fopen(filename, "r");
    // if file is NULL print an error
    if (file == NULL) {
        printf("ERROR: File '%s' not found.\n", filename);
    } 
    return file;
}

int main() {
    // initialize file pointer
    FILE *file;
    // initialize variable to store if the loop has reached the end of the file
    int END = 0;
    // initialize character arrays for the filename and position strings
    char filename[512];
    char position[512];
    // initialize counters of the number of each employee type
    int numManagers = 0;
    int numSecretaries = 0;
    int numSalespeople = 0;
    // initialize array index counters for printing the reports
    int managerIndex = 0;
    int secretaryIndex = 0;
    int salespersonIndex = 0;
    // initialize variables for the company summary variables
    int numEmployees = 0;
    double weeklyPayout = 0;
    // initialize a name struct for reading in an employee name in the case
    // of too many employees being inputted for error reporting
    Name name;

    // initialize array of each employee type with the size of the maximum number of each employee type
    Manager managers[maxManagers];
    Secretary secretaries[maxSecretaries];
    Salesperson salespeople[maxSalespeople];

    // opening statement
    printf("Welcome to the universes best employee HR management system.\n");

    // get user to input filename and open the file
    printf("Enter the name of the file you would like to open: ");
    scanf("%s", filename);
    file = openUserReadFile(filename);

    // file not found so quiting the program
    if (file == NULL) {
        printf("Quiting the program.\n");
        // return 1 to end the program
        return 1;
    }

    printf("\n");

    // while END is false loop and scan in employees
    while (!END){
        // scan in the position of the employee to the position placeholder to check the employee type
        // if the inputted employee is not valid (more than max num of employee type), the loop
        // will scan in all their information (except name which is proccess for error reporting)
        // as it iterates through each line and will do this until it reaches the next line with
        // a valid employee position. This way if the max num of employees is reached for a certain 
        // position, that employee is still processed but the information is not stored
        // to move to the next employee in the file
        fscanf(file, "%s", position);
        fgetc(file);
        // position is manager
        if (strcmp(position, "manager") == 0) {
            // number of managers is less than the maximum allowed for the company
            // this is less than and not equal to because indexing starts at 0
            // ie. 0-14 indexes in an employee array holds 15 employees so this checks
            // that the num of managers has not reached the max
            if (numManagers < maxManagers) {
                // copy position into the manager struct
                strcpy(managers[numManagers].commonInfo.position, position);
                // get the managers information
                getManager(file, &managers[numManagers]);
                // add managers weekly amount owed to the company total
                weeklyPayout += managers[numManagers].commonInfo.payInfo.amountOwed;
                // increment num of managers by 1
                numManagers++;
            // more than the max num of managers have been attempted to be inputed
            } else {
                // get the employee name and print an error. employee is not scanned into any array to be stored
                getName(file, &name);
                printf("ERROR: Manager ");
                printName(&name, " ", 0);
                printf(" could not be stored in the database as the company has over %d managers.\n", maxManagers);
            }
        // position is secretary
        } else if (strcmp(position, "secretary") == 0) {
            // number of secretaries is less than the maximum allowed for the company
            // this is less than and not equal to because indexing starts at 0
            // ie. 0-14 indexes in an employee array holds 15 employees so this checks
            // that the num of secretaries has not reached the max
            if (numSecretaries < maxSecretaries) {
                // copy position into the secretary struct
                strcpy(secretaries[numSecretaries].commonInfo.position, position);
                // get the secretaries information
                getSecretary(file, &secretaries[numSecretaries]);
                // add secretaries weekly amount owed to the company total
                weeklyPayout += secretaries[numSecretaries].commonInfo.payInfo.amountOwed;
                // increment num of secretaries by 1
                numSecretaries++;
            // more than the max num of secretaries have been attempted to be inputed
            } else {
                // get the employee name and print an error. employee is not scanned into any array to be stored
                getName(file, &name);
                printf("ERROR: Secretary ");
                printName(&name, " ", 0);
                printf(" could not be stored in the database as the company has over %d secretaries.\n", maxSecretaries);
            }
        // position is salesperson
        } else if (strcmp(position, "salesperson") == 0) {
            // number of salesperson is less than the maximum allowed for the company
            // this is less than and not equal to because indexing starts at 0
            // ie. 0-14 indexes in an employee array holds 15 employees so this checks
            // that the num of salespeople has not reached the max
            if (numSalespeople < maxSalespeople) {
                // copy position into the salesperson struct
                strcpy(salespeople[numSalespeople].commonInfo.position, position);
                // get the salespersons information
                getSalesperson(file, &salespeople[numSalespeople]);
                // add salespersons weekly amount owed to the company total
                weeklyPayout += salespeople[numSalespeople].commonInfo.payInfo.amountOwed;
                // increment num of salespeople by 1
                numSalespeople++;
            // more than the max num of salespeople have been attempted to be inputed
            } else {
                // get the employee name and print an error. employee is not scanned into any array to be stored
                getName(file, &name);
                printf("ERROR: Salesperson ");
                printName(&name, " ", 0);
                printf(" could not be stored in the database as the company has over %d salespeople.\n", maxSalespeople);
            }
        // position was set to END so break the loop as there are no more employees
        } else if (strcmp(position, "END") == 0) {
            END = 1;
        }
    }

    // calculate the number of employees in the company by adding the number of each employee type
    numEmployees = numManagers + numSecretaries + numSalespeople;

    printf("\n");

    // print the pay information report
    printf("-------------- Printing Pay Information Report --------------\n");
    // loop through all inputted managers
    for (managerIndex = 0; managerIndex < numManagers; managerIndex++) {
        //print pay information report for manager
        printManagerPayInformation(&managers[managerIndex]);
    }
    // loop through all inputted secretaries
    for (secretaryIndex = 0; secretaryIndex < numSecretaries; secretaryIndex++) {
        //print pay information report for secretary
        printSecretaryPayInformation(&secretaries[secretaryIndex]);
    }
    // loop through all inputted salespeople
    for (salespersonIndex = 0; salespersonIndex < numSalespeople; salespersonIndex++) {
        //print pay information report for salesperson
        printSalespersonPayInformation(&salespeople[salespersonIndex]);
    }

    // print the employee information report
    printf("-------------- Printing Employee Information Report --------------\n");
    // loop through all inputted managers
    for (managerIndex = 0; managerIndex < numManagers; managerIndex++) {
        // print employee information report for manager
        printEmployeeInformationReport(&managers[managerIndex].commonInfo);
    }
    // loop through all inputted secretaries
    for (secretaryIndex = 0; secretaryIndex < numSecretaries; secretaryIndex++) {
        // print employee information report for secretary
        printEmployeeInformationReport(&secretaries[secretaryIndex].commonInfo);
    }
    // loop through all inputted salespeople
    for (salespersonIndex = 0; salespersonIndex < numSalespeople; salespersonIndex++) {
        // print employee information report for salesperson
        printEmployeeInformationReport(&salespeople[salespersonIndex].commonInfo);
    }

    // print cheques for employees
    printf("-------------- Printing Cheques --------------\n");
    // loop through all inputted managers
    for (managerIndex = 0; managerIndex < numManagers; managerIndex++) {
        // print cheque for manager
        printCheque(&managers[managerIndex].commonInfo);
    }
    // loop through all inputted secretaries
    for (secretaryIndex = 0; secretaryIndex < numSecretaries; secretaryIndex++) {
        // print cheque for secratary
        printCheque(&secretaries[secretaryIndex].commonInfo);
    }
    // loop through all inputted salespeople
    for (salespersonIndex = 0; salespersonIndex < numSalespeople; salespersonIndex++) {
        // print cheque for salesperson
        printCheque(&salespeople[salespersonIndex].commonInfo);
    }

    // print company summary of number of employees and weekly payout
    printf("-------------- Company Summary --------------\n");
    printf("Number of Employees: %d\n", numEmployees);
    printf("Weekly Payout: $%1.2lf\n", weeklyPayout);

    // closing statement
    printf("\nThank you for using the universes best employee HR management system.\n");

    return (EXIT_SUCCESS);
}