#pragma once
#include <exception>

struct DirectoryNotExists : public std::exception{
    const char * what () const throw ()    {
        return "Directory Not Exists";
    }
};
struct PathIsNotDirectory : public std::exception{
    const char * what () const throw ()    {
        return "path is not directory";
    }
};