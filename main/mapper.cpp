#include "mapper.hpp"

Mapper::Mapper(Mediator* m)
{ 
    this -> mediator = m;
}

void Mapper::changed(uint8_t *event, uint8_t size) {
  mediator->notify(this, event, size);
}

void Mapper::enter() {
  // redraw pad selection screen
  entered = 1;
  changed(pad_to_voice_map, 16);
}

void Mapper::exit() {
  entered = 0;
}

void Mapper::pad_pressed(uint8_t pad_index) {
  int8_t voice_index = -1;
  
  if (entered == 1) {
    // SERIAL_MONITOR.print("Mapper: pad_index ");
    // SERIAL_MONITOR.println(pad_index, DEC);
    // SERIAL_MONITOR.println();
    
    // SERIAL_MONITOR.print("Mapper: pad_selected ");
    // SERIAL_MONITOR.println(pad_selected, DEC);

    if (pad_selected == -1) {
      uint8_t notify_message[2];

      pad_selected = pad_index; 
      notify_message[0] = pad_selected;
      notify_message[1] = pad_to_voice_map[pad_selected];

      // SERIAL_MONITOR.println("Mapper: draw voice selection screen");

      // draw voice selection screen for selected pad,
      // mark active voice for selected pad if exists
      changed(notify_message, 2);  
    }
    else {
      // Update mapping

      // this time pad_index repsents voie_index
      if (pad_index < 10) {
        pad_to_voice_map[pad_selected] = pad_index;
      }
      else {
        pad_to_voice_map[pad_selected] = -1;
      }
      
      pad_selected = -1;

      // SERIAL_MONITOR.println("Mapper: draw pad selection screen");

      // redraw pad selection screen
      changed(pad_to_voice_map, 16);
    }
  }
}

int8_t Mapper::get_voice_index(uint8_t pad_index) {
  return pad_to_voice_map[pad_index];
}