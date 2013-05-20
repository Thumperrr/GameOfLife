#ifndef _LOGUTIL_H
#define _LOGUTIL_H

#include <iostream>
#include <fstream>
#include <streambuf>

namespace gol { namespace log
{
    class LogUtil
    {
        std::ofstream log {"debug_log.log", std::ios::out|std::ios::trunc}
                    , err {"debug_err.log", std::ios::out|std::ios::trunc}
                    , out {"debug_out.log", std::ios::out|std::ios::trunc};
        std::streambuf *clogbuf {log ? std::clog.rdbuf(log.rdbuf()) : std::clog.rdbuf()}
                     , *cerrbuf {err ? std::cerr.rdbuf(err.rdbuf()) : std::cerr.rdbuf()}
                     , *coutbuf {out ? std::cout.rdbuf(out.rdbuf()) : std::cerr.rdbuf()};
        LogUtil() noexcept
        {
        }
        LogUtil(LogUtil const &) = delete;
        LogUtil(LogUtil &&) = delete;
        LogUtil &operator=(LogUtil const &) = delete;
        LogUtil &operator=(LogUtil &&) = delete;

    public:
        static void EnableRedirection() noexcept
        {
            static LogUtil lu;
        }
        ~LogUtil()
        {
            std::clog.rdbuf(clogbuf), clogbuf = nullptr;
            std::cerr.rdbuf(cerrbuf), cerrbuf = nullptr;
            std::cout.rdbuf(coutbuf), coutbuf = nullptr;
        }

    };
}}

#endif