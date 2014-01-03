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
*   @file   Logging.cpp
*
*   @brief  A general purpose logging class, using printf-style formatting.
*
****************************************************************************/

#include "Logging.h"
#include "StrPrintf.h"
#include "Arduino.h"

Logging Log;

void Logging::Init(Logging::Level defaultLevel, Print *printer)
{
  _level = defaultLevel;
  if (printer) {
    _printer = printer; 
  } else {
    _printer = &Serial;
    Serial.begin(38400);
  }
}

void Logging::Debug(const char *fmt, ...)
{
  if (_level >= DEBUG) {
    va_list args; 

    va_start(args, fmt);
    vPrintf(DEBUG, fmt, args);
    va_end(args);
  }
}
void Logging::Info(const char *fmt, ...)
{
  if (_level >= INFO) {
    va_list args; 

    va_start(args, fmt);
    vPrintf(INFO, fmt, args);
    va_end(args);
  }
}

void Logging::Warning(const char *fmt, ...)
{
  if (_level >= WARNING) {
    va_list args; 

    va_start(args, fmt);
    vPrintf(WARNING, fmt, args);
    va_end(args);
  }
}

void Logging::Error(const char *fmt, ...)
{
  if (_level >= ERROR) {
    va_list args; 

    va_start(args, fmt);
    vPrintf(ERROR, fmt, args);
    va_end(args);
  }
}

void Logging::Printf(Logging::Level level, const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  vPrintf(level, fmt, args);
  va_end(args);
}

void Logging::vPrintf(Logging::Level level, const char *fmt, va_list args)
{
  if (!_printer) {
    return;
  }
  char levelChar[] = "\0EWID"; 
  if (level < sizeof(levelChar) && levelChar[level] != '\0') {
    PrintFunc(_printer, levelChar[level]);
    PrintFunc(_printer, ':');
    PrintFunc(_printer, ' ');
  }
  vStrXPrintf(PrintFunc, _printer, fmt, args); 
  PrintFunc(_printer, '\n');
}

// static
int Logging::PrintFunc(void *param, int ch)
{
  if (ch == '\n') {
    static_cast<Print*>(param)->print('\r'); 
  }
  static_cast<Print*>(param)->print(static_cast<char>(ch)); 
  return 1;
}
