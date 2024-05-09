#include "header.h"
// input database
bool isFileEmpty(string& filename){
    ifstream file("./database/" + filename);
    return file.peek() == ifstream::traits_type::eof();
}

int countElementInFile(string fileName){
    ifstream input("./database/" + fileName);
    if (!input.is_open())
    {
        cout << "File does not exist\n";
        return -1;
    }
    string s;
    int count = 0;
    while (!input.eof()){
        getline(input, s);
        count ++;
    }
    input.close();
    return count;
}

void inputYear(YearLink* &yearHead, YearLink* &yearTail, string HCMUS_database){
    ifstream input("./database/" + HCMUS_database);
    int numYear = countElementInFile(HCMUS_database);
    for (int i = 0; i < numYear; i++)
    {
        ifstream input1;
        string HCMUS_year;
        getline(input, HCMUS_year , '\n');
        input1.open("./database/" + HCMUS_year);
        YearLink* newYear = new YearLink;
        newYear -> next = NULL;
        input1 >> newYear -> start;
        input1.ignore(100, ',');
        input1 >> newYear -> end;
        input1.ignore(100, ',');
        getline(input1, newYear -> yearID, ',');
        string class_list;
        string semester_list;
        getline(input1, class_list, ',');
        // Class Import
        inputClass(newYear -> classHead, newYear -> classTail, class_list);

        input1 >> newYear -> numSemester;
        input1.ignore(100, ',');
        getline(input1, semester_list, '\n');
        // Semester Import
        inputSemesterMain(newYear -> semesterHead, semester_list, newYear);

        if (yearHead == NULL)
        {
            yearHead = newYear;
            yearTail = newYear;
        }
        else
        {
            yearTail -> next = newYear;
            yearTail = yearTail -> next;
        }
        input1.close();
    }
    input.close();
}

// Class Import
void inputClass(ClassLink* &classHead, ClassLink* &classTail, string class_list){
    ifstream input;
    input.open("./database/" + class_list);
    int numClass = countElementInFile(class_list);
    for (int i = 0; i < numClass; i++)
    {
        ifstream input1;
        string className_csv;
        getline(input, className_csv, '\n');
        input1.open("./database/" + className_csv);
        ClassLink* newClass = new ClassLink;
        newClass -> next = NULL;
        getline(input1, newClass -> className, ',');
        int numStu;
        input1 >> numStu;
        newClass -> studentNum = numStu;
        input1.ignore(100, ',');
        string className_list_csv;
        getline(input1, className_list_csv, '\n');
        // Input student array
        inputStudentArray(newClass -> studentHead, className_list_csv, numStu);
        input1.close();

        if (classHead == NULL)
        {
            classHead = newClass;
            classTail = newClass;
        }
        else
        {
            classTail -> next = newClass;
            classTail = classTail -> next;;
        }
    }
    input.close();
}

void inputStudentArray(StudentArray* &studentHead, string className_list_csv, int numStu){
    ifstream input;
    input.open("./database/" + className_list_csv);
    studentHead = new StudentArray[numStu];
    for (int i = 0; i < numStu; i++)
    {
        string studentID_csv;
        getline(input, studentID_csv, '\n');
        ifstream input1;
        input1.open("./database/" + studentID_csv);
        getline(input1, studentHead[i].studentID, ',');
        getline(input1, studentHead[i].firstName, ',');
        getline(input1, studentHead[i].lastName, ',');
        getline(input1, studentHead[i].gender, ',');
        getline(input1, studentHead[i].dateOfBirth, ',');
        getline(input1, studentHead[i].socialID, ',');
        string StudentID_year_list_csv;
        getline(input1, StudentID_year_list_csv, '\n');
        // Input firstYear, curYear
        inputCurYear(studentHead[i].firstYear, studentHead[i].curYear, StudentID_year_list_csv);
        input1.close();
    }
    input.close();
}

void inputCurYear(StudentYear* &firstYear, StudentYear* &curYear, string studentID_year_list_csv){
    int numYear = countElementInFile(studentID_year_list_csv);
    ifstream input;
    input.open("./database/" + studentID_year_list_csv);
    firstYear = new StudentYear[7];
    for (int i = 0; i < numYear; i++)
    {   
        getline(input, firstYear[i].yearID, ',');
        firstYear[i].isStudied = 1;
        string studentID_year_csv;
        getline(input, studentID_year_csv, '\n');
        int numSemester = countElementInFile(studentID_year_csv);
        firstYear[i].numSemester = numSemester;
        // Input studentSemester
        inputStudentSemester(firstYear[i].semesterHead, numSemester, studentID_year_csv);   
    }
    curYear = (firstYear + numYear - 1);
    input.close();
}

void inputStudentSemester(StudentSemester* &semesterHead, int numSemester, string studentID_year_csv){
    semesterHead = new StudentSemester[numSemester];
    ifstream input;
    input.open("./database/" + studentID_year_csv);
    for (int i = 0; i < numSemester; i++)
    {
        // semesterHead[i].start ???
        // semesterHead[i].end ???
        string studentID_Sem_course_csv;
        getline(input, studentID_Sem_course_csv, '\n');
        // Input course
        inputStudentCourse(semesterHead[i].courseHead, semesterHead[i].courseTail, studentID_Sem_course_csv);
    }
    input.close();
}

void inputStudentCourse(StudentCourse* &courseHead, StudentCourse* &courseTail, string studentID_Sem_course_csv){
    int numCourse = countElementInFile(studentID_Sem_course_csv);
    ifstream input;
    input.open("./database/" + studentID_Sem_course_csv);
    for (int i = 0; i < numCourse; i++)
    {
        StudentCourse* newCourse = new StudentCourse;
        newCourse -> next = NULL;
        getline(input, newCourse -> courseID, ',');
        getline(input, newCourse -> courseName, ',');
        string studentID_courseID_mark_csv;
        getline(input, studentID_courseID_mark_csv, '\n');
        // Input mark
        inputMark(newCourse -> studentMarkOfThisCourse, studentID_courseID_mark_csv);
        if (courseHead == NULL)
        {
            courseHead = newCourse;
            courseTail = newCourse;
        }
        else
        {
            courseTail -> next = newCourse;
            courseTail = courseTail -> next;
        }
    }
    input.close();
}

void inputMark(Mark &studentMark, string studentID_courseID_mark_csv){
    ifstream input;
    input.open("./database/" + studentID_courseID_mark_csv);
    input >> studentMark.totalMark;
    input.ignore(100, ',');
    input >> studentMark.finalMark;
    input.ignore(100, ',');
    input >> studentMark.midtermMark;
    input.ignore(100, ',');
    input >> studentMark.otherMark;
    input.close();
}

// Semester main Import
void inputSemesterMain(SemesterMain* &semesterHead, string semester_list, YearLink* newYear){
    int numSemester = countElementInFile(semester_list);
    semesterHead = new SemesterMain[numSemester];
    ifstream input;
    input.open("./database/" + semester_list);
    for (int i = 0; i < numSemester; i++)
    {
        string dataFileOf1MainSemester;
        getline(input, dataFileOf1MainSemester, '\n');
        ifstream input1;
        input1.open("./database/" + dataFileOf1MainSemester);
        getline(input1, semesterHead[i].start, ',');
        getline(input1, semesterHead[i].end, ',');
        string course_list;
        getline(input1, course_list, '\n');
        // Input CourseMain
        inputCourseMain(semesterHead[i].courseHead, semesterHead[i].courseTail, course_list, newYear);
        input1.close();
    }
    input.close();
}

void inputCourseMain(CourseMain* &courseHead, CourseMain* &courseTail, string course_list, YearLink* newYear){
    ifstream input;
    input.open("./database/" + course_list);
    int numCourse = countElementInFile(course_list);
    for (int i = 0; i < numCourse; i++)
    {
        CourseMain* newCourse = new CourseMain;
        newCourse -> next = NULL;
        string dataOf1Course;
        getline(input, dataOf1Course, '\n');
        ifstream input1;
        input1.open("./database/" + dataOf1Course);
        getline(input1, newCourse -> courseID, ',');
        getline(input1, newCourse -> courseName, ',');
        getline(input1, newCourse -> className, ',');
        getline(input1, newCourse -> teacherName, ',');
        getline(input1, newCourse -> day, ',');
        getline(input1, newCourse -> session, ',');
        input1 >> newCourse -> semester;
        input1.ignore(100, ',');
        input1 >> newCourse -> numberOfCredits;
        input1.ignore(100, ',');
        input1 >> newCourse -> curStudent;
        input1.ignore(100, ',');
        int max;
        input1 >> max;
        newCourse -> maxStudent = max;
        input1.ignore(100, ',');
        string studentCopyData;
        getline(input1, studentCopyData, '\n');
        linkCopyToLink(newCourse-> copyOfStudent, max, studentCopyData, newYear);
        ////////////////////////////


        if (courseHead == NULL)
        {
            courseHead = newCourse;
            courseTail = newCourse;
        }
        else
        {
            courseTail -> next = newCourse;
            courseTail = courseTail -> next;
        }
        input1.close();
    }
    input.close();
}

void linkCopyToLink (StudentArray** &copyOfStuArr, int maxStu, string studentCopyData_file, YearLink* newYear){
    ifstream input;
    input.open("./database/" + studentCopyData_file);
    copyOfStuArr = new StudentArray*[maxStu];
    for (int j=0; j<maxStu; j++){
        string tmpID;
        getline(input, tmpID, '\n');
        ClassLink* tmpClass = newYear -> classHead;
        while (tmpClass){
            bool flag = 0;
            for (int i=0; i < tmpClass -> studentNum; i++)
            {
                if (tmpID == tmpClass->studentHead[i].studentID ){
                    copyOfStuArr[j] = &tmpClass->studentHead[i];
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) break;
            tmpClass = tmpClass -> next;
        }
    }
    input.close();
}