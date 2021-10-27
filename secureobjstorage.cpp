// Secure Object Storage Class


#include "secureobjstorage.h"
#include "file_handler.h"
#include "crypto.h"

#include <fstream>
#include <string>


SecureObjStorage::SecureObjStorage(const std::string& fileName)
    : fileName_(fileName)
{
}

//SecureObjStorage::SecureObjStorage(std::stringfile, fileType type)
//{

//}

void SecureObjStorage::load()
{

    //cryptoObj_->decrypt(fileName_);

}

void SecureObjStorage::save()
{
    //cryptoObj_->encrypt(fileName_);
}
