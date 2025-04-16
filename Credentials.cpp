#include "Credentials.h"
#include "CryptoUtils.h"

Credentials::Credentials(const std::string& site, const std::string& user, const std::string& pass) : website(site), username(user) 
{
    setPassword(pass); // encrypts pws
}

std::string Credentials::getWebsite() const 
{
    return website;
}

std::string Credentials::getUser() const 
{
    return username;
}

std::string Credentials::getPassword(bool decrypt) const 
{
    return decrypt ? decryptPassword(encryptedPassword) : "[PROTECTED]";
}

void Credentials::setWebsite(const std::string& site) 
{
    website = site;
}

void Credentials::setUser(const std::string& user) 
{
    username = user;
}

void Credentials::setPassword(const std::string& pass) 
{
    encryptedPassword = encryptPassword(pass); // stores encrypted version
}
