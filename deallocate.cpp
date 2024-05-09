#include "header.h"

// Course bracnh deallocation
void deallocateCourseMain(CourseMain *&courseHead)
{
    CourseMain *tmp = courseHead;
    while (tmp)
    {
        CourseMain *del = tmp;
        delete[] del->copyOfStudent;
        tmp = tmp->next;
        delete del;
    }
    courseHead = nullptr;
}

void deallocateSemesterMain(SemesterMain *&semesterHead)
{
    deallocateCourseMain(semesterHead->courseHead);
    // deallocateCourseMain(semesterHead->courseTail);
    delete[] semesterHead;
    semesterHead = nullptr;
}

// Student branch deallocation
void deallocateStudentCourse(StudentCourse *&courseHead)
{
    StudentCourse *tmp = courseHead;
    while (tmp)
    {
        StudentCourse *del = tmp;
        tmp = tmp->next;
        delete del;
    }
}

void deallocateStudentSemester(StudentSemester *&semesterHead)
{
    deallocateStudentCourse(semesterHead->courseHead);
    deallocateStudentCourse(semesterHead->courseTail);
    delete[] semesterHead;
}

void deallocateStudentYear(StudentYear *&yearHead)
{
    deallocateStudentSemester(yearHead->semesterHead);
    delete[] yearHead;
}

void deallocateStudentArray(StudentArray *&studentHead)
{
    deallocateStudentYear(studentHead->firstYear);
    delete[] studentHead;
}

void deallocateClassLink(ClassLink *&classHead)
{
    ClassLink *tmp = classHead;
    while (tmp)
    {
        ClassLink *del = tmp;
        deallocateStudentArray(del->studentHead);
        tmp = tmp->next;
        delete del;
    }
}

void deallocateYearLink(YearLink *&schoolHead)
{
    YearLink *tmp = schoolHead;
    while (tmp)
    {
        YearLink *del = tmp;
        deallocateClassLink(del->classHead);
        deallocateSemesterMain(del->semesterHead);
        tmp = tmp->next;
        delete del;
    }
}
