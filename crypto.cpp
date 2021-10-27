/*
    SAW3
    Cryptograpy class using cppcrypto lib



*/

#include "cppcrypto/hmac.h"
#include "cppcrypto/sha256.h"
#include "cppcrypto/pbkdf2.h"
#include "cppcrypto/kuznyechik.h"
#include "cppcrypto/camellia.h"
#include "cppcrypto/mars.h"
#include "cppcrypto/sha3.h"

#include "crypto.h"
#include "file_handler.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <memory>

// dev testing
//#include <iostream>

std::string genRand();

Crypto::Crypto()

{




}

Crypto::~Crypto()
{

}

// Encrypt
void Crypto::encrypt(const std::string& fileName,
                     const std::string& password,
                     cppcrypto::block_cipher* cipher)
{
    /*
        encrypt file for SecureObjStorage





    */
    // fileHandler object
    File_handler fh(fileName);

    // Size of file to encrypt
    size_t fileSize = fh.getFileSize();

    // key
    unsigned char key[256/8];

    // Hash the password
    cppcrypto::hmac hMac(cppcrypto::sha256(), password);

    //
    cppcrypto::pbkdf2(hMac,
                      (unsigned char*)"salt",
                      4, 100000,
                      key, sizeof(key)
                      );


    //
    size_t read{0};
    char buffer[16];
    char ctData[16];

    //
    cipher->init(key, cppcrypto::block_cipher::direction::encryption);

    //
    while(read != fileSize)
    {
        fh.read((unsigned char*)buffer, sizeof(buffer));
        cipher->encrypt_block((unsigned char*) buffer, (unsigned char*)ctData);
        fh.write((unsigned char*)ctData, sizeof(buffer));
        read += sizeof(buffer);
    }
    
    //
    fh.complete();
    //delete cipher;



}


// Decrypt
void Crypto::decrypt(const std::string& fileName,
                     const std::string& password,
                     cppcrypto::block_cipher* cipher)
{

    /*
        decrypt file for SecureObjStorage





    */

    //
    File_handler fh(fileName);

    //
    size_t fileSize = fh.getFileSize();

    //
    unsigned char key[256/8];

    //
    cppcrypto::hmac hMac(cppcrypto::sha256(), password);

    //
    cppcrypto::pbkdf2(hMac,
                      (unsigned char*)"salt",
                      4, 100000,
                      key, sizeof(key)
                      );

    //
    size_t read{0};
    char buffer[16];
    char ctData[16];

    //
    cipher->init(key, cppcrypto::block_cipher::direction::decryption);

    //
    while(read != fileSize)
    {
        fh.read((unsigned char*)buffer, sizeof(buffer));
        cipher->decrypt_block((unsigned char*) buffer, (unsigned char*)ctData);
        fh.write((unsigned char*)ctData, sizeof(buffer));
        read += sizeof(buffer);
    }

    //
    fh.complete();



}
























