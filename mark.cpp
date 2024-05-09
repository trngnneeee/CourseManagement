#include "header.h"

void replaceSpace (string& str){
    for (int i=0; i< str.length(); i++){
        if (str[i] == ' ') str[i] = '_';
    }
}
// void CourseMain::viewScoreBoard(){
//     StudentCourse* cur;
//     cout << setfill('_') << setw(150) << "_" << setfill(' ') << "\n";
//     cout << "|" << setw(14) << "No" << "|" << setw(49) << "Full Name" << "|" << setw(24) << "Total Mark" << "|" << setw(24) << "Final Mark" << "|" << setw(24) << "Midterm Mark" << "|" << setw(24) << "Other Mark" << "|" << endl;
//     cout << setfill('_') << setw(150) << "_" << setfill(' ') << "\n";
//     for (int i=0; i < curStudent; i++){
//         cur = copyOfStudent[i] -> curYear -> semesterHead[semester-1].courseHead;
//         while (cur && cur -> courseID != courseID) cur = cur -> next;
//         if (cur){
//             cout << "|" << setw(14) << i+1 << "|" << setw(49) << copyOfStudent[i] -> lastName + " " + copyOfStudent[i] -> firstName << "|" << setw(24) << cur -> studentMarkOfThisCourse.totalMark << "|" << setw(24) << cur -> studentMarkOfThisCourse.finalMark << "|" << setw(24) << cur -> studentMarkOfThisCourse.midtermMark << "|" << setw(24) << cur -> studentMarkOfThisCourse.otherMark << "|" << endl;
//         }
//     }
//     cout << setfill('_') << setw(150) << "_" << setfill(' ') << "\n";
// }
void CourseMain::exportList(string filename)
{
    ofstream fout;
    fout.open(filename); // cho nay them duong dan;
    if (!fout.is_open())
    {
        cout << "Can't open file" << endl;
        return;
    }
    fout << "No,ID,Full name, Total Mark, Final Mark, Midterm Mark, Other Mark" << endl;
    for (int i = 0; i < curStudent; i++)
    {
        fout << i + 1 << "," << copyOfStudent[i]->studentID << "," << copyOfStudent[i]->firstName + " " + copyOfStudent[i]->lastName << endl;
    }
    fout.close();
}
void CourseMain::importMark(string filename)
{
    ifstream fin;
    StudentCourse *cur;
    string tmp = "";
    fin.open(filename); // them duong dan
    if (!fin.is_open())
    {
        cout << "Can't import file" << endl;
        return;
    }

    fin.ignore(100, '\n');

    for (int i = 0; i < curStudent; i++)
    {
        fin.ignore(100, ',');
        fin.ignore(100, ',');
        fin.ignore(100, ',');
        cur = copyOfStudent[i]->curYear->semesterHead[semester - 1].courseHead;
        while (cur && cur->courseID != courseID)
        {
            cur = cur->next;
        }
        if (!cur)
            cout << "This Course is not in the data" << endl;
        if (cur)
        {
            getline(fin, tmp, ',');
            cur->studentMarkOfThisCourse.totalMark = stod(tmp);
            tmp = "";
            getline(fin, tmp, ',');
            cur->studentMarkOfThisCourse.finalMark = stod(tmp);
            tmp = "";
            getline(fin, tmp, ',');
            cur->studentMarkOfThisCourse.midtermMark = stod(tmp);
            tmp = "";
            getline(fin, tmp, '\n');
            cur->studentMarkOfThisCourse.otherMark = stod(tmp);
            tmp = " ";
        }
    }
    fin.close();
}


void markManagementMenu (YearLink* year, int semesterNum){
    int cmd = -1;
    int n = 0;
    do {
        system("cls");
        cout << "MARK MANANGEMENT | Semester " << semesterNum << " | Year " << year->start << " - " << year->end << endl;
        cout << "Choose a course : " << endl;
        CourseMain* cur = year -> semesterHead[semesterNum - 1].courseHead;
        int i = 0;
        while  (cur){
            cout << i+1 << ". ";
            i++;
            cout << cur -> courseName << endl;
            n ++;
            cur = cur -> next;
        }
        cout << "Your choice: ";
        cin >> cmd;
        cin.ignore();
        if (cmd > 0 && cmd <= n){
            string defaultFilename;
            string file;
            cur = year -> semesterHead[semesterNum - 1].courseHead;
            i = 0;
            while (i < cmd - 1){
                i++;
                cur = cur -> next;
            }
            defaultFilename = "./Mark/" + cur ->courseID +".csv";
            replaceSpace(defaultFilename);
            // cur is pointing at the wanted course
            int cmd2 = -1;
            do {
                system("cls");
                cout << cur->courseName << endl;
                cout << "Choose an action : " << endl;
                cout << "1. Export list of student " << endl;
                cout << "2. Import score (you need to export first)" << endl;
                cout << "3. View score board" << endl;
                cout << "0. Exit" << endl;
                cout << "Your action : ";
                cin >> cmd2;
                cin.ignore();
                if (cmd2 == 1){
                    cout << "Your export file is " << defaultFilename << endl;
                    cur->exportList(defaultFilename);
                    system("pause");
                }
                else if (cmd2 == 2){
                    char tmp;
                    cout << "Your import file is " << defaultFilename << " Y/N ";
                    cin >> tmp;
                    cin.ignore();
                    while (tmp != 'Y' && tmp != 'y' && tmp != 'n' && tmp != 'N'){
                        cout << "Invalid input . Y/N only : " << endl;
                        cin >> tmp;
                        cin.ignore();
                    }
                    if (tmp == 'n' || tmp == 'N'){
                        cout << "Enter your input file (no need to add .csv) : ";
                        getline (cin, defaultFilename);
                        defaultFilename += ".csv";
                    }
                    cur->importMark(defaultFilename);
                }
                else if (cmd2 == 3){
                    cout << "Score of " << cur->courseName << endl;
                    cur->viewScoreBoard();
                    system("pause");
                }
            }while (cmd2 > 0);
        }
    }while (cmd > 0);
}
