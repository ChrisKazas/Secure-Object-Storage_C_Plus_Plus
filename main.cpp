// SAW3 main file for class testing


#include "cppcrypto/hmac.h"
#include "cppcrypto/sha256.h"
#include "cppcrypto/pbkdf2.h"
#include "cppcrypto/kuznyechik.h"
#include "cppcrypto/mars.h"
#include "cppcrypto/camellia.h"

#include "crypto.h"
#include "file_handler.h"
#include "secureobjstorage.h"

#include <fstream>
#include <string>
#include <memory>
#include <termios.h>
#include <unistd.h>


// Dev testing
#include <iostream>

// Suppress console echo during password input
void enable_tty_echo(bool on)
{
    struct termios settings;
    tcgetattr(STDIN_FILENO, &settings);
    settings.c_lflag = on ? (settings.c_lflag | ECHO) : (settings.c_lflag & (~ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

int main(int argc, char* argv[])
{

    std::string file{argv[1]};
    std::string operation{argv[2]};
    std::string aes{argv[3]};
    std::string password{};

    if(argc != 4)
    {
        throw std::runtime_error("ERROR: Incorrect number of parameters! example: <fileName><operation><algorithm>");
    }

    enable_tty_echo(false);
    std::cout << "Enter your password: ";
    std::cin >> password;
    std::cout << '\n';
    enable_tty_echo(true);



    Crypto c;

    // Encrypt
    if(operation == "enc")
    {
        if(aes == "mars")
        {
            cppcrypto::mars128 cipher;
            c.encrypt(file, password, &cipher);
        }
        else if(aes == "camellia")
        {
            cppcrypto::camellia128 cipher;
            c.encrypt(file, password, &cipher);
        }
        else if(aes == "kuznyechik")
        {
            cppcrypto::kuznyechik cipher;
            c.encrypt(file, password, &cipher);
        }
        else
        {
            throw std::runtime_error("ERROR: Invalid AES Encrytion option! <mars> or <camellia> or <kuznyechik>");
        }
    }

    // Decrypt
    else if(operation == "dec")
    {
        if(aes == "mars")
        {
            cppcrypto::mars128 cipher;
            c.decrypt(file, password, &cipher);
        }
        else if(aes == "camellia")
        {
            cppcrypto::camellia128 cipher;
            c.decrypt(file, password, &cipher);
        }
        else if(aes == "kuznyechik")
        {
            cppcrypto::kuznyechik cipher;
            c.decrypt(file, password, &cipher);
        }
        else
        {
            throw std::runtime_error("ERROR: Invalid AES Encrytion option! <mars> or <camellia> or <kuznyechik>");
        }
    }
    else
    {
        throw std::runtime_error("ERROR: Invalid operation! <enc> or <dec>");
    }

}
