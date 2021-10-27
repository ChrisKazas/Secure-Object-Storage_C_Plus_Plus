#ifndef SECUREOBJSTORAGE_H
#define SECUREOBJSTORAGE_H

#include "file_handler.h"
#include "crypto.h"

#include <string>
#include <fstream>
#include <memory>

class SecureObjStorage
{
public:
//    enum class fileType {xml, json, text};
    enum class fileType {XML, JSON, TXT};

    SecureObjStorage(const std::string& file);
//    SecureObjStorage(std::string file, fileType type);

    void load();
    void save();

private:
    std::unique_ptr<Crypto> cryptoObj_ = std::make_unique<Crypto>();
    std::string fileName_;

};

#endif // SECUREOBJSTORAGE_H
