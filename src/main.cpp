#include <iostream>
#include <fstream>
#include <streambuf>
#include <typeinfo>

#include "Application.hpp"
#include "core/Exception.hpp"
#include "log/LogUtil.hpp"

int main()
{
    gol::log::LogUtil::EnableRedirection();

    try
    {
        return gol::Application().Exec();
    }
    catch(gol::core::exception &e)
    {
        std::clog << typeid(e).name() << " caught in main: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}