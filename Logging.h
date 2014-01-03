/****************************************************************************
*
*   Copyright (c) 2013 Dave Hylands     <dhylands@gmail.com>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License version 2 as
*   published by the Free Software Foundation.
*
*   Alternatively, this software may be distributed under the terms of BSD
*   license.
*
*   See README and COPYING for more details.
*
****************************************************************************/
/**
*
*   @file   Logging.h
*
*   @brief  A general purpose logging class, using printf-style formatting.
* 
*   This class makes use of the StrPrintf module to do all of the actual
*   formatting.
* 
*   Basic Usage:
* 
*   void setup()
*   {
*     Log.Init(Log.VERBOSE)
*     Log.Info("Informational log '%s'", "for testing");
*   }
* 
*   If no printing device is specified (when calling Log.Init), then
*   Serial with a baud rate of 38400 will be used.
* 
*   Debug, Warning and Error lines will be preceded by D: W:, and E:
*   respectively.
*
****************************************************************************/

#if !defined(LOGGING_H)
#define LOGGING_H

#include <stdarg.h>
#include "Print.h"

class Logging
{
public:
  enum Level
  {
    NO_OUTPUT,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
  };

  Logging()
    : _level(INFO),
      _printer(nullptr) {}

  void Init(Level defaultLevel, Print *printer=nullptr);

  void Debug(const char *fmt, ...);
  void Info(const char *fmt, ...);
  void Warning(const char *fmt, ...);
  void Error(const char *fmt, ...);

  void Printf(Level level, const char *fmt, ...);
  void vPrintf(Level level, const char *fmt, va_list args);

private:
  static int PrintFunc(void *param, int ch);

  Level _level;
  Print *_printer;
};

extern Logging Log;

#endif  // LOGGING_H
