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

typedef struct EmployeeDetails{
    string companyName;
    int employeeID;
    string month;
    int dayNo;
    int wagePerHour;
    int dailyWage;
}employeeDetails;
list <employeeDetails> employeeDetailsList;

typedef struct Company {
    string companyName;
    int NUM_OF_WORKING_DAYS;
    int MAX_MONTHLY_HRS ;
    int EMP_RATE_PER_HOUR;
    int empNumber;
    vector <int> monthlyWage;
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
                // cout << dailyWage;
                dailyWagesList.push_back(dailyWage);
                totalEmpHrs += empHrs;
            }
        return totalEmpHrs;
}

int company :: empWageBuilder(company companyObj){
    int totalEmpHrs = getTotalEmpHours(companyObj);
    return totalEmpHrs * companyObj.EMP_RATE_PER_HOUR;
}

void writeToFile (string fileName, int monthCount, _List_iterator<company> companyObj){
    int totalDays = (*companyObj).NUM_OF_WORKING_DAYS;
    string companyName = (*companyObj).companyName;
    int employeeNumber = (*companyObj).empNumber;
    int wagePerHour = (*companyObj).EMP_RATE_PER_HOUR;
    int dayCount;
    list <int> :: iterator dailyWage;

    fstream fileStream;
    fileStream.open(fileName, ios::out | ios::app);
    if(fileStream.is_open()){
        fileStream.seekp(0, ios::end);
        if (fileStream.tellg() == 0){
            fileStream << "Company, Employee-ID, Month, Day No., Daily Wage, Wage Per-Hour";
        }

        fileStream.seekp(0, ios::beg);
        for (int i = 0; i < employeeNumber; i++)
            for (dayCount = 0, dailyWage = dailyWagesList.begin(); dailyWage != dailyWagesList.end() ; dayCount++, dailyWage++ ){
                fileStream << "\n" << companyName << "," <<  i + 1 << "," << month[monthCount] << "," << dayCount + 1
                << "," <<  *dailyWage << "," << wagePerHour;
               
            }
        fileStream.close();
    }
}

vector<string> split(const string& line, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);
    while (std::getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

void readFromFile (string fileName){
    fstream fileStream;
  
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
                employeeDetailsList.push_back(employeeDetails);
            }
        }
    }
    fileStream.close();
}

void empTotalWage(list<company> companyList){
    list <company> :: iterator companyObj;
    list <employeeDetails> :: iterator empObj;
    int totalEmpWage = 0;
    string company;
    int totalEmployees;
    int totalDays;
    int day;
    int empCount;
    int flag = 0;
    cout << "Enter Company Name: " << endl;
    cin >> company ;

     for ( companyObj = companyList.begin(); companyObj!=companyList.end(); companyObj++){
        if ( (*companyObj).companyName == company){
            totalEmployees = (*companyObj).empNumber;
            totalDays = (*companyObj).NUM_OF_WORKING_DAYS;
             flag = 1;
             break;
        }
     }
     if (flag != 1){
         cout << "No Such Company Found" << endl;
         return ;
     }
     cout << company << totalEmployees << totalDays << endl;

    empObj = employeeDetailsList.begin();
     for (empCount = 0; empCount < totalEmployees; empCount++){ 
        cout << "\nEmployeeID-" << empCount + 1 << ": " << endl;
          cout << endl;
            for (int monthCount = 0; monthCount < monthSize; monthCount++){
                cout << "Month : " << month[monthCount] << ",";
                empObj = employeeDetailsList.begin();
                totalEmpWage = 0;
                while (empObj != employeeDetailsList.end()){
                    if((*empObj).companyName == company && ((*empObj).employeeID == (empCount + 1)) && ((*empObj).month == month[monthCount])){
                             totalEmpWage = totalEmpWage + (*empObj).dailyWage;
                             empObj++;
                        }
                        else
                        {
                             empObj++;
                        }   
                }
                cout << " Salary: " << totalEmpWage << endl;
            }   
     }
}

void companyDetailsBuilder(list<company> companyList){
    list <company> :: iterator companyObj;
    list <int> :: iterator day;
    string fileName = "employeeWageDetails.csv";
    int empHrs, empWage, totalEmpHrs, monthCount;

   for ( companyObj = companyList.begin(); companyObj!=companyList.end(); companyObj++){
        int empNumber = (*companyObj).empNumber;
        string companyName = (*companyObj).companyName;
        monthCount = 0;
        cout << endl ;
        while (monthCount < monthSize){
            for ( int i = 0; i < empNumber ; i++){
                sleep(1.5);
                empWage = (*companyObj).empWageBuilder((*companyObj));
                cout << "Company :" << companyName << ", employee ID :" << i + 1 <<", Employee Wage = " << empWage << ", Month: " << month[monthCount]<< endl;
            }

            writeToFile(fileName, monthCount, companyObj);
            dailyWagesList.clear();
            monthCount++;
        }
    }
}

int main (){
    cout << "\n\tWelcome To Employee Wage Program." << endl;
    bool status = true;
    int numberOfCompanies, companyCount = 0;
    int choice;


    list <company> companyList;
    list <company> :: iterator companyObj;

    cout << "Enter Number of companies" << endl;
            cin >> numberOfCompanies;
        while (companyCount < numberOfCompanies){
            company companyObj;
            companyList.push_back(companyObj);
            companyCount++;
            }
        companyDetailsBuilder(companyList);
        readFromFile("employeeWageDetails.csv");
        empTotalWage(companyList);
}