/*
 *  SAW3- SecureObjStorage
 *
 *  March 15 2018
 *
 *  Chris Kazas
 *
 *  File wrapper Class for SecureObjStorage and Crypto class
 *
 *
*/


#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


#include <string>
#include <fstream>


class File_handler
{
public:


    /*
     *   Opens 2 files - target file as infile_ and
     *   outfile_ as tmpfile to work with.
     *   Sets filesize_ data member
     *   Sets success_ data member to false
    */
    File_handler(const std::string& fileName);
    ~File_handler();

    // read char* from file
    void read(unsigned char* buf, size_t len);

    // write char* to file
    void write(unsigned char* buf, size_t len);

    // return the size of the file
    long long getFileSize();

    // return the file locaction
    std::string getFileLocation();
    std::string getTmpFileLoc();

    // Swap temp file with file
    void complete();

private:

    std::string fileloc_;
    std::string tmpfile_;
    std::ofstream outfile_;
    std::ifstream infile_;

    long long filesize_;
    bool success_;

};

#endif // FILE_HANDLER_H
