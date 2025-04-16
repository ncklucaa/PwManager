#include <iostream>
#include <limits>
#include "Accounts.h"
#define NOMINMAX // preventing windows.h from defining min/max macros was too lazy to change it all
#include <Windows.h>

using namespace std;

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
    {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return width;
}

void printCentered(const std::string& text) 
{
    int width = getConsoleWidth();
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
    std::cout << std::string(padding, ' ') << text << std::endl;
}

void printCenteredPrompt(const std::string& text) 
{
    int width = getConsoleWidth();
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
    std::cout << std::string(padding, ' ') << text;
}

void setColor(int colorCode) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

int main() 
{
    setColor(11); // light cyan
    printCentered("=============================");
    printCentered("  Password Vault Manager");
    printCentered("  Encrypted with Crypto++");
    printCentered("=============================");
    std::cout << std::endl;
    setColor(15);

    Accounts vault;
    const std::string vaultFile = "vault.txt";
    vault.loadFromFile(vaultFile); // load saved creds
    int numCreds;

    printCenteredPrompt("How many credentials would you like to enter?: "); // programs starts by asking user how many creds they want to save
    while (!(cin >> numCreds) || numCreds <= 0) 
    {
        printCenteredPrompt("Enter a positive number: ");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < numCreds; ++i) // input loop for creds
    {
        string site, user, pass;
        std::cout << std::endl;
        printCentered("Credential " + to_string(i + 1) + ":");

        printCenteredPrompt("Website: ");
        getline(cin, site);

        printCenteredPrompt("Username: ");
        getline(cin, user);

        do {
            printCenteredPrompt("Password (8-20 chars): "); // input and validate pw length
            getline(cin, pass);
            if (pass.length() < 8 || pass.length() > 20) 
            {
                setColor(4);
                printCentered("Invalid length.");
                setColor(15);
            }
        } while (pass.length() < 8 || pass.length() > 20);

        vault.add(site, user, pass);
    }

    int choice; // menu loop
    do 
    {
        std::cout << std::endl;
        printCentered("Menu:");
        printCentered("1. Show credentials");
        printCentered("2. Add more");
        printCentered("3. Exit");
        printCenteredPrompt("Choice: ");

        while (!(cin >> choice) || choice < 1 || choice > 3) 
        {
            printCenteredPrompt("Enter a number between 1 and 3: ");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if (choice == 1) 
        {
            char reveal; // program asks user if they want to show their passwords'
            do 
            {
                printCenteredPrompt("Show passwords? (y/n): ");
                cin >> reveal;
                cin.ignore();
                reveal = tolower(reveal);
            } while (reveal != 'y' && reveal != 'n');

            vault.show(reveal == 'y');
        }
        else if (choice == 2) 
        {
            int addCount; // add more creds
            printCenteredPrompt("How many more credentials?: ");
            while (!(cin >> addCount) || addCount <= 0) 
            {
                printCenteredPrompt("Enter a positive number: ");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            for (int i = 0; i < addCount; ++i) 
            {
                string site, user, pass;
                std::cout << std::endl;
                printCentered("Credential " + to_string(i + 1) + ":");

                printCenteredPrompt("Website: ");
                getline(cin, site);

                printCenteredPrompt("Username: ");
                getline(cin, user);

                do 
                {
                    printCenteredPrompt("Password (8-20 chars): ");
                    getline(cin, pass);
                    if (pass.length() < 8 || pass.length() > 20) 
                    {
                        setColor(4);
                        printCentered("Invalid length.");
                        setColor(15);
                    }
                } while (pass.length() < 8 || pass.length() > 20);

                vault.add(site, user, pass);
            }
        }

    } while (choice != 3);

    std::cout << std::endl;
    printCentered("Goodbye!");

    vault.saveToFile(vaultFile); // saves creds to txt file

    return 0;
}
