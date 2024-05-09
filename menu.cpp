#include "header.h"

void teacherMenu(YearLink *&school, YearLink *&tailSchool)
{
    int ctr;
    do
    {
        system("cls");
        cout << "1. Create a new school year.\n";         // 1 - 12 (missing 10, 3 ???, 5???, 8_Folder (Decoration), 9_aLittleBitOfBug, )
        cout << "2. Impork mark for the current year.\n"; // Import couse into folder (like 8)
        cout << "3. View data for current year.\n";
        if (school)
            cout << "4. Course management \n"; // moi them 28/4
        cout << "0. Exit.\n";
        cout << "Your choice: ";
        cin >> ctr;
        switch (ctr)
        {
        case 1:
        {
            createNewYear(school, tailSchool);
            int numClass;
            cout << "How many class do you want to add? ";
            cin >> numClass;
            cin.ignore();
            for (int i = 0; i < numClass; i++)
            {
                system("cls");
                cout << "Class No." << i + 1 << ": " << endl;
                addAClass(tailSchool);
            }
            inputSemester(tailSchool);
            break;
        }
        case 2:
        {
            if (school == NULL)
            {
                cout << "No year information for importing!\n";
                break;
            }
            else
            {
                for (int i = 0; i < tailSchool->numSemester; i++)
                    markManagementMenu(tailSchool, i + 1);
                break;
            }
        }
        case 3:
        {
            teacherView(tailSchool);
            break;
        }
        case 4:
        {
            if (!school)
            {
                cout << "Invalid choice\n";
                break;
            }
            courseManagementMenu(tailSchool);
            break;
        }
        case 0:
        {
            cout << "Exit!\n";
            break;
        }
        default:
        {
            cout << "Invalid choice\n";
            break;
        }
            system("pause");
        }
    } while (ctr != 0);
}

void studentMenu(YearLink *&school, string studentID)
{
    string tmp = studentID.substr(0, 2);
    StudentArray *user;
    bool flag = 0;
    YearLink *tmpSchool = school;
    while (tmpSchool)
    {
        if (tmpSchool->yearID == tmp)
        {
            ClassLink *tmpClass = tmpSchool->classHead;
            while (tmpClass)
            {
                for (int i = 0; i < tmpClass->studentNum; i++)
                {
                    if (tmpClass->studentHead[i].studentID == studentID)
                    {
                        user = &(tmpClass->studentHead[i]);
                        flag = 1;
                        break;
                    }
                }

                if (flag == 1)
                    break;
                tmpClass = tmpClass->next;
            }
        }
        if (flag == 1)
            break;
        tmpSchool = tmpSchool->next;
    }
    if (!flag)
    {
        cout << "No data found" << endl;
        return;
    }
    int ctr;
    do
    {
        system("cls");
        cout << "1. View a list of your courses.\n";
        cout << "2. View your scoreboard.\n";
        cout << "0. Exit.\n";
        cout << "Your choice: ";
        cin >> ctr;
        cin.ignore();
        switch (ctr)
        {
        case 1:
        {
            viewAStuddentCourseList(user, school);
            system("pause");
            break;
        }
        case 2:
        {
            viewAStuddentScoreBoard(user, school);
            system("pause");
            break;
        }
        case 0:
        {
            cout << "Exit!\n";
            system("pause");
            break;
        }
        }
    } while (ctr != 0);
}

void teacherView(YearLink *curYear)
{
    int ctr;
    do
    {
        system("cls");
        cout << "<    VIEW DATA IN YEAR " << curYear->start << " - " << curYear->end << "     >" << endl;
        cout << "1. View a list of classes\n";
        cout << "2. View a list of students in a class\n";
        cout << "3. View a list of courses\n";
        cout << "4. View a list of students in a course\n";
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ctr;
        cin.ignore();
        if (ctr == 1)
        {
            viewTheListOfClass(curYear);
        }
        else if (ctr == 2)
        {
            string tmpClassName;
            cout << "Enter class name: ";
            getline(cin, tmpClassName);
            ClassLink *tmpClass = curYear->classHead;
            while (tmpClass && tmpClass->className != tmpClassName)
            {
                tmpClass = tmpClass->next;
            }
            viewTheListOfStudentInClass(tmpClass);
        }
        else if (ctr == 3)
        {
            CourseMain *tmpCourse;
            for (int i = 0; i < curYear->numSemester; i++)
            {
                ////////////////////////////////////////////////
                tmpCourse = curYear->semesterHead[i].courseHead;
                viewTheListOfCourse(tmpCourse);
                cout << endl;
            }
        }
        else if (ctr == 4)
        {
            bool isEnd = false;
            string tmpCourseName;
            cout << "Enter your course ID: ";
            getline(cin, tmpCourseName);
            SemesterMain *tmpSem;
            CourseMain *tmpCourse;
            tmpSem = curYear->semesterHead;
            for (int i = 0; i < curYear->numSemester; i++)
            {
                tmpCourse = tmpSem[i].courseHead;
                while (tmpCourse)
                {
                    if (tmpCourse->courseID == tmpCourseName)
                    {
                        viewTheListOfStudentInCourse(tmpCourse);
                        isEnd = true;
                        break;
                    }
                    tmpCourse = tmpCourse->next;
                }
                if (isEnd)
                    break;
            }

            if (!isEnd)
            {
                cout << "+-------------------------------------------------+\n";
                cout << "|            There is no student to show          |\n";
                cout << "+-------------------------------------------------+\n";
            }
        }
        else
        {
            cout << "EXIT" << endl;
        }
        system("pause");
    } while (ctr > 0);
}

void courseManagementMenu(YearLink *year)
{
    int ctr;
    do
    {
        system("cls");
        cout << "=======================================\n";
        cout << "||         Course Management         ||\n";
        cout << "=======================================\n";
        cout << "||                                   ||\n";
        cout << "|| 1.  Delete a course.              ||\n";
        cout << "||                                   ||\n";
        cout << "|| 2.  Remove student from course.   ||\n";
        cout << "||                                   ||\n";
        cout << "|| 3.  Add student to course.        ||\n";
        cout << "||                                   ||\n";
        cout << "|| 4.  Update course information.    ||\n";
        cout << "||                                   ||\n";
        cout << "||                                   ||\n";
        cout << "|| 0.  Exit.                         ||\n";
        cout << "||                                   ||\n";
        cout << "=======================================\n";
        cout << "                    Your choice: ";
        cin >> ctr;
        cin.ignore();
        switch (ctr)
        {
            case 1:
            {    
                int sem = 0;
                cout << "Your course is in what semester? ";
                cin >> sem;
                cin.ignore();
                if (sem <= 0 || sem > year->numSemester){
                    cout << "Invalid semester" << endl;
                    system("pause");
                    break;
                }
                cout << endl;
                string courseID;
                bool flag = false;
                cout << "Enter the course ID : ";
                getline(cin, courseID);
                deleteCourse(year->semesterHead[sem-1].courseHead, courseID);
                break;
            }
            case 2:
            {
                int sem = 0;
                cout << "Your course is in what semester? ";
                cin >> sem;
                cin.ignore();
                if (sem <= 0 || sem > year->numSemester){
                    cout << "Invalid semester" << endl;
                    system("pause");
                    break;
                }
                removeStudentFromCourse(year->semesterHead[sem-1].courseHead);
                break;
            }
            case 3: 
            {
                int sem = 0;
                cout << "Your course is in what semester? ";
                cin >> sem;
                cin.ignore();
                if (sem <= 0 || sem > year->numSemester){
                    cout << "Invalid semester" << endl;
                    system("pause");
                    break;
                }
                addStudentToCourse(year->semesterHead[sem-1].courseHead, year);
                break;
            }
            case 4:
            {   
                int sem = 0;
                cout << "Your course is in what semester? ";
                cin >> sem;
                cin.ignore();
                if (sem <= 0 || sem > year->numSemester){
                    cout << "Invalid semester" << endl;
                    system("pause");
                    break;
                }
                changeIn4OfCourse(year->semesterHead[sem-1].courseHead);
                break;
            }
            default:
            {
                cout << "Exit" << endl;
                break;
            }
                
        }
    } while (ctr > 0);
}