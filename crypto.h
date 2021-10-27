#ifndef CRYPTO_H
#define CRYPTO_H

#include "file_handler.h"
#include "cppcrypto/block_cipher.h"

#include <string>
#include <memory>
#include <vector>



class Crypto
{
public:

    Crypto();
    ~Crypto();
    void encrypt(const std::string& fileName,
                 const std::string& password,
                 cppcrypto::block_cipher* cipher);

    void decrypt(const std::string& fileName,
                 const std::string& password,
                 cppcrypto::block_cipher* cipher);



private:
    std::ifstream pwinfile;
    std::ofstream pwoutfile;
};

#endif // CRYPTO_H
