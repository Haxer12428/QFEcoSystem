#pragma once
#include "QFDefines.h"
#include <fmt/core.h>

/* 
  QF Shutdown's work only in debug mode 
  If u want those to work define _qfDebugBuild
*/

/* QF Shutdown Message */
#ifdef _qfDebugBuild
    #define _qfShutdownMessage() { \
        fmt::print("\033[41m\033[1;33m [ {} ] \033[0m", "QF Shutting down, critical error occurred"); \
    }
#else 
    #define _qfShutdownMessage()
#endif 

/* QF Shutdown */
#ifdef _qfDebugBuild 
    #define _qfShutdown() { \
            _qfShutdownMessage(); \
            std::exit(EXIT_FAILURE); \
        }
#else 
  #define _qfShutdown()
#endif 