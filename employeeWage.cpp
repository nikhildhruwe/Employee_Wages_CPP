#include <iostream>
#include <ctime>
using namespace std;

int main (){
             cout << "\n\tWelcome To Employee Wage Program.\n" << endl;
    int isPresent = 1;
    srand(time(0));
    int empCheck = rand() % 2;
    if (empCheck == 1)
        cout << "Employee is Present" << endl;
    else
        cout << "Employee is Absent" << endl;
}