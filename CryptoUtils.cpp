#include "CryptoUtils.h"
#include "aes.h"
#include "filters.h"
#include "modes.h"
#include "osrng.h"

using namespace CryptoPP;

// changed from 16 bit to 128 bit symmetric key and IV
static const byte KEY[16] = { 'm','y','s','e','c','u','r','e','k','e','y','1','2','3','4','5' };
static const byte IV[16] = { 'i','n','i','t','i','a','l','v','e','c','t','o','r','1','2','3' };

std::string encryptPassword(const std::string& plainText) // encrypt plain text using AES CBC mode
{
    std::string cipher;
    CBC_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(KEY, sizeof(KEY), IV);
    StringSource ss(plainText, true, new StreamTransformationFilter(enc, new StringSink(cipher)));
    return cipher;
}

std::string decryptPassword(const std::string& cipherText) // decrypt AES-encrypted text back to plain text
{
    std::string recovered;
    CBC_Mode<AES>::Decryption dec;
    dec.SetKeyWithIV(KEY, sizeof(KEY), IV);
    StringSource ss(cipherText, true, new StreamTransformationFilter(dec, new StringSink(recovered)));
    return recovered;
}
