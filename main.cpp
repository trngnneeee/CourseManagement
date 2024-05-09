#include "header.h"

int main()
{
    // input database
    YearLink *HCMUS = nullptr;
    YearLink *tailHCMUS = nullptr;
    string HCMUS_database = "HCMUS_database.csv";
    if (!isFileEmpty(HCMUS_database))
    {
        inputYear(HCMUS, tailHCMUS, HCMUS_database);
    }
    // Login
    while (true)
    {
        clearScreen();
        long long LIMIT = 2e9;
        int NUMS = 0;
        Account *LIST = new Account[LIMIT];
        loggedAccount *LoggedAccount = new loggedAccount;

        if (login(LIST, NUMS, LIMIT, LoggedAccount) == false)
        {
            std::cout << std::endl;
            std::cout << "Program Exited.";
            break;
        }
        while (true)
        {
            clearScreen();
            std::cout << "\nWelcome, " << LoggedAccount->username << ".";
            std::cout << std::endl;
            int option;
            std::cout << "\nCommands :";
            std::cout << "\n1. Change Password.";
            std::cout << "\n2. Sign out.";
            if (LoggedAccount->type == 2)
            {
                cout << "\n3. Mark management.";
            }
            else
                cout << "\n3. View score.";
            cout << "\n0. Exit.";
            std::cout << "\nYour option : ";
            std::cin >> option;
            clearScreen();
            if (option == 1)
            {
                if (ChangePassword(LoggedAccount->type, LoggedAccount->accountid, LIST, NUMS))
                {
                    std::cout << "Changed Password Successfully" << std::endl;
                    system("Pause");
                }
            }
            else if (option == 2)
            {
                delete[] LIST;
                delete LoggedAccount;
                std::cout << "\nSign out successfully." << std::endl;
                system("Pause");
                break;
            }
            else if (LoggedAccount->type == 2 && option == 3)
            {
                teacherMenu(HCMUS, tailHCMUS);
            }
            else if (LoggedAccount->type == 1 && option == 3)
            {
                studentMenu(HCMUS, LoggedAccount->accountid);
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Program Exited.";
                break;
            }
        }
    }
    databaseExport(HCMUS, tailHCMUS);
    return 0;
}
