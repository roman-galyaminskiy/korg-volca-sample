#include "dispatcher.hpp"
#include "definitions.hpp"

Dispatcher dispatcher;

void setup() {  
  SERIAL_MONITOR.begin(9600);
  // SERIAL_MONITOR.println("setup");
  dispatcher.setup();
}

void loop() {
  dispatcher.loop();
}
