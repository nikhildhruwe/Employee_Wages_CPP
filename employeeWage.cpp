#include <iostream>
#include <ctime>
using namespace std;

int main (){
             cout << "\n\tWelcome To Employee Wage Program.\n" << endl;
    const int EMP_RATE_PER_HOUR = 20;
    int empHrs, empWage, isPresent = 1;

    srand(time(0));
    int empCheck = rand() % 2;
    if (empCheck == isPresent)
        empHrs = 8;
    else
        empHrs = 0;
    empWage = empHrs * EMP_RATE_PER_HOUR;
    cout << "Employee Wage Per Day = " << empWage << endl;
}