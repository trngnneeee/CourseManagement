// #pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

//#include <filesystem>

using namespace std;


struct Mark;
struct StudentArray;
struct CourseMain;
struct StudentCourse;
struct StudentSemester;
struct StudentYear;
struct ClassLink;
struct SemesterMain;
struct YearLink;

struct Mark
{
    double totalMark, finalMark, midtermMark, otherMark;
    Mark(){
        totalMark = finalMark = midtermMark = otherMark = -1;
    }
};


struct StudentArray
{
    // int No;
    string studentID, firstName, lastName, gender, dateOfBirth, socialID;
    StudentYear* firstYear;
    StudentYear* curYear;
    StudentArray(){
        firstYear = curYear = nullptr;
    }
};


struct CourseMain
{   
    string courseID, courseName, className, teacherName, day, session;
    int semester; // quy them: de biet dang o trong hoc ki nao
    int numberOfCredits;
    int curStudent;
    int maxStudent;
    CourseMain* next;
    StudentArray** copyOfStudent;
    CourseMain(){
        next = nullptr;
        copyOfStudent = nullptr;
        curStudent = maxStudent = 0;
    }
    
    void exportList(string filename);
    void importMark(string filename);
    void viewScoreBoard ();
};


struct StudentCourse
{
    // CourseMain* course;
    string courseID; // quy them
    string courseName;
    Mark studentMarkOfThisCourse;
    StudentCourse *next; // quy them
    StudentCourse (){
        next = nullptr;
    }
};


struct StudentSemester
{
    int start, end;   
    StudentCourse* courseHead;
    StudentCourse* courseTail; //quy them
    StudentSemester(){
        courseHead = courseTail = nullptr;
    }
};


struct StudentYear
{   
    string yearID;
    StudentSemester* semesterHead;
    int numSemester;
    bool isStudied; // để biết là đã tới năm đó chưa
    StudentYear(){
        semesterHead = nullptr;
        isStudied = false;
    }
};


   
struct ClassLink
{   
    string className;
    StudentArray* studentHead;
    int studentNum;
    int capacity;
    ClassLink* next;
    ClassLink (){
        studentNum = capacity = 0;
        next = nullptr;
        studentHead = nullptr;
    }
    void viewScore(int semesterNum); // viewScore cua lop trong hoc ki N
};

struct SemesterMain
{   
    string start, end;
    CourseMain* courseHead;
    CourseMain* courseTail;
    SemesterMain(){
        courseHead = courseTail = nullptr;
    }
};


struct YearLink
{
    int start, end;
    string yearID; // quy them: vi du ID : 23 la khoa 2023, ID : 24 la khoa 2024
    ClassLink* classHead;
    ClassLink* classTail;
    SemesterMain* semesterHead;
    int numSemester;
    YearLink* next;
    YearLink(){
        next = nullptr;
        numSemester = 3;
        classHead = classTail = nullptr;
        semesterHead = nullptr;
    }
    

};

int countStudentNum(string filename);

// view
void viewAStuddentScoreBoard (StudentArray* Stu, YearLink* School); // School la bien con tro chua tat ca 
void viewAStuddentCourseList(StudentArray* Stu, YearLink *curYear);
void viewTheListOfClass(YearLink* year);
void viewTheListOfStudentInClass(ClassLink* classHead);
void viewTheListOfStudentInCourse(CourseMain* courseHead);
void teacherView(YearLink *curYear);
// phan cua nguyen : quy lam
void createNewYear (YearLink* &schoolhead, YearLink* &schoolTail);
void addAClass(YearLink* &currYear);
// void addAStudentToClass(YearLink* school);
//Semsester and course 
void linkCopyToMainStudent(string filename, CourseMain &course, YearLink* &currYear);
//void importFile(string filename, StudentArray student[], int maxStudent);
void inputCourse(CourseMain*&, string &filename);
void viewTheListOfCourse(CourseMain* courseHead);
void deleteCourse(CourseMain* &courseHead, string courseID);
void removeStudentFromCourse(CourseMain* &courseHead);
void changeIn4OfCourse(CourseMain *&courseHead);
void inputSemester(YearLink* &schoolTail);
void addStudentToCourse(CourseMain* &coursehead, YearLink* &schoolTail);
void markManagementMenu(YearLink* year, int semesterNum);

//deallocate
void deallocateStudentArray(StudentArray* &studentHead);
void deallocateCourseMain(CourseMain* &courseHead);
void deallocateStudentCourse(StudentCourse* &courseHead);
void deallocateStudentSemester(StudentSemester* &semesterHead);
void deallocateStudentYear(StudentYear* &yearHead);
void deallocateClassLink(ClassLink* &classHead);
void deallocateSemesterMain(SemesterMain* &semesterHead);
void deallocateYearLink(YearLink* &yearHead);

//database export
void databaseExport(YearLink* schoolHead, YearLink* schoolTail);
void classExport(YearLink* schoolHead);
void semesterExport (YearLink* year);

//databbase import
bool isFileEmpty(string& filename);
int countElementInFile(string fileName);
void inputYear(YearLink* &yearHead, YearLink* &yearTail, string HCMUS_database);
// Class Import
void inputClass(ClassLink* &classHead, ClassLink* &classTail, string class_list);
void inputStudentArray(StudentArray* &studentHead, string className_list_csv, int numStu);
void inputCurYear(StudentYear* &firstYear, StudentYear* &curYear, string studentID_year_list_csv);
void inputStudentSemester(StudentSemester* &semesterHead, int numSemester, string studentID_year_csv);
void inputStudentCourse(StudentCourse* &courseHead, StudentCourse* &courseTail, string studentID_Sem_course_csv);
void inputMark(Mark &studentMark, string studentID_courseID_mark_csv);
// SemesterMain Import
void inputSemesterMain(SemesterMain* &semesterHead, string semester_list, YearLink* newYear);
void inputCourseMain(CourseMain* &courseHead, CourseMain* &courseTail, string course_list, YearLink* newYear);
void linkCopyToLink (StudentArray** &copyOfStuArr, int maxStu, string studentCopyData_file, YearLink* newYear);

// Menu
void teacherMenu(YearLink* &school, YearLink* &tailSchool);
void studentMenu(YearLink* &school, string studentID);
void courseManagementMenu(YearLink *year);

// Login
// login system by duc manh
void printTopBar();
void clearScreen();

struct Account
{
    std::string AccountID;
    std::string Password;
    std::string Username;
};

struct loggedAccount
{
    int type;
    std::string accountid;
    std::string username;
};

Account parseIndex(const std::string &line);
void fillList(std::ifstream &file, Account *&LIST, const int &LIMIT, int &NUMS);
void replaceList(Account *&oldList, Account *newList, int size);
void updatePassword(const int &logged_as, const std::string AccountID, const std::string newPassword);
bool login(Account *&LIST, int &NUMS, const int LIMIT, loggedAccount *&LoggedAccount);
bool ResetPassword(const int &logged_as, const int &Order, Account *&LIST);
bool ChangePassword(const int &logged_as, const std::string &logged_account, Account *&LIST, const int &NUMS);
bool ChangePassword2(const int &logged_as, const int Order, Account *&LIST, const int &NUMS, const std::string &cur_password);
bool PasswordCheck(const int logged_as, const int Order, Account *&LIST);
bool Authenticate(Account *&LIST, int &NUMS, const int LIMIT, int &logged_as, std::string &logged_account, std::string &logged_user, bool &exit);
void createNewAccountForStudent (string studentID, string fullName);