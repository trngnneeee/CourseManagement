#include "header.h"
// year treatment holy fk

void createNewYear (YearLink* &schoolHead, YearLink* &schoolTail){
    YearLink* tmp = schoolHead;
    // update curr year for each student
    while (tmp){
        ClassLink* tmpClass = tmp ->classHead;
        while (tmpClass){
            for (int i=0 ;i < tmpClass->studentNum; i++){
                if (tmpClass->studentHead[i].curYear - tmpClass->studentHead[i].firstYear <=  6)
                    tmpClass->studentHead[i].curYear++;
            }
            tmpClass = tmpClass -> next;
        }
        tmp = tmp -> next;
    }
    // initialize a year
    if (!schoolHead){
        schoolHead = new YearLink;
        schoolTail = schoolHead;
    }
    else {
        schoolTail -> next = new YearLink;
        schoolTail = schoolTail -> next;
    }
    schoolTail -> next = nullptr;
    cout << "Enter year ID : (year id is the first two characters in a student's ID) : ";
    cin >> schoolTail->yearID;
    cout << "The starting year of this school year  :";
    cin >> schoolTail->start;
    cout << "The final year of this school year  :";
    cin >> schoolTail->end;
} 
int countStudentNum(string filename) {
    ifstream file;
    file.open(filename);
    if(!file.is_open()) {
        cout << "File does not exist" << endl;
        return 0;
    }
    int count = 0;
    string line;
    while (!file.eof()) {
        getline(file, line);
        count++;
    }
    file.close();
    return --count;
}

void addAClass(YearLink* &currYear){
    string filename;
    string classname;
    char tmpCh;

    // initialize a new class
    // cin.ignore();
    cout << "What is your class' name:  ";
    getline(cin, classname);

    if (!currYear -> classHead){
        
        currYear->classHead = new ClassLink;
        currYear->classTail = currYear -> classHead;
    }
    else{
       
        currYear -> classTail -> next = new ClassLink;
        currYear -> classTail = currYear -> classTail -> next;
    }
    filename = classname + ".csv";
    filename = "./importClass/" + filename;
    cout << "You will import this class by " << filename << "   Y/N  ?";
    cin >> tmpCh;
    // cin.ignore();
    while (tmpCh != 'Y' && tmpCh != 'y' && tmpCh != 'n' && tmpCh != 'N'){
        cout << "Invalid. Enter Y/N only : ";
        cin >> tmpCh;
        cin.ignore();
    }
    if (tmpCh == 'n' || tmpCh == 'N'){
        cout << "Enter your import file (.csv) : ";
        getline(cin, filename);
        filename = filename + ".csv";
    }
    int numStu = countStudentNum(filename);
    cout << "This class will have "<< numStu << " students maximum. Y/N ? ";
    cin >> tmpCh;
    cin.ignore();
    while (tmpCh != 'Y' && tmpCh != 'y' && tmpCh != 'n' && tmpCh != 'N'){
        cout << "Invalid. Enter Y/N only : ";
        cin >> tmpCh;
        cin.ignore();
    }
    int tmpCap;
    if (tmpCh == 'n' || tmpCh == 'N'){
        cout << "Enter the max number of student: ";
        cin >> tmpCap;
        while (tmpCap < numStu){
            cout << "This capacity is smaller than the number of students in " << filename << " ! . Please enter another number: ";
            cin >> tmpCap;
        }
        currYear -> classTail -> capacity = tmpCap;
    }
    if (tmpCh == 'y' || tmpCh == 'Y'){
        currYear -> classTail -> capacity = numStu;
    }
    currYear -> classTail -> studentNum = numStu;
    tmpCh = 0;
    currYear -> classTail -> className = classname;
    currYear -> classTail ->studentHead = new StudentArray[currYear -> classTail -> capacity];
   

    // filename = classname + ".csv";
    

    // import class file format: 
    // No, Student ID, First name, Last name, Gender, Date of Birth, Social ID.
    // the rest of file is data in this order
    string s;
    ClassLink* pClass = currYear -> classTail;
    ifstream fin;
    int i = 0;
    fin.open(filename);
    if (i < !fin.is_open()){
        cout << filename << " can not be opened." << endl;
    }
    getline (fin, s);
    while (i < pClass -> studentNum && !fin.eof() ){
        fin.ignore(100, ','); // ignore No collumn
        getline (fin, s, ',');
        pClass -> studentHead[i].studentID = s;
        getline (fin, s, ',');
        pClass -> studentHead[i].firstName = s;
        getline (fin, s, ',');
        pClass -> studentHead[i].lastName = s;
        getline (fin, s, ',');
        pClass -> studentHead[i].gender = s;
        getline (fin, s, ',');
        pClass -> studentHead[i].dateOfBirth = s;
        getline (fin, s, '\n');
        pClass -> studentHead[i].socialID = s;
        pClass -> studentHead[i].firstYear = new StudentYear[7];
        pClass -> studentHead[i].curYear = pClass -> studentHead[i].firstYear; // khoa them vo
        pClass -> studentHead[i].curYear->yearID = currYear->yearID;
        pClass -> studentHead[i].curYear->numSemester = currYear->numSemester;
        createNewAccountForStudent(pClass -> studentHead[i].studentID, pClass -> studentHead[i].lastName + " " + pClass -> studentHead[i].firstName);
        i++;
    }
}
