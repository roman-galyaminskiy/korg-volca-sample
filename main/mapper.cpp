#include "mapper.hpp"

Mapper::Mapper() {}

void Mapper::notify(Component *component, uint8_t *event, uint8_t size) {
  if (component == volca) {
    // SERIAL_MONITOR.println("volca");
  }
  else if (component == controller) {
    // SERIAL_MONITOR.println("controller");

    // SERIAL_MONITOR.print(event[0], DEC);
    // SERIAL_MONITOR.print(" ");
    // SERIAL_MONITOR.print(event[1], DEC);
    // SERIAL_MONITOR.print(" ");
    // SERIAL_MONITOR.print(event[2], DEC);
    // SERIAL_MONITOR.println();

    if (event[0] == CHANNEL1_NOTE_ON) {
      // SERIAL_MONITOR.print("Debug: pad index ");
      if (event[1] >= PAD1 && event[1] <= PAD8) {
        // SERIAL_MONITOR.print(event[1] - PAD1);
        volca->note_on(pad_to_voice_map[event[1] - PAD1]);
      }
      else if (event[1] >= PAD9 && event[1] <= PAD16) {
        // SERIAL_MONITOR.print(event[1] - PAD9);
        volca->note_on(pad_to_voice_map[event[1] + 8 - PAD9]);
      }
      // SERIAL_MONITOR.println();
    }
  }
}

void Mapper::setup() {
  volca->initialize();   
  controller->start();
  controller->enableExtendedMode();
}

void Mapper::loop() {
  controller->listen();  
}