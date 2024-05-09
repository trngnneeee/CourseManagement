
#include "header.h" 

void databaseExport(YearLink* schoolHead, YearLink* schoolTail){
    ofstream fout1;
    fout1.open("./database/HCMUS_database.csv");
    YearLink* tmpSchoolHead = schoolHead;
    while (tmpSchoolHead)
    {
        ofstream fout;
        fout.open("./database/HCMUS_" + tmpSchoolHead ->yearID + ".csv");
        classExport(tmpSchoolHead);
        semesterExport(tmpSchoolHead);
        fout << tmpSchoolHead -> start << "," << tmpSchoolHead -> end << "," << tmpSchoolHead -> yearID << "," << tmpSchoolHead -> yearID + "_class_list.csv" << "," << tmpSchoolHead -> numSemester << "," << tmpSchoolHead -> yearID + "_semester_list.csv";
        fout.close();
        fout1 << "HCMUS_" + tmpSchoolHead ->yearID + ".csv";
        if (tmpSchoolHead -> next) fout1 << endl;
        tmpSchoolHead = tmpSchoolHead -> next;
    }
    fout1.close();
}


void classExport(YearLink* schoolHead){ 
    ////////////TMP///////
    string tmpstudentID;
    string tmpcourseID;
    string filename;
    string tmpFileName;
    string tmpFileName2;
    ClassLink* tmpClass = nullptr;
    StudentYear* tmpStuYear = nullptr;
    StudentCourse* tmpStuCourse = nullptr;
    ///////////////////
    while (schoolHead){
        tmpClass = schoolHead -> classHead;
        /////////////////////
        ofstream fout7;
        fout7.open("./database/" + schoolHead -> yearID + "_class_list.csv");
        ////////////////////
        while (tmpClass){
            ////////////////////////////////
            
            ///////////////////////////////
            ofstream fout6;
            fout6.open("./database/" + tmpClass ->className + ".csv");
            ////////////////////////////////
            ofstream fout5;
            fout5.open("./database/" + tmpClass->className + "_list.csv");
            ///////////////////////////////
            for (int i=0 ;i< tmpClass->studentNum; i++){
                tmpstudentID = tmpClass->studentHead[i].studentID;
                tmpStuYear = tmpClass->studentHead[i].firstYear;
                ///////////////////////////////////////
                ofstream fout4;
                fout4.open("./database/" + tmpstudentID + ".csv");
                ////////////////////////////////////////
                ofstream fout3;
                fout3.open("./database/" + tmpstudentID + "_year_list.csv");
                //////////////////////////////////////
                while (tmpStuYear <= tmpClass->studentHead[i].curYear){
                    //////////////////////////////////
                    ofstream fout2;
                    fout2.open("./database/" + tmpstudentID + '_' + tmpStuYear->yearID + "_year.csv");
                    ///////////////////////////////////////////
                    for (int j=0; j < schoolHead->numSemester; j++){
                        tmpStuCourse = tmpStuYear ->semesterHead[j].courseHead;
                        ofstream fout1;
                        ///////////////////////
                        tmpFileName = tmpstudentID + "_Sem" + to_string(j+1) + "_" + schoolHead->yearID + "_course.csv";
                        fout1.open("./database/" + tmpFileName);
                        ////////////////////////
                        while (tmpStuCourse){
                            tmpcourseID = tmpStuCourse->courseID;
                            ///////////////////classExport//////// file name MSSV_CourseID_mark.csv
                            filename = tmpstudentID + '_' + tmpcourseID + "_Sem" + to_string(j+1) + "_" + schoolHead -> yearID + "_mark.csv";
                            ofstream fout;
                            fout.open("./database/" + filename);
                            fout << tmpStuCourse->studentMarkOfThisCourse.totalMark << "," << tmpStuCourse->studentMarkOfThisCourse.finalMark << "," << tmpStuCourse->studentMarkOfThisCourse.midtermMark << "," << tmpStuCourse->studentMarkOfThisCourse.otherMark;
                            fout.close();
                            ///////////////////////studentCourse////// file name MSSV_Sem#_course.csv 
                            fout1 << tmpcourseID << ',' << tmpStuCourse->courseName << ',' << filename;
                            if (tmpStuCourse->next) fout1 << endl;
                            ///////////////////////////////
                            tmpStuCourse = tmpStuCourse -> next;
                        }
                        ///////////////////////
                        fout2 << tmpFileName;
                        if (j != schoolHead -> numSemester - 1) fout2 << endl;
                        ///////////////////////
                        fout1.close();
                    }
                    ////////////////////////
                    fout2.close();
                    
                    ///////////////////////
                    fout3 << tmpStuYear->yearID << "," << tmpstudentID + '_' + tmpStuYear->yearID + "_year.csv";
                    if (tmpStuYear != tmpClass->studentHead[i].curYear) fout3<< endl;
                    ///////////////////////
                    tmpStuYear++;
                }
                fout4 << tmpClass->studentHead[i].studentID << "," << tmpClass->studentHead[i].firstName << ","<< tmpClass->studentHead[i].lastName << "," << tmpClass->studentHead[i].gender << "," << tmpClass->studentHead[i].dateOfBirth << "," << tmpClass->studentHead[i].socialID << "," << tmpstudentID + "_year_list.csv";
                ///////////////////////
                fout3.close();
                fout4.close();
                ///////////////////////
                fout5 << tmpstudentID + ".csv";
                if (i != tmpClass->studentNum - 1) fout5 << endl;
                ///////////////////////
            }
            fout6 << tmpClass ->className << "," << tmpClass->studentNum << "," << tmpClass->className + "_list.csv";
            ////////////////////
            fout7 << tmpClass ->className + ".csv";
            if (tmpClass -> next) fout7 << endl;
            ///////////////////
            fout5.close();
            fout6.close();
            /////////////////////
            tmpClass = tmpClass -> next;
        }
        fout7.close();
        schoolHead = schoolHead -> next;
    }
}

void semesterExport (YearLink* year){
    SemesterMain* tmpSem = nullptr;
    CourseMain* tmpCourse = nullptr;
    ///////////////////
    ofstream fout4;
    fout4.open("./database/" + year -> yearID + "_semester_list.csv");
    /////////////////
    for(int i=0; i< year->numSemester; i++){
        tmpCourse = year ->semesterHead[i].courseHead;
        ///////////////////
        ofstream fout3;
        ofstream fout2;
        fout2.open("./database/Main_Sem" + to_string(i+1) + "_" + year->yearID+ "_course_list.csv");
        fout3.open("./database/Main_Sem" + to_string(i+1) + "_" + year->yearID + ".csv");
        
        //////////////////
        while (tmpCourse){
            ///////////////////////////
            ofstream fout;
            ofstream fout1;
            fout1.open("./database/Main_" + tmpCourse -> courseID + "_Sem" + to_string(i+1) + "_" + year->yearID + ".csv");
            fout.open("./database/Main_" + tmpCourse -> courseID + "_Sem" + to_string(i+1) + "_" + year->yearID + "_list.csv");
            ///////////////////////////
            for (int j=0; j< tmpCourse->curStudent; j++){
                ////////////////////
                fout << tmpCourse -> copyOfStudent[j] ->studentID;
                if (j != tmpCourse -> curStudent - 1) fout << endl;
                ////////////////////
            }
            fout1 << tmpCourse -> courseID << "," << tmpCourse -> courseName << "," << tmpCourse -> className << "," << tmpCourse -> teacherName << "," << tmpCourse -> day << "," << tmpCourse -> session << "," << tmpCourse -> semester << "," << tmpCourse -> numberOfCredits << "," << tmpCourse -> curStudent << "," << tmpCourse -> maxStudent << "," <<  "Main_" + tmpCourse->courseID + "_Sem" + to_string(i+1) + "_" + year->yearID + "_list.csv";
            //////////////////
            fout.close();
            fout1.close();

            /////////////////
            fout2 <<  "Main_" + tmpCourse -> courseID + "_Sem" + to_string(i+1) + "_" + year->yearID + ".csv";
            if (tmpCourse->next) fout2 << endl;
            /////////////////
            tmpCourse = tmpCourse -> next;
        }
        fout3 << year->semesterHead[i].start << "," << year->semesterHead[i].end << "," << "Main_Sem" + to_string(i+1) +  "_" + year->yearID+ "_course_list.csv";
        fout4 << ("Main_Sem" + to_string(i+1) + "_" + year->yearID + ".csv");
        if (i != year -> numSemester - 1) fout4 << endl;
        ///////////
        fout2.close();
        fout3.close();
        //////////
    }
    /////////
    fout4.close();
    /////////
}