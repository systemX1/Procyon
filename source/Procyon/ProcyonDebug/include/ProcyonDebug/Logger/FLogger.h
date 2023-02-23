#pragma once

#ifndef PRDEBUG_LOGGER_FLOGGER_H
#define PRDEBUG_LOGGER_FLOGGER_H

#include <fmt/printf.h>
#include <fmt/ranges.h>


// include from https://github.com/MengRao/fmtlog
#define FMTLOG_HEADER_ONLY
#include <fmtlog/fmtlog.h>


namespace PrDebug::Logger {
    inline void InitLogger() noexcept {
        fmtlog::setLogLevel(fmtlog::INF);
        //fmtlog::setHeaderPattern("{HMSf} {g:<16} {l}[{t:<6}] ");
        //fmtlog::setLogFile(".\\log.log", false);
    }

    class FLogger {


    };

}

#endif
