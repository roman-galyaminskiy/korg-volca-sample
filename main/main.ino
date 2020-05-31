#include "mapper.hpp"
#include "definitions.hpp"

Mapper mapper;

void setup() {  
  SERIAL_MONITOR.begin(9600);
  // SERIAL_MONITOR.println("setup");
  mapper.setup();
}

void loop() {
  mapper.loop();
}
