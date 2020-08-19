#include <iostream>
#include <ctime>
using namespace std;

int main (){
             cout << "\n\tWelcome To Employee Wage Program.\n" << endl;
    const int EMP_RATE_PER_HOUR = 20, FULL_TIME = 0, PART_TIME = 1;
    int empHrs, empWage, isPresent = 1;
    srand(time(0));
    
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
    empWage = empHrs * EMP_RATE_PER_HOUR;
    cout << "Employee Wage Per Day = " << empWage << endl;
}