#pragma once
#include <string>

class Credentials 
{
private:
    std::string website;
    std::string username;
    std::string encryptedPassword; // stores pws in encrypted form

public:
    Credentials(const std::string& site, const std::string& user, const std::string& pass); // constructor encrypts and stores pws

    std::string getWebsite() const;
    std::string getUser() const;
    std::string getPassword(bool decrypt = false) const; // returns either shown pws or protected/hidden

    void setWebsite(const std::string& site);
    void setUser(const std::string& user);
    void setPassword(const std::string& pass); // encrypts pws before storing it
};
