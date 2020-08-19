#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void writeToFile (string fileName, int empWage){
    fstream fileStream;
    fileStream.open(fileName, ios::out | ios::trunc);
    if(fileStream.is_open()){
        fileStream << empWage << endl;
        fileStream.close();
    }
}

int main (){
             cout << "\n\tWelcome To Employee Wage Program.\n" << endl;
    const int EMP_RATE_PER_HOUR = 20, FULL_TIME = 0, PART_TIME = 1, NUM_OF_WORKING_DAYS = 20;
    const int MAX_MONTHLY_HRS = 100;
    int empHrs, empWage, isPresent = 1, day = 0, totalEmpHrs = 0 ;
    string fileName = "employeeWageDetails.csv";
    srand(time(0));

  while ( day <= NUM_OF_WORKING_DAYS && totalEmpHrs <= MAX_MONTHLY_HRS){  
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
    empWage = totalEmpHrs * EMP_RATE_PER_HOUR;
    writeToFile(fileName, empWage);
    cout << "Employee Wage Per Day = " << empWage << endl;
}