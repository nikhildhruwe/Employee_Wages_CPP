#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <list>
#include <sstream>
#include <vector>
using namespace std;

string month[] = {"Jan", "Feb", "March", "April"};
int monthSize = sizeof(month)/ sizeof(month[0]);
list <int> dailyWagesList;
list <int> currentTotalWageList;


typedef struct EmployeeDetails{
    string companyName;
    int employeeID;
    string month;
    int dayNo;
    int wagePerHour;
    int dailyWage;
    int currentTotalWage;
}employeeDetails;

typedef struct employeeSort{
    int monthlyWage;
    int employeeID;
    string companyName;
    string month;
    int dailyWage;
    int dayNo;
    employeeSort(int monthlyWage, int empID, string companyName, string month, int dailyWage, int dayNo){
        this -> monthlyWage = monthlyWage;
        this -> employeeID = empID;
        this -> companyName = companyName;
        this -> month = month;
        this ->dailyWage = dailyWage;
        this ->dayNo = dayNo;
    }
}employeeSort;

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
            while ( (day < companyObj.NUM_OF_WORKING_DAYS) && (totalEmpHrs <= companyObj.MAX_MONTHLY_HRS)){
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
                int dailyWage = empHrs*companyObj.EMP_RATE_PER_HOUR;
                dailyWagesList.push_back(dailyWage);
                totalEmpHrs += empHrs;
                currentTotalWageList.push_back(totalEmpHrs*companyObj.EMP_RATE_PER_HOUR);
            }
        return totalEmpHrs;
}

int company :: empWageBuilder(company companyObj){
    int totalEmpHrs = getTotalEmpHours(companyObj);
    return totalEmpHrs * companyObj.EMP_RATE_PER_HOUR;
}

void writeToFile (string fileName, int monthCount, company companyObj, int employeeID){
    int totalDays = companyObj.NUM_OF_WORKING_DAYS;
    string companyName = companyObj.companyName;
    int employeeNumber = companyObj.empNumber;
    int wagePerHour = companyObj.EMP_RATE_PER_HOUR;
    int dayCount;
    list <int> :: iterator dailyWage = dailyWagesList.begin();
    list <int> :: iterator currentTotalWage = currentTotalWageList.begin();

    fstream fileStream;
    fileStream.open(fileName, ios::out | ios::app);
    if(fileStream.is_open()){
        fileStream.seekp(0, ios::end);
        if (fileStream.tellg() == 0){
            fileStream << "Company, Employee-ID, Month, Day No., Daily Wage, Wage Per-Hour,totalWage-current ";
        }

        fileStream.seekp(0, ios::beg);
        for (dayCount = 0 ; dailyWage != dailyWagesList.end() ; dayCount++, dailyWage++, currentTotalWage++ ){
            fileStream << "\n" << companyName << "," <<  employeeID << "," << month[monthCount] << "," << dayCount + 1
            << "," <<  *dailyWage << "," << wagePerHour << "," << *currentTotalWage;
            }
        fileStream.close();
    }
}

vector<string> split(const string& line, char delimiter){
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);
    while (std::getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

list <employeeDetails> readFromFile (string fileName){
    fstream fileStream;
    list <employeeDetails> employeeDetailsList;

    fileStream.open(fileName, ios::in);
    if (fileStream.is_open()){
        vector <string> details;
        string line, word;
        getline(fileStream, line);

        while (!fileStream.eof()) {
            details.clear();
            getline(fileStream, line);
            stringstream s(line);

            while (getline(s, word)){
                details = split(word, ',');
                EmployeeDetails employeeDetails;
                employeeDetails.companyName = details[0];
                employeeDetails.employeeID = stoi(details[1]);
                employeeDetails.month = details[2];
                employeeDetails.dayNo = stoi(details[3]);
                employeeDetails.dailyWage = stoi(details[4]);
                employeeDetails.wagePerHour = stoi(details[5]);
                employeeDetails.currentTotalWage = stoi(details[6]);
                employeeDetailsList.push_back(employeeDetails);
            }
        }
    }
    fileStream.close();
    return employeeDetailsList;
}

void companyDetailsBuilder(company companyObj){
    string fileName = "employeeWageDetails.csv";
    int empHrs, empWage, totalEmpHrs, monthCount, empNumber;

    empNumber = companyObj.empNumber;
    string companyName = companyObj.companyName;
    cout << endl ;
    int i = 0;
    for ( int empCount = 0; empCount < empNumber ; empCount++){
        monthCount = 0;
        while (monthCount < monthSize){
            sleep(1.5);
            empWage = companyObj.empWageBuilder(companyObj);
            cout << "Company :" << companyName << ", employee ID :" << (empCount + 1) <<", Employee Wage = " << empWage << ", Month: " << month[monthCount]<< endl;
            writeToFile(fileName, monthCount, companyObj, empCount + 1);
            dailyWagesList.clear();
            currentTotalWageList.clear();
            monthCount++;
            }
        }
}

vector <employeeSort> getDailyWageList(list<company> companyList){
    list <employeeDetails> employeeDetailsList = readFromFile("employeeWageDetails.csv");
    list <employeeDetails> :: iterator empObj;
    vector <employeeSort> employeeDailyList;

    for ( empObj = employeeDetailsList.begin(); empObj != employeeDetailsList.end(); empObj++){
        employeeSort employeeSort( empObj -> currentTotalWage, empObj ->employeeID, empObj->companyName, empObj->month,empObj->dailyWage, empObj ->dayNo);
        employeeDailyList.push_back(employeeSort);
    }
    return employeeDailyList;
}

vector <employeeSort> getMonthlyWageList(list<company> companyList){
    list <employeeDetails> employeeDetailsList = readFromFile("employeeWageDetails.csv");
    list <company> :: iterator companyObj;
    list <employeeDetails> :: iterator empObj;
    vector <employeeSort> employeeMonthlyList;
    int totalEmpWage = 0;
    string company;
    int totalEmployees;
    int totalDays;
    int day;
    int empCount;
    int flag = 0;

    for ( companyObj = companyList.begin(); companyObj!=companyList.end(); companyObj++){
        totalEmployees = (*companyObj).empNumber;
        totalDays = (*companyObj).NUM_OF_WORKING_DAYS;
        company =  (*companyObj).companyName;
        empObj = employeeDetailsList.begin();
        for (empCount = 0; empCount < totalEmployees; empCount++){
            for (int monthCount = 0; monthCount < monthSize; monthCount++){
                totalEmpWage = 0;
                 while( !((*empObj).companyName == company && ((*empObj).employeeID == (empCount + 1)) && (*empObj).month == month[monthCount])){
                        empObj++;
                        }
                while ((*empObj).month == month[monthCount] && empObj != employeeDetailsList.end()) {
                    totalEmpWage = empObj ->currentTotalWage;
                    empObj++;
                }
                employeeSort empSortObj(totalEmpWage, empCount + 1, company, month[monthCount], empObj->dailyWage, empObj ->dayNo );
                employeeMonthlyList.push_back(empSortObj);
            }
        }
    }
    return employeeMonthlyList;
}

void display(vector <employeeSort> employeeWageList){
     for (int i = 0; i < employeeWageList.size() ; i++){
      cout << "Company: " << employeeWageList[i].companyName << ", EmployeeID: " << employeeWageList[i].employeeID << ", Month :"
      << employeeWageList[i].month << ", Monthly Wage: " << employeeWageList[i].monthlyWage
      << ", Daily Wages: "<< employeeWageList[i].dailyWage << endl;
    }
}

 void searchEmployeeByWagePerHr(list <Company> companyList){
    list <employeeDetails> employeeDetailsList = readFromFile("employeeWageDetails.csv");
    list <employeeDetails> :: iterator empObj;
    vector <employeeSort> employeeDailyList;
    int empWagePerHour, flag = 0;
    cout << "Enter Wage Per Hour to search the employee" << endl;
    cin >> empWagePerHour;

    for ( empObj = employeeDetailsList.begin(); empObj != employeeDetailsList.end(); empObj++){
        if (empObj->wagePerHour == empWagePerHour){
        employeeSort employeeSort( empObj -> currentTotalWage, empObj ->employeeID, empObj->companyName, empObj->month,empObj->dailyWage, empObj ->dayNo);
        employeeDailyList.push_back(employeeSort);
        flag = 1;
        }
    }

    if (flag != 1){
        cout << "No Employee with with wage per hour : " << empWagePerHour << endl;
        return;
    }
    display(employeeDailyList);
}

void sortByMonthlyWage(vector <employeeSort> employeeWageList){
    for (int i = 0; i < employeeWageList.size() - 1 ; i++){
        for (int j = 0; j < employeeWageList.size() - i - 1 ; j++){
            if (employeeWageList[j].monthlyWage < employeeWageList[j+1].monthlyWage){
                    swap (employeeWageList[j], employeeWageList[j+1]);
            }
        }
    }
    display(employeeWageList);
}

void sortByDailylyWage(vector <employeeSort> employeeWageList){
for (int i = 0; i < employeeWageList.size() ; i++){
        for (int j = 0; j < employeeWageList.size() - i; j++){
            if (employeeWageList[j].dailyWage < employeeWageList[j+1].dailyWage){
                    swap (employeeWageList[j], employeeWageList[j+1]);
            }
        }
    }
    display(employeeWageList);
}

list <company> insertCompanyDetails( list <company> companyList ){
    company companyObj;
    companyList.push_back(companyObj);
    companyDetailsBuilder(companyObj);
    return companyList;
}

void displayOptions(){
    bool status = true;
    string fileName = "employeeWageDetails.csv";
    list <company> companyList;
    vector <employeeSort> employeeWageList;

     while (status){
      cout << "\n  Choose Operation.\n1.Insert Company Details."
      "\n2.Sort By Monthly Wage.\n3.Sort By Daily Wages\n4.Search Employee by Wage-Per-Hour\n5.Exit" << endl;
      int choice;
      cin >> choice;
      switch (choice){
            case 1 :
                companyList = insertCompanyDetails(companyList);
                break;
            case 2:
                employeeWageList.clear();
                employeeWageList = getMonthlyWageList(companyList);
                sortByMonthlyWage(employeeWageList);
                break;
            case 3:
                employeeWageList.clear();
                employeeWageList = getDailyWageList(companyList);
                sortByDailylyWage(employeeWageList);
                break;
            case 4:
                employeeWageList.clear();
                searchEmployeeByWagePerHr(companyList);
                break;
            case 5 :
                status = false;
                break;
            default:
                cout << "Invalid Input" << endl;
      }
  }
}

int main (){
    cout << "\n\tWelcome To Employee Wage Program." << endl;
    displayOptions();
}
