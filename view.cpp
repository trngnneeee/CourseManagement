#include "header.h"

void CourseMain::viewScoreBoard()
{
    StudentCourse *cur;
    cout << setfill('_') << setw(167) << "_" << setfill(' ') << "\n";

    string headers[] = {"No", "Full Name", "Total Mark", "Final Mark", "Midterm Mark", "Other Mark"};
    int widths[] = {15, 40, 25, 25, 25, 25};

    for (int i = 0; i < 6; i++) {
        int padding = (widths[i] - headers[i].length()) / 2;
        cout << "| " << setw(padding) << "" << headers[i] << setw(widths[i] - headers[i].length() - padding) << "";
    }
    cout << "|\n";

    cout << setfill('_') << setw(167) << "_" << setfill(' ') << "|\n";

    for (int i = 0; i < curStudent; i++)
    {
        cur = copyOfStudent[i]->curYear->semesterHead[semester - 1].courseHead;
        while (cur && cur->courseID != courseID)
            cur = cur->next;
        if (cur)
        {
            cout << "| " << setw(13) << left << i + 1 << " "
                 << " | " << setw(38) << left << copyOfStudent[i]->lastName + " " + copyOfStudent[i]->firstName << " "
                 << " | " << setw(23) << left << cur->studentMarkOfThisCourse.totalMark << " "
                 << " | " << setw(23) << left << cur->studentMarkOfThisCourse.finalMark << " "
                 << " | " << setw(23) << left << cur->studentMarkOfThisCourse.midtermMark << " "
                 << " | " << setw(23) << left << cur->studentMarkOfThisCourse.otherMark << " "
                 << " |\n";
        }
    }
    
    // for (int i = 0; i < 6; i++) {
    //     int padding = (widths[i] - headers[i].length()) / 2;
    //     cout << "| " << setw(padding) << "" << headers[i] << setw(widths[i] - headers[i].length() - padding) << "";
    // }
    cout << "|\n";
    cout << setfill('_') << setw(167) << "_" << setfill(' ') << "|\n";
}

void ClassLink::viewScore(int semesterNum)
{
    StudentCourse *cur = nullptr;
    double totalScore = 0;
    double overall = 0;
    int n = 0;
    for (int i = 0; i < studentNum; i++)
    {
        totalScore = 0;
        n = 0;
        cout << "|" << setw(15) << "No"
             << "|" << setw(15) << "ID"
             << "|" << setw(30) << "Full Name"
             << "|";
        cur = studentHead[i].curYear->semesterHead[semesterNum - 1].courseHead;
        while (cur)
        {
            cout << setw(30) << cur->courseName << "|";
            cur = cur->next;
        }
        cout << setw(15) << "GPA"
             << "|" << endl;
        cout << setfill('_') << setw(50) << "_" << setfill(' ') << endl;
        cout << "|" << setw(8) << i + 1 << "|" << setw(8) << studentHead[i].studentID << "|" << setw(19) << studentHead[i].lastName + " " + studentHead[i].firstName << "|";
        cur = studentHead[i].curYear->semesterHead[semesterNum - 1].courseHead;
        while (cur)
        {
            cout << setw(19) << cur->studentMarkOfThisCourse.finalMark << "|";
            totalScore += cur->studentMarkOfThisCourse.finalMark;
            n++;
            cur = cur->next;
        }

        if (n != 0)
        {
            cout << setw(9) << totalScore / n << "|" << endl;
            overall += totalScore / n;
        }
        else
        {
            cout << setw(9) << 0 << "|" << endl;
        }
        cout << setfill('_') << setw(50) << "_" << setfill(' ') << endl;
    }
    cout << "|" << setw(9) << "Overall Class GPA :"
         << "|" << setw(9) << overall / studentNum << "|" << endl;
    cout << setfill('_') << setw(50) << "_" << setfill(' ') << endl;
}

void viewAStuddentScoreBoard(StudentArray* Stu, YearLink *curYear)
{
    // tim thang co trung ID trong studentArray
    int ctr;
    int i;
    string msg = "";
    do
    {
        system("cls");
        if (msg != "")
        {
            int boxWidth = 26; 
            string border = string(boxWidth, '-');
            cout << border << endl;
            int padding = (boxWidth - msg.length() - 2) / 2; 
            cout << '|' << setw(padding) << "" << msg << setw(boxWidth - msg.length() - padding - 1) << '|' << endl;
            cout << border << endl;
        }
        msg = "";
        i = 0;

            cout << "=======================================\n";
            cout << "||                                   ||\n";
            cout << "||    Which year you want to view?   ||\n";
            cout << "||                                   ||\n";
            cout << "=======================================\n";
            cout << "||                                   ||\n";
            cout << "|| 1.  First year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 2.  Second year                   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 3.  Third year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 4.  Fourth year                   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 5.  Fifth year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 6.  Sixth year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 7. Seventh year                   ||\n";
            cout << "||                                   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 0. Exit                           ||\n";
            cout << "||                                   ||\n";
            cout << "=======================================\n";
            cout << "                    Your choice: "; cin >> ctr;
            
        i = ctr - 1;
        if (ctr > 0 && ctr <= 7)
        {
            if (Stu->firstYear + i > Stu->curYear)
            {
                msg = "No data found";
            }
            else
            {
                cout << "What semester do you want view ? (Ex: semester 1, semester 2, etc)" << endl;
                cout << "0. Exit\n";
                cout << "semester :";
                cin >> ctr;
                cout << "---------------------------------------------------\n";
                if (ctr > 0 && ctr <= Stu->firstYear[i].numSemester)
                {
                    StudentCourse *pCourse = Stu->firstYear[i].semesterHead[ctr - 1].courseHead;
                    if (!pCourse)
                    {
                        msg = "No course to shown";
                    }
                    else
                    {
                        cout << setw(15) << "Course" << setw(15) << "Total Mark" << setw(15) << "Final Mark" << setw(15) << "Midterm Mark" << setw(15) << "Other Mark" << endl;
                        while (pCourse)
                        {
                            cout << setw(15) << pCourse->courseID << setw(15) << pCourse->studentMarkOfThisCourse.totalMark << setw(15) << pCourse->studentMarkOfThisCourse.finalMark << setw(15) << pCourse->studentMarkOfThisCourse.midtermMark << setw(15) << pCourse->studentMarkOfThisCourse.otherMark << endl;
                            pCourse = pCourse->next;
                        }
                        system("pause");
                    }
                }
                else
                {
                    msg = "Invalid semester";
                }
            }
        }
        else
        {
            msg = "Invalid year";
        }
    } while (ctr > 0);
}

// view course
// void viewTheListOfCourse(CourseMain *courseHead)  
// {
//     if (!courseHead)
//     {
//         cout << "+-------------------------------------------------+\n";
//         cout << "|            There is no course to show           |\n";
//         cout << "+-------------------------------------------------+\n";
//         return;
//     }
//     cout << setfill('=') << setw(164) << "=" << endl;
//     cout << setfill(' ') << left << "|| " << setw(12) << "No."
//          << " || " << setw(25) << "Name"
//          << " || " << setw(18) << "Class"
//          << " || " << setw(25) << "Teacher Name"
//          << " || " << setw(15) << "Day"
//          << " || " << setw(15) << "Session"
//          << " || " << setw(8) << "Credits"
//          << " || " << setw(12) << "Max Student"
//          << " ||" << endl;
//     cout << setfill('-') << setw(164) << "-" << endl;
//     cout << setfill(' ');

//     CourseMain *tmp = courseHead;
//     while (tmp != NULL)
//     {
//         cout << left << "|| " << setw(12) << tmp->courseID
//              << " || " << setw(25) << tmp->courseName
//              << " || " << setw(18) << tmp->className
//              << " || " << setw(25) << tmp->teacherName
//              << " || " << setw(15) << tmp->day
//              << " || " << setw(15) << tmp->session
//              << " || " << setw(8) << tmp->numberOfCredits
//              << " || " << setw(12) << tmp->maxStudent
//              << " ||" << endl;
//         tmp = tmp->next;
//     }
//     cout << setfill('=') << setw(164) << "=" << endl;
// }

// void viewTheListOfClass(YearLink* year){
//     if (!year->classHead)
//     {
//         cout << "+-------------------------------------------------+\n";
//         cout << "|            There is no class to show            |\n";
//         cout << "+-------------------------------------------------+\n";
//         return;
//     }
//     cout << setfill('=') << setw(164) << "=" << endl;
//     cout << setfill(' ') << left << "|| " << setw(12) << "No."
//          << " || " << setw(25) << "Name"
//          << " || " << setw(18) << "Teacher Name"
//          << " || " << setw(15) << "Max Student"
//          << " ||" << endl;
//     cout << setfill('-') << setw(164) << "-" << endl;
//     cout << setfill(' ');

//     ClassLink *tmp = year->classHead;
//     while (tmp != NULL)
//     {
//         cout << left << "|| " << setw(12) << tmp->classID
//              << " || " << setw(25) << tmp->className
//              << " || " << setw(18) << tmp->teacherName
//              << " || " << setw(15) << tmp->maxStudent
//              << " ||" << endl;
//         tmp = tmp->next;
//     }
//     cout << setfill('=') << setw(164) << "=" << endl;
// }

// void viewTheListOfStudentInClass(YearLink* year){

// }

// void viewTheListOfStudentInCourse(CourseMain* courseHead){
    
// }



void viewAStuddentCourseList(StudentArray* Stu, YearLink *curYear)
{
    int ctr;
    int i;
    string msg = "";
    do
    {
        system("cls");
        if (msg != "")
        {
            int boxWidth = 26; 
            string border = string(boxWidth, '-');
            cout << border << endl;
            int padding = (boxWidth - msg.length() - 2) / 2; 
            cout << '|' << setw(padding) << "" << msg << setw(boxWidth - msg.length() - padding - 1) << '|' << endl;
            cout << border << endl;
        }
        msg = "";
        i = 0;

            cout << "=======================================\n";
            cout << "||                                   ||\n";
            cout << "||    Which year you want to view?   ||\n";
            cout << "||                                   ||\n";
            cout << "=======================================\n";
            cout << "||                                   ||\n";
            cout << "|| 1.  First year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 2.  Second year                   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 3.  Third year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 4.  Fourth year                   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 5.  Fifth year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 6.  Sixth year                    ||\n";
            cout << "||                                   ||\n";
            cout << "|| 7. Seventh year                   ||\n";
            cout << "||                                   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 0. Exit                           ||\n";
            cout << "||                                   ||\n";
            cout << "=======================================\n";
            cout << "                    Your choice: "; cin >> ctr;
            
        i = ctr - 1;
        if (ctr > 0 && ctr <= 7)
        {
            if (Stu->firstYear + i > Stu->curYear)
            {
                msg = "No data found";
            }
            else
            {
                cout << "What semester do you want view ? (Ex: semester 1, semester 2, etc)" << endl;
                cout << "0. Exit\n";
                cout << "semester :";
                cin >> ctr;
                cout << "---------------------------------------------------\n";
                if (ctr > 0 && ctr <= Stu->firstYear[i].numSemester)
                {
                    StudentCourse *pCourse = Stu->firstYear[i].semesterHead[ctr - 1].courseHead;
                    if (!pCourse)
                    {
                        msg = "No course to shown";
                    }
                    else
                    {
                        cout << "Course ID" << setw(20) << "Course Name" << setw(20) << "Teacher" << setw(50) << "Day" << setw(50) << "Session" << endl;
                        for (int b=0; b<140; b++) cout << "_";
                        cout << endl;
                        while (pCourse)
                        {
                            CourseMain* tmpCourseMain = curYear->semesterHead[ctr - 1].courseHead;
                            while (tmpCourseMain && tmpCourseMain->courseID != pCourse->courseID){
                                tmpCourseMain = tmpCourseMain -> next;
                            }
                            if (!tmpCourseMain){
                                cout << "Cant find this course in CoureMain" << endl;
                                break;
                            }
                            cout << tmpCourseMain->courseID << setw(20) << tmpCourseMain->courseName << setw(20) << tmpCourseMain->teacherName << setw(50) << tmpCourseMain->day << setw(50) << tmpCourseMain->session << endl;
                            pCourse = pCourse->next;
                        }
                        system("pause");
                    }
                }
                else
                {
                    msg = "Invalid semester";
                }
            }
        }
        else
        {
            msg = "Invalid year";
        }
    } while (ctr > 0);
}

void viewTheListOfCourse(CourseMain *courseHead)
{
    if (!courseHead)
    {
        cout << "+-------------------------------------------------+\n";
        cout << "|            There is no course to show           |\n";
        cout << "+-------------------------------------------------+\n";
        return;
    }
    cout << setfill('=') << setw(164) << "=" << endl;
    cout << setfill(' ') << left << "|| " << setw(12) << "No."
         << " || " << setw(25) << "Name"
         << " || " << setw(18) << "Class"
         << " || " << setw(25) << "Teacher Name"
         << " || " << setw(15) << "Day"
         << " || " << setw(15) << "Session"
         << " || " << setw(8) << "Credits"
         << " || " << setw(12) << "Max Student"
         << " ||" << endl;
    cout << setfill('-') << setw(164) << "-" << endl;
    cout << setfill(' ');

    CourseMain *tmp = courseHead;
    while (tmp != NULL)
    {
        cout << left << "|| " << setw(12) << tmp->courseID
             << " || " << setw(25) << tmp->courseName
             << " || " << setw(18) << tmp->className
             << " || " << setw(25) << tmp->teacherName
             << " || " << setw(15) << tmp->day
             << " || " << setw(15) << tmp->session
             << " || " << setw(8) << tmp->numberOfCredits
             << " || " << setw(12) << tmp->maxStudent
             << " ||" << endl;
        tmp = tmp->next;
    }
    cout << setfill('=') << setw(164) << "=" << endl;
}

void viewTheListOfClass(YearLink *year)
{
    if (!year->classHead)
    {
        cout << "+-------------------------------------------------+\n";
        cout << "|            There is no class to show            |\n";
        cout << "+-------------------------------------------------+\n";
        delete year;
        return;
    }

    ClassLink *tmp = year->classHead;
    cout << setfill('-') << setw(38) << "-" << endl;
    cout << "||           * Class Name *           ||\n";
    cout << setfill('-') << setw(38) << "-" << endl;

    int i = 0;
    while (tmp != NULL)
    {
        cout << "|| " << ++i << ". " << tmp->className << setfill(' ') << setw(25) << "||" << endl;
        cout << "|| " << setfill(' ') << setw(35) << "||" << endl;
        tmp = tmp->next;
    }
    cout << setfill('-') << setw(38) << "-" << endl;
}

// In main function, ask user to choose the class to view
void viewTheListOfStudentInClass(ClassLink *classHead)
{
    if (!classHead)
    {
        cout << "+-------------------------------------------------+\n";
        cout << "|            There is no student to show          |\n";
        cout << "+-------------------------------------------------+\n";
        return;
    }
    cout << setfill('-') << setw(117) << "-" << endl;
    string title = "* Student In * " + classHead->className;
    int padding = (117 - title.length()) / 2;
    cout << setfill(' ') << setw(padding) << " " << title << setfill(' ') << setw(padding) << " " << endl;
    cout << setfill('-') << setw(117) << "-" << endl;
    cout << setfill(' ') << left << "|| " << setw(12) << "No."
         << " || " << setw(35) << "Name"
         << " || " << setw(18) << "Gender"
         << " || " << setw(15) << "Date of Birth"
         << " || " << setw(15) << "Social ID"
         << " ||" << endl;
    cout << setfill('-') << setw(117) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < classHead->studentNum; i++)
    {
        cout << left << "|| " << setw(12) << classHead->studentHead[i].studentID
             << " || " << setw(35) << classHead->studentHead[i].lastName + " " + classHead->studentHead[i].firstName
             << " || " << setw(18) << classHead->studentHead[i].gender
             << " || " << setw(15) << classHead->studentHead[i].dateOfBirth
             << " || " << setw(15) << classHead->studentHead[i].socialID
             << " ||" << endl;
    }
    cout << setfill('=') << setw(117) << "=" << endl;
}

// In main function, ask user to choose the course to view
void viewTheListOfStudentInCourse(CourseMain *courseHead)
{
    if (!courseHead)
    {
        cout << "+-------------------------------------------------+\n";
        cout << "|            There is no student to show          |\n";
        cout << "+-------------------------------------------------+\n";
        return;
    }
    cout << setfill('-') << setw(139) << "-" << endl;
    string title = "* Student In * " + courseHead->courseName;
    int padding = (139 - title.length()) / 2;
    cout << setfill(' ') << setw(padding) << " " << title << setfill(' ') << setw(padding) << " " << endl;
    cout << setfill('-') << setw(139) << "-" << endl;
    cout << setfill(' ') << left << "|| " << setw(12) << "No."
         << " || " << setw(35) << "Name"
         << " || " << setw(18) << "Class"
         << " || " << setw(18) << "Gender"
         << " || " << setw(15) << "Date of Birth"
         << " || " << setw(15) << "Social ID"
         << " ||" << endl;
    cout << setfill('-') << setw(139) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < courseHead->curStudent; i++)
    {
        cout << left << "|| " << setw(12) << courseHead-> copyOfStudent[i]->studentID
             << " || " << setw(35) << courseHead->copyOfStudent[i]->lastName + " " + courseHead->copyOfStudent[i]->firstName
             << " || " << setw(18) << courseHead->className
             << " || " << setw(18) << courseHead->copyOfStudent[i]->gender
             << " || " << setw(15) << courseHead->copyOfStudent[i]->dateOfBirth
             << " || " << setw(15) << courseHead->copyOfStudent[i]->socialID
             << " ||" << endl;
    }
    cout << setfill('=') << setw(139) << "=" << endl;
}