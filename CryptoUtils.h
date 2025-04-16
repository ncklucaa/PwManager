#pragma once
#include <string>

std::string encryptPassword(const std::string& plainText); // encrypts pws using AES
std::string decryptPassword(const std::string& cipherText); // decrypts pws using AES
