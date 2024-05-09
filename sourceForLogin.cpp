#include "header.h"

void printTopBar()
{
    std::cout << "[ INSTRUCTION ]";
    std::cout << "\n- Type any keys else OR follow the commands to exit.";
    std::cout << "\n----------------------------------------------------" << std::endl;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printTopBar();
}

int PASSWORD_LENGTH = 3;

using namespace std;

Account parseIndex(const string &line)
{
    string str[3];
    int startIndex = 0, endIndex;
    int index = 0;

    for (int i = 0; i < 3; ++i)
    {
        endIndex = line.find(',', startIndex);
        if (endIndex == string::npos)
            endIndex = line.length();
        str[index++] = line.substr(startIndex, endIndex - startIndex);
        startIndex = endIndex + 1;
    }

    Account account;
    account.AccountID = str[0];
    account.Password = str[1];
    account.Username = str[2];

    return account;
}

void fillList(ifstream &file, Account *&LIST, const int &LIMIT, int &NUMS)
{
    string line;
    while (getline(file, line))
    {
        LIST[NUMS++] = parseIndex(line);
        if (NUMS >= LIMIT)
        {
            cout << "Maximum number reached." << endl;
            break;
        }
    }
}

void replaceList(Account *&oldList, Account *newList, int size)
{
    delete[] oldList;
    oldList = newList;
}

void updatePassword(const int &logged_as, const string AccountID, const string newPassword)
{
    string filename = ((logged_as == 1) ? "./Student_Members.csv" : "./Staff_Members.csv");
    ifstream infile(filename.c_str());
    if (!infile)
    {
        cerr << "Error: Unable to open file csv" << endl;
        return;
    }

    string content;
    string line;
    bool found = false;
    while (getline(infile, line))
    {
        int pos = line.find(",");
        string id = line.substr(0, pos);
        pos = line.find(",") + 1;
        string password = line.substr(pos, line.find(",", pos) - pos);
        pos = line.find(",", pos) + 1;
        string username = line.substr(pos);

        if (id == AccountID)
        {
            content += id + "," + newPassword + "," + username + "\n";
            found = true;
        }
        else
        {
            content += line + "\n";
        }
    }
    infile.close();

    if (!found)
    {
        cerr << "Error: Account with ID " << AccountID << " not found." << endl;
        return;
    }

    ofstream outfile(filename.c_str());
    if (!outfile)
    {
        cerr << "Error: Unable to open file csv for writing." << endl;
        return;
    }
    outfile << content;
    outfile.close();

    clearScreen();
    cout << endl;
    return;
}

bool login(Account *&LIST, int &NUMS, const int LIMIT, loggedAccount *&LoggedAccount)
{
    cout << "\nLOG IN AS A/AN";
    cout << "\n1. Log in as a student.";
    cout << "\n2. Log in as an academic staff member.";
    cout << "\nYour option : ";
    cin >> LoggedAccount->type;

    if (LoggedAccount->type != 1 && LoggedAccount->type != 2)
    {
        clearScreen();
        return false;
    }

    clearScreen();

    if (LoggedAccount->type == 1 || LoggedAccount->type == 2)
    {
        ifstream file((LoggedAccount->type == 1) ? "./Student_Members.csv" : "./Staff_Members.csv");

        if (!file.is_open())
        {
            cerr << "Error while opening file !" << endl;
            return false;
        }

        NUMS = 0;
        Account *newList = new Account[LIMIT];
        fillList(file, newList, LIMIT, NUMS);
        replaceList(LIST, newList, NUMS);

        file.close();
        bool exit = false;
        bool authenticated = Authenticate(LIST, NUMS, LIMIT, LoggedAccount->type, LoggedAccount->accountid, LoggedAccount->username, exit);

        if (authenticated)
        {
            return true;
        }
        else
        {
            if (exit == true)
            {
                clearScreen();
                return false;
            }
            else
            {
                cout << endl;
                cout << "OOPS, WE CAN NOT FIND YOUR ACCOUNT :(";
                cout << "\n1. Return to log in session.";
                int option;
                cout << "\nYour option : ";
                cin >> option;
                clearScreen();
                if (option == 1)
                {
                    return login(LIST, NUMS, LIMIT, LoggedAccount);
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

bool ResetPassword(const int &logged_as, const int &Order, Account *&LIST)
{
    string new_password;
    cout << "\nRESET PASSWORD ( FIRST TIME LOGGED IN )";
    cout << "\nEnter Your New Password : ";
    cin >> new_password;
    if (LIST[Order].Password == new_password)
    {
        clearScreen();
        cout << "<< New Password Must Be Different From The Old One >>";
        return ResetPassword(logged_as, Order, LIST);
    }
    else
    {
        LIST[Order].Password = new_password;
        updatePassword(logged_as, LIST[Order].AccountID, LIST[Order].Password);
        return true;
    }
}

bool ChangePassword2(const int &logged_as, const int Order, Account *&LIST, const int &NUMS, const string &cur_password)
{
    string new_password;
    cout << "\nEnter Your New Password : ";
    cin >> new_password;
    if (cur_password == new_password)
    {
        clearScreen();
        cout << "<< New Password Must Be Different From The Old One >>";
        return ChangePassword2(logged_as, Order, LIST, NUMS, cur_password);
    }
    else
    {
        if (new_password.length() > PASSWORD_LENGTH)
        {
            LIST[Order].Password = new_password;
            updatePassword(logged_as, LIST[Order].AccountID, LIST[Order].Password);
            return true;
        }
        else
        {
            clearScreen();
            cout << "<< New Password Must Be More Than " << PASSWORD_LENGTH << " Letters >>";
            return ChangePassword2(logged_as, Order, LIST, NUMS, cur_password);
        }
    }
}

bool ChangePassword(const int &logged_as, const string &logged_account, Account *&LIST, const int &NUMS)
{
    int Order;

    for (int i = 0; i < NUMS; i++)
    {
        if (LIST[i].AccountID == logged_account)
        {
            Order = i;
            break;
        }
    }
    string cur_password;
    cout << "\nEnter Your Current Password : ";
    cin >> cur_password;
    if (LIST[Order].Password == cur_password)
    {
        clearScreen();
        return ChangePassword2(logged_as, Order, LIST, NUMS, cur_password);
    }
    else
    {
        clearScreen();
        cout << "<< Current Password Invalid >>";
        return ChangePassword(logged_as, logged_account, LIST, NUMS);
    }
}

bool PasswordCheck(const int logged_as, const int Order, Account *&LIST)
{
    string password;
    cout << "Enter Your Password : ";
    cin >> password;
    int password_type = 0;
    if (LIST[Order].Password == password)
    {
        if (logged_as == 1)
        {
            password_type = (LIST[Order].Password != "1") ? 1 : 2;
        }
        else if (logged_as == 2)
        {
            password_type = (LIST[Order].Password != "1staff") ? 1 : 2;
        }
    }
    else if (password == "-1")
    {
        password_type = 3;
    }

    if (password_type == 1)
    {
        clearScreen();
        cout << endl;
        return true;
    }
    else if (password_type == 2)
    {
        clearScreen();
        if (ResetPassword(logged_as, Order, LIST))
        {
            return true;
        }
    }
    else if (password_type == 3)
    {
        clearScreen();
        return false;
    }
    else
    {
        clearScreen();
        cout << "<< Type -1 to exit | Wrong Password >>" << endl;
        cout << "Enter Your Account ID : " << LIST[Order].AccountID << endl;
        if (PasswordCheck(logged_as, Order, LIST) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Authenticate(Account *&LIST, int &NUMS, const int LIMIT, int &logged_as, string &logged_account, string &logged_user, bool &exit)
{
    string username;
    cout << endl;
    cout << "Enter Your AcountID : ";
    cin >> username;
    int Order = -1;
    for (int i = 0; i < NUMS; i++)
    {
        if (LIST[i].AccountID == username)
        {
            Order = i;
            break;
        }
    }
    if (Order != -1)
    {
        if (PasswordCheck(logged_as, Order, LIST) == true)
        {
            logged_account = LIST[Order].AccountID;
            logged_user = LIST[Order].Username;
            return true;
        }
        else
        {
            exit = true;
            return false;
        }
    }
    else
    {
        clearScreen();
        return false;
    }
}


////////////////////////////////////////////////////////


void createNewAccountForStudent (string studentID, string fullName){
    string fileName = "Student_Members.csv";
    string defaultPassword = "1";
    ofstream fout;
    fout.open(fileName, ios:: app);
    if (!fout.is_open())
    {
        cout << "File does not exist";
        return;
    }
    fout << studentID << "," << defaultPassword << "," << fullName << endl;
    fout.close();
}