#include "Accounts.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <sstream>

Accounts::Accounts() : size(0), capacity(2) 
{
    credentials = new Credentials * [capacity]; // allocate initial space
}

Accounts::~Accounts() 
{
    for (int i = 0; i < size; ++i) // clean up dynamically allocated creds obj
    {
        delete credentials[i];
    }
    delete[] credentials;
}

void Accounts::resize() 
{
    capacity *= 2;
    Credentials** temp = new Credentials * [capacity];

    for (int i = 0; i < size; ++i) // double the cap and copy over existing ptrs
    {
        temp[i] = credentials[i];
    }
    delete[] credentials;
    credentials = temp;
}

void Accounts::add(const std::string& site, const std::string& user, const std::string& pass) 
{
    assert(pass.length() >= 8 && pass.length() <= 20 && "Password must be 8-20 characters"); // validate pws using assert

    if (size == capacity) 
    {
        resize(); // expands if array is full
    }

    credentials[size++] = new Credentials(site, user, pass);
}

void Accounts::show(bool revealPasswords) const 
{
    std::cout << "\nStored Credentials:\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "| Website         | Username        | Password        |\n";  // prints user input
    std::cout << "-------------------------------------------------------\n";

    for (int i = 0; i < size; ++i) 
    {
        std::cout << "| " << std::setw(15) << credentials[i]->getWebsite()
            << " | " << std::setw(15) << credentials[i]->getUser()
            << " | " << std::setw(15) << credentials[i]->getPassword(revealPasswords)
            << " |\n";
    }
    std::cout << "-------------------------------------------------------\n";
}

void Accounts::saveToFile(const std::string& filename) const 
{
    std::ofstream outFile(filename);
    if (!outFile) 
    {
        std::cerr << "Error writing to file.\n";
        return;
    }

    for (int i = 0; i < size; ++i) // save decrypted pws
    {
        outFile << credentials[i]->getWebsite() << "," << credentials[i]->getUser() << "," << credentials[i]->getPassword(true) << "\n";
    }
    outFile.close();
    std::cout << "Credentials saved to " << filename << "\n";
}

void Accounts::loadFromFile(const std::string& filename) 
{
    std::ifstream inFile(filename);
    if (!inFile) 
    {
        std::cerr << "No existing vault file found.\n";
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) 
    {
        std::istringstream iss(line);
        std::string site, user, pass;

        std::getline(iss, site, ',');
        std::getline(iss, user, ',');
        std::getline(iss, pass);

        if (!site.empty() && !user.empty() && !pass.empty()) 
        {
            add(site, user, pass); // re-encrypts on load
        }
    }
    inFile.close();
    std::cout << "Loaded credentials from " << filename << "\n";
}
