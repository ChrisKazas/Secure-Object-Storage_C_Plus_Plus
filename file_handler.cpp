/*
 *  SAW3- SecureObjStorage
 *
 *  March 15 2018
 *
 *  Chris Kazas
 *
 *  File wrapper Class for SecureObjStorage and Crypto class
 *
*/


#include "file_handler.h"
#include <algorithm> // remove & rename
#include <string>
#include <fstream>
#include <cstdlib>   // rand &  srand
#include <ctime>    // time

std::string genRand()
{
    // Generate ran string for file tempfile name
    std::srand(static_cast<unsigned>(std::time(0)));
    int r = std::rand();
    std::string str = std::to_string(r);
    return str;

}


File_handler::File_handler(const std::string& fileloc)
    :fileloc_(fileloc), success_(false)
{

    /*
     *   Opens 2 files - target file as infile_ and
     *   tmpfile as to outfile_ work with.
     *   Sets filesize_ data member
     *   Sets success_ data member to false
     *   Supports a basic guarantee
    */

    try
    {
        // infile_ is a std::ifstream data member of File_handler class
        infile_.open(fileloc_.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

        if(!infile_.is_open())
        {
            throw std::runtime_error("ERROR: File failed to open");
        }else  if (infile_.bad())
        {
           throw std::runtime_error("ERROR: I/O error while reading");
        }else if (infile_.fail())
        {
            throw std::runtime_error("ERROR: Unknown error occured \"File Failure\"");
        }

        // Set the filesize_data member
        filesize_ = infile_.tellg();

        //
        if(filesize_ %16 != 0)
        {
            infile_.close();
            outfile_.open(fileloc_, std::ios::out | std::ios::app);

            if(outfile_.is_open())
            {
                while(filesize_ %16 != 0)
                {
                    outfile_ << ' ';
                    ++filesize_;
                }
            }
            else
            {
                throw std::runtime_error("ERROR: File failed to open");
            }
            outfile_.close();
            infile_.open(fileloc_, std::ios::in|std::ios::binary);
        }

        infile_.seekg(0);

        // Generate random string for tmpfile name
        tmpfile_ = genRand();

        // outfile_ is a std::ofstream data member of File_handler class
        outfile_.open(tmpfile_.c_str(), std::ios::out|std::ios::binary|std::ios::trunc);
        if(!outfile_.is_open())
        {
            throw std::runtime_error("ERROR: Temp File failed to open");
        }else  if (outfile_.bad())
        {
           throw std::runtime_error("ERROR: I/O Error while reading");
        }else if (outfile_.fail())
        {
            throw std::runtime_error("ERROR: Unknown error occured \"File Failure\"");
        }
    }
    catch(std::exception& e)
    {
        throw std::runtime_error(e.what());
    }

}

// Deconstructor removes tmpfile_
File_handler::~File_handler()
{
    if(!success_)
    {
        try
        {
            std::remove(fileloc_.c_str());
            if(!std::remove(fileloc_.c_str()))
            {
                throw std::runtime_error("ERROR: Failed to remeve tmpFile!\n");

            }
        }
        catch(std::runtime_error& e)
        {
            throw std::runtime_error(e.what());
            throw std::runtime_error("Temporary file: \"" + getTmpFileLoc() +
                                     "\" needs to be removed manually to ensure integrity of security\n");
        }
    }

}

// read char* from file
void File_handler::read(unsigned char *buf, size_t len)
{
    infile_.read((char*)buf, len);
}

// write char* to file
void File_handler::write(unsigned char* buf, size_t len)
{
    outfile_.write((char*) buf, len);
}


// return the size of the file
long long File_handler::getFileSize()
{
    return filesize_;
}

// return the file locaction
std::string File_handler::getFileLocation()
{
    return fileloc_;
}

std::string File_handler::getTmpFileLoc()
{
    return tmpfile_;
}

// Swap temp file with file
void File_handler::complete()
{

    infile_.close();
    outfile_.close();

    try
    {

        std::remove(fileloc_.c_str());

        success_ = !std::rename(tmpfile_.c_str(), fileloc_.c_str());

        if(!success_)
        {
            throw std::runtime_error("ERROR: Unable to rename tmp file!");
        }
    }
    catch(std::exception& e)
    {
        throw std::runtime_error(e.what());
    }
}















