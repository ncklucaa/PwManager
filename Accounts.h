#pragma once
#include "Credentials.h"

class Accounts // dynamic list of creds
{
private:
    Credentials** credentials;
    int size;
    int capacity;

    void resize(); // resize when array full

public:
    Accounts(); // constructor
    ~Accounts(); // destructor

    void add(const std::string& site, const std::string& user, const std::string& pass); // adds new creds
    void show(bool revealPasswords = false) const; // shows all saved creds with showing password optionally
    void saveToFile(const std::string& filename) const; // saves user input to txt file
    void loadFromFile(const std::string& filename); // loads user input/creds from txt file
};
