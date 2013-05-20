#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>
#include <string>

namespace gol { namespace core 
{
    class exception : public std::exception
    {
        using std::exception::what;
    public:
        exception() noexcept {}
        virtual ~exception() noexcept {}
        exception(const exception &) = default;

        exception(const std::string &_e) noexcept : e(_e) {}
        virtual const char *what() noexcept { return e.c_str(); }

    private:
        std::string e;
    };
}}

#endif