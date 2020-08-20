#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
using namespace std;

string month[] = {"Jan", "Feb", "March", "April"};
int monthSize = sizeof(month)/ sizeof(month[0]);

typedef struct Company {
    string companyName;
    int NUM_OF_WORKING_DAYS;
    int MAX_MONTHLY_HRS ;
    int EMP_RATE_PER_HOUR;
    int empNumber;
    Company();
    int empWageBuilder(Company);
} company;

Company :: Company(){
    cout << "Enter Company Name: ";
    cin >> companyName;
    cout << "Enter total working days per month : ";
    cin >> NUM_OF_WORKING_DAYS;
    cout << "Enter maximum working hours : ";
    cin >> MAX_MONTHLY_HRS;
    cout << "Enter employee rate per hour : ";
    cin >> EMP_RATE_PER_HOUR;
    cout << "Enter number of employees" << endl;
    cin >> empNumber;
    cout << endl;
}
int getTotalEmpHours(company companyObj){
     const int FULL_TIME = 0, PART_TIME = 1;
    int totalEmpHrs = 0, day = 0, empHrs;

     srand(time(0));
            while ( day <= companyObj.NUM_OF_WORKING_DAYS && totalEmpHrs <= companyObj.MAX_MONTHLY_HRS){  
                day++;
                int empCheck = rand() % 3;
                switch(empCheck){
                    case FULL_TIME:
                            empHrs = 8;
                            break;
                    case PART_TIME:
                            empHrs = 4;
                            break;
                    default:
                            empHrs = 0;
                }
                totalEmpHrs += empHrs;
            }
            return totalEmpHrs;
}

int company :: empWageBuilder(company companyObj){
    int totalEmpHrs = getTotalEmpHours(companyObj);
    return totalEmpHrs * companyObj.EMP_RATE_PER_HOUR;
}

void writeToFile (string fileName, int *employee, int empNumber, int monthCount, string companyName){
    fstream fileStream;
    fileStream.open(fileName, ios::out | ios::app);
    if(fileStream.is_open()){
        fileStream.seekp(0, ios::end);
         if (fileStream.tellg() == 0){
            fileStream << "Company,employee ID,Month,Monthly Wage" << endl; 
         }  
                 fileStream.seekp(0, ios::beg);

        for (int i = 0; i < empNumber ; i++){
            fileStream << companyName << "," <<  i + 1 << "," <<month[monthCount] << ","<< employee[i] << endl;        
        }
        fileStream.close();
    }
}

void companyDetailsBuilder(company companyObj){
    int empHrs, empWage, totalEmpHrs, monthCount;
    int empNumber = companyObj.empNumber;
    string fileName = "employeeWageDetails.csv";
    
    string companyName = companyObj.companyName;
    int employee[empNumber];
     monthCount = 0;
    while (monthCount < monthSize){
        for ( int i = 0; i < empNumber ; i++){
            sleep(1.5);
            empWage = companyObj.empWageBuilder(companyObj);
            employee[i] = empWage;
            cout << "Company :" << companyName << ", employee ID :" << i + 1 <<", Employee Wage = " << empWage << ", Month: " << month[monthCount]<< endl;
        }
        writeToFile(fileName, employee, empNumber, monthCount, companyName);
        monthCount++;
    }
}

int main (){
    cout << "\n\tWelcome To Employee Wage Program." << endl;
    bool status = true;
    int numberOfCompanies, companyCount = 0;
    
    cout << "Enter Number of companies" << endl;
    cin >> numberOfCompanies;

    company companyObj[numberOfCompanies];

    while (companyCount < numberOfCompanies){
        companyDetailsBuilder(companyObj[companyCount]);
        companyCount++;
    }
}  