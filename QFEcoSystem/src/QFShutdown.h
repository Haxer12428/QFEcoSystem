#pragma once
#include <stdexcept>
#include "QFDefines.h"
#include <fmt/core.h>

/* 
  check QFDefines.h for better assert||shutdown debugging 'settings' 
*/

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

//#define _qfShutdownWithRuntimeError

#ifdef _qfShutdownWithRuntimeError
  #define _qfShutdownExit() do { \
    throw std::runtime_error("qfshutdown"); \
  } while(0) 
#else 
  #define _qfShutdownExit() do { \
       std::exit(EXIT_FAILURE); \
  } while(0) 
#endif 

/* QF Shutdown */
#ifdef _qfDebugBuild 
    #define _qfShutdown() do { \
            _qfShutdownMessage(); \
            _qfShutdownExit(); \
        } while (0)
#else 
  #define _qfShutdown()
#endif 