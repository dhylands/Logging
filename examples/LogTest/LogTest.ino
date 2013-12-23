#include "Logging.h"

void setup() {
  Log.Init(Logging::DEBUG);
  while (!Serial) {
    ;
  }

  Log.Info("In setup()");

  Log.Debug("debug message");
  Log.Info("info message");
  Log.Warning("warning message");
  Log.Error("Error message");
  Log.Printf(Logging::INFO, "Another way to log an info message");
}

static int count = 0;

void loop()
{
  if (count % 16 < 4) {
    Log.Info("info count = %d (decimal)", count);
  }
  else if (count % 16 < 8) {
    Log.Warning("warning count = 0%o (octal)", count);
  }
  else if (count % 16 < 12) {
    Log.Error("error count = 0x%x (hexadecimal)", count);
  }
  else {
    Log.Debug("debug count = 0b%b", count); 
  }
  count++; 
  delay(1000);
}
