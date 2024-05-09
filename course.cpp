#include "header.h"

////////////////// khoa /////////////
void linkCopyToMainStudent(string filename, CourseMain &course, YearLink *&currYear)
{

    // course.copyOfStudent = new StudentArray* [course.maxStudent];
    ifstream input(filename);
    ClassLink *curr = nullptr;
    StudentSemester *tmpSem;
    curr = currYear->classHead;
    if (!input.is_open())
    {
        cout << "File does not exist";
        return;
    }
    string s;
    getline(input, s);
    int i = 0;
    while (!input.eof() && i < course.curStudent)
    {
        input.ignore(100, ',');
        getline(input, s, ',');
        curr = currYear->classHead;
        while (curr)
        {
            for (int t = 0; t < curr->studentNum; t++)
            {
                if (curr->studentHead[t].studentID == s)
                {
                    course.copyOfStudent[i] = &curr->studentHead[t];
                    tmpSem = curr->studentHead[t].curYear->semesterHead;
                    tmpSem += course.semester - 1;
                    if (!tmpSem->courseHead)
                    {
                        tmpSem->courseHead = new StudentCourse;
                        tmpSem->courseTail = tmpSem->courseHead;
                    }
                    else
                    {
                        tmpSem->courseTail->next = new StudentCourse;
                        tmpSem->courseTail = tmpSem->courseTail->next;
                    }
                    tmpSem->courseTail->next = nullptr;
                    tmpSem->courseTail->courseID = course.courseID;
                    tmpSem->courseTail->courseName = course.courseName;
                }
            }
            curr = curr->next;
        }
        input.ignore(200, '\n');
        ++i;
    }

    input.close();
}

void inputCourse(CourseMain *&newCourse, string &filename)
{
    system("cls");
    const int line_width = 85;
    const int column_width = 25;
    cout << setfill('=') << setw(line_width) << "" << setfill(' ') << "\n";
    cout << setw((line_width + 13) / 2) << "Course Input" << setw((line_width - 13) / 2 - 2)
         << "\n";
    cout << setfill('=') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << left << setw(column_width) << "Enter course ID: ";
    getline(cin, newCourse->courseID);
    cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << left << setw(column_width) << "Enter course name: ";
    getline(cin, newCourse->courseName);
    cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << left << setw(column_width) << "Enter class name: ";
    getline(cin, newCourse->className);
    cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << left << setw(column_width) << "Enter teacher name: ";
    getline(cin, newCourse->teacherName);
    cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << "Choose days in the week from the following options:\n";
    string dayOptions[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++)
    {
        cout << i + 1 << ". " << dayOptions[i] << "\n";
    }
    string days;
    int day;

    cout << "Day (enter the number): "; 
    do{
        cin >> day;
        cin.ignore();
        if (day < 1 || day > 7)
        {
            cout << "Invalid day. Please choose a valid day:\n";
        }
        else
        {
            days = dayOptions[day - 1];
            break;
        }
    } while (true);


    newCourse->day = days;
    cout << "Days chosen: " << days << "\n";
    cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << "Choose sessions and times from the following options:\n";
    string sessionOptions[] = {"S1 (07:30)", "S2 (09:30)", "S3 (13:30)", "S4 (15:30)"};
    for (int i = 0; i < 4; i++)
    {
        cout << i + 1 << ". " << sessionOptions[i] << "\n";
    }
    string sessions;
    int session;

    cout << "Session (enter the number): ";
    do
    {
        cin >> session;
        cin.ignore();
        if (session < 0 || session > 4)
        {
            cout << "Invalid session. Please choose a valid session:\n";
        }
        else
        {
            sessions = sessionOptions[session - 1];
            break;
        }
    } while (true);

    newCourse->session = sessions;
    cout << "Session chosen: " << sessions << "\n";
    cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

    cout << left << setw(column_width) << "Enter number of credits: ";
    cin >> newCourse->numberOfCredits;
    cin.ignore();
    cout << setfill('=') << setw(line_width) << "" << setfill(' ') << "\n";
    cout << endl;

    char tmpCh;
    filename = newCourse->courseID + ".csv";
    filename = "./importCourse/" + filename;
    cout << setfill(' ') << setw(70) << right << "You will import this course in " << filename << "? (Y/N): ";
    cin >> tmpCh;
    cin.ignore();
    while (tmpCh != 'y' && tmpCh != 'Y' && tmpCh != 'n' && tmpCh != 'N')
    {
        cout << "\n"
             << setw(85) << "❌Invalid. Input Y/N only: ";
        cin >> tmpCh;
        cin.ignore();
    }
    if (tmpCh == 'n' || tmpCh == 'N')
    {
        cout << "\n"
             << setfill(' ') << setw(85) << right << "Enter your import file (no need to add .csv): ";
        getline(cin, filename);
        filename = filename + ".csv";
    }

    int courseStuNum = countStudentNum(filename);
    newCourse->curStudent = courseStuNum;
    cout << "\n"
         << setfill(' ') << setw(58) << right << "Max student is " << courseStuNum << ". Is this correct? (Y/N): ";
    string choice;
    getline(cin, choice);
    if (choice == "Y" || choice == "y")
    {
        newCourse->maxStudent = courseStuNum;
    }
    else
    {
        cout << "\n"
             << setw(85) << "Enter max student: ";
        cin >> newCourse->maxStudent;
    }

    newCourse->copyOfStudent = new StudentArray *[newCourse->maxStudent];
}

// Delete 1 course
void deleteCourse(CourseMain *&courseHead, string courseID)
{
    CourseMain *tmp = courseHead;
    if (!tmp)
    {
        cout << setw(40) << "+--------------------------------------------------------------+\n";
        cout << setw(40) << "|                     Course list is empty.                    |\n";
        cout << setw(40) << "+--------------------------------------------------------------+\n";
        system("pause");
        return;
    }
    if (tmp->courseID == courseID)
    {
        courseHead = courseHead->next;
        delete[] tmp->copyOfStudent;
        delete tmp;
        return;
    }

    while (tmp->next != NULL)
    {
        if (tmp->next->courseID == courseID)
        {
            CourseMain *del = tmp->next;
            tmp->next = del->next;
            delete[] del->copyOfStudent;
            delete del;
            cout << setw(40) << "+--------------------------------------------------------------+\n";
            cout << setw(40) << "|                  Course " << setw(30) << left << courseID << " has been deleted.               |\n";
            cout << setw(40) << "+--------------------------------------------------------------+\n";
            system("pause");
            return;
        }
        tmp = tmp->next;
    }
    cout << setw(40) << "+--------------------------------------------------------------+\n";
    cout << setw(40) << "|                       Course not found.                      |\n";
    cout << setw(40) << "+--------------------------------------------------------------+\n";
    system("pause");
}

void addStudentToCourse(CourseMain *&coursehead, YearLink *&schoolTail)
{
    string courseID;
    cout << "| Enter the course ID: ";
    getline(cin, courseID);
    CourseMain *tmp = coursehead;
    while (tmp)
    {
        if (tmp->courseID == courseID)
        {
            cout << "| Enter the student ID to add: ";
            string studentID;
            getline(cin, studentID);

            if (tmp->curStudent == tmp->maxStudent)
            {
                cout << setw(40) << "+--------------------------------------------------------------+\n";
                cout << setw(40) << "|                      Course is full.                         |\n";
                cout << setw(40) << "+--------------------------------------------------------------+\n";
                system("pause");
                return;
            }

            for (int i = 0; i < tmp->curStudent; i++)
            {
                if (tmp->copyOfStudent[i]->studentID == studentID)
                {
                    cout << setw(40) << "+--------------------------------------------------------------+\n";
                    cout << setw(40) << "|                  Student already in the course.              |\n";
                    cout << setw(40) << "+--------------------------------------------------------------+\n";
                    system("pause");
                    return;
                }
            }

            ClassLink *tmpClass = schoolTail->classHead;
            while (tmpClass)
            {
                for (int i = 0; i < tmpClass->studentNum; i++)
                {
                    if (tmpClass->studentHead[i].studentID == studentID)
                    {
                        tmp->copyOfStudent[tmp->curStudent] = &tmpClass->studentHead[i];
                        tmp->curStudent++;
                        cout << setw(40) << "+--------------------------------------------------------------+\n";
                        cout << setw(40) << "|                  Student added successfully.                |\n";
                        cout << setw(40) << "+--------------------------------------------------------------+\n";
                        system("pause");
                        return;
                    }
                }
                tmpClass = tmpClass->next;
            }
            if (!tmpClass)
            {
                cout << setw(40) << "+--------------------------------------------------------------+\n";
                cout << setw(40) << "|                          Student not found.                  |\n";
                cout << setw(40) << "+--------------------------------------------------------------+\n";
                system("pause");
                return;
            }
        }
        tmp = tmp->next;
    }
    if (!tmp)
    {
        cout << setw(40) << "+--------------------------------------------------------------+\n";
        cout << setw(40) << "|                          Course not found.                   |\n";
        cout << setw(40) << "+--------------------------------------------------------------+\n";
    }
    system("pause");
}

void removeStudentFromCourse(CourseMain *&courseHead)
{
    string courseID;
    cout << endl;
    cout << "| Enter the course ID: ";
    getline(cin, courseID);
    CourseMain *tmp = courseHead;
    while (tmp)
    {
        if (tmp->courseID == courseID)
        {
            cout << "| Enter the student ID to remove: ";
            string studentID;
            getline(cin, studentID);
            for (int i = 0; i < tmp->curStudent; i++)
            {
                if (tmp->copyOfStudent[i]->studentID == studentID)
                {
                    for (int j = i; j < tmp->curStudent - 1; j++)
                    {
                        tmp->copyOfStudent[j] = tmp->copyOfStudent[j + 1];
                    }
                    tmp->curStudent--;
                    cout << setw(40) << "+--------------------------------------------------------------+\n";
                    cout << setw(40) << "|                  Student removed successfully.               |\n";
                    cout << setw(40) << "+--------------------------------------------------------------+\n";
                    system("pause");
                    return;
                }
            }
            cout << setw(40) << "+--------------------------------------------------------------+\n";
            cout << setw(40) << "|                          Student not found.                  |\n";
            cout << setw(40) << "+--------------------------------------------------------------+\n";
            system("pause");
            return;
        }
        tmp = tmp->next;
    }
    if (!tmp)
    {
        cout << setw(40) << "+--------------------------------------------------------------+\n";
        cout << setw(40) << "|                          Course not found.                   |\n";
        cout << setw(40) << "+--------------------------------------------------------------+\n";
    }
    system("pause");
}

void changeIn4OfCourse(CourseMain *&courseHead)
{
    system("cls");
    string courseID;
    cout << "| Enter the course ID: ";
    getline(cin, courseID);
    CourseMain *tmp = courseHead;
    while (tmp)
    {
        if (tmp->courseID == courseID)
        {
            const int line_width = 85;
            const int column_width = 25;
            cout << setfill('=') << setw(line_width) << "" << setfill(' ') << "\n";
            cout << setw((line_width + 13) / 2) << "Course Input" << setw((line_width - 13) / 2 - 2)
                 << "\n";
            cout << setfill('=') << setw(line_width) << "" << setfill(' ') << "\n";

            cout << left << setw(column_width) << "Enter course name: ";
            getline(cin, tmp->courseName);
            cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

            cout << left << setw(column_width) << "Enter class name: ";
            getline(cin, tmp->className);
            cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

            cout << left << setw(column_width) << "Enter teacher name: ";
            getline(cin, tmp->teacherName);
            cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

            cout << "Choose days in the week from the following options:\n";
            string dayOptions[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            for (int i = 0; i < 7; i++)
            {
                cout << i + 1 << ". " << dayOptions[i] << "\n";
            }
            string days;
            int day;

            cout << "Day (enter the number): ";
            do
            {
                cin >> day;
                cin.ignore();
                if (day < 1 || day > 7)
                {
                    cout << "Invalid day. Please choose a valid day:\n";
                }
                else
                {
                    days = dayOptions[day - 1];
                    break;
                }
            } while (true);

            tmp->day = days;
            cout << "Days chosen: " << days << "\n";
            cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

            cout << "Choose sessions and times from the following options:\n";
            string sessionOptions[] = {"S1 (07:30)", "S2 (09:30)", "S3 (13:30)", "S4 (15:30)"};
            for (int i = 0; i < 4; i++)
            {
                cout << i + 1 << ". " << sessionOptions[i] << "\n";
            }
            string sessions;
            int session;

            cout << "Session (enter the number): ";
            do
            {
                cin >> session;
                cin.ignore();
                if (session < 0 || session > 4)
                {
                    cout << "Invalid session. Please choose a valid session:\n";
                }
                else
                {
                    sessions = sessionOptions[session - 1];
                    break;
                }
            } while (true);

            tmp->session = sessions;
            cout << "Session chosen: " << sessions << "\n";
            cout << setfill('_') << setw(line_width) << "" << setfill(' ') << "\n";

            cout << left << setw(column_width) << "Enter number of credits: ";
            cin >> tmp->numberOfCredits;
            cin.ignore();
            cout << setfill('=') << setw(line_width) << "" << setfill(' ') << "\n";
            cout << "\n\n";
            cout << setw(40) << "+--------------------------------------------------------------+\n";
            cout << setw(40) << "|                  Course updated successfully.               |\n";
            cout << setw(40) << "+--------------------------------------------------------------+\n";
            system("pause");
            return;
        }
        tmp = tmp->next;
    }
    if (!tmp)
    {
        cout << setw(40) << "+--------------------------------------------------------------+\n";
        cout << setw(40) << "|                          Course not found.                   |\n";
        cout << setw(40) << "+--------------------------------------------------------------+\n";
    }
    system("pause");
}

// Semester of courses
void inputSemester(YearLink *&schoolTail)
{
    // SemesterMain* curSemester = schoolTail -> semesterHead;
    int n = 3;
    // cin >> n;
    char tmpCh;
    cout << "| Your year will have 3 semester. Y/N ? ";
    cin >> tmpCh;
    cout << endl;
    while (tmpCh != 'Y' && tmpCh != 'y' && tmpCh != 'n' && tmpCh != 'N')
    {
        cout << setw(40) << "Invalid. Enter Y/N only : ";
        cin >> tmpCh;
        cout << endl;
    }
    if (tmpCh == 'n' || tmpCh == 'N')
    {
        cout << "| Enter the number of semester: ";
        cin >> n;
    }
    schoolTail->numSemester = n;
    // Update student semester
    ClassLink *tmpClass = schoolTail->classHead;
    while (tmpClass)
    {
        for (int i = 0; i < tmpClass->studentNum; i++)
        {
            tmpClass->studentHead[i].curYear->semesterHead = new StudentSemester[n];
        }
        tmpClass = tmpClass->next;
    }

    cin.ignore();
    ///
    schoolTail->semesterHead = new SemesterMain[n];
    SemesterMain *curSemester = schoolTail->semesterHead;
    for (int i = 0; i < n; i++)
    {
        system("cls");
        cout << "| Semester " << i + 1 << ". Year " << schoolTail->start << " - " << schoolTail->end << " |"<< endl << endl;
        // Input start and end of semsester
        cout << "|-- Enter start date: ";
        getline(cin, curSemester[i].start);
        cout << "|\n"; 
        cout << "|-- Enter end date: ";
        getline(cin, curSemester[i].end);
        int ctr;
        // Course Main
        do
        {
            system("cls");
            cout << "=======================================\n";
            cout << "||            Course Menu            ||\n";
            cout << "=======================================\n";
            cout << "||                                   ||\n";
            cout << "|| 1.  Create a new course.          ||\n";
            cout << "||                                   ||\n";
            cout << "|| 2.  View the list of course.      ||\n";
            cout << "||                                   ||\n";
            cout << "|| 3.  Delete a course.              ||\n";
            cout << "||                                   ||\n";
            cout << "|| 4.  Remove student from course.   ||\n";
            cout << "||                                   ||\n";
            cout << "|| 5.  Add student to course.        ||\n";
            cout << "||                                   ||\n";
            cout << "|| 6.  Update course information.    ||\n";
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
                CourseMain *newCourse = new CourseMain;
                newCourse->next = NULL;
                string filename;

                // input new course data here

                inputCourse(newCourse, filename);
                newCourse->semester = i + 1;
                linkCopyToMainStudent(filename, *newCourse, schoolTail);
                if (curSemester[i].courseHead == NULL)
                {
                    curSemester[i].courseHead = newCourse;
                    curSemester[i].courseTail = newCourse;
                }
                else
                {
                    curSemester[i].courseTail->next = newCourse;
                    curSemester[i].courseTail = curSemester[i].courseTail->next;
                }
                break;
            }
            case 2:
            {
                cout << endl;
                viewTheListOfCourse(curSemester[i].courseHead);
                system("pause");
                break;
            }
            case 3:
            {
                cout << endl;
                string courseID;
                cout << "Enter the course ID to delete: ";
                getline(cin, courseID);
                deleteCourse(curSemester[i].courseHead, courseID);
                break;
            }
            case 4:
            {
                removeStudentFromCourse(curSemester[i].courseHead);
                break;
            }
            case 5:
            {
                addStudentToCourse(curSemester[i].courseHead, schoolTail);
                break;
            }
            case 6:
            {
                changeIn4OfCourse(curSemester[i].courseHead);
                break;
            }
            case 0:
            {
                cout << "Exit.\n";
                break;
            }
            }
        } while (ctr != 0);
    }
}