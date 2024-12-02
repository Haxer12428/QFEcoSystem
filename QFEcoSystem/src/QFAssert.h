#pragma once
#include <fmt/core.h>
#include "QFDefines.h"
#include "QFShutdown.h"

/* This only works in debug mode 
  If you want it to work in release mode define _qfDebugBuild
*/

#ifdef _qfDebugBuild 
  #define _qfAssert(condition, message)   \
      do {                                  \
          if (!(condition)) {               \
              fmt::print( \
                "\033[1;31m[ {} ]\033[0m\n\033[1;33m Function: {}\n Expression: {}\n Why: {}\n File: {}\n Line: {}\n\033[0m", \
                "_qfAssert Assertion failed",     \
                __FUNCTION__, \
                #condition,                \
                message,                  \
                __FILE__,                 \
                __LINE__);                  \
            _qfShutdown();              \
          }                                 \
      } while (false)
#else 
  #define _qfAssert(condition, message)   \
        do { } while (false)  
#endif 

