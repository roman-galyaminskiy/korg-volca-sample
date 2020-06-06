#include "mapper.hpp"

void Mapper::changed(uint8_t *event, uint8_t size) {
  mediator->notify(this, event, size);
}

void Mapper::pad_pressed(uint8_t pad_index) {
  if (pad_selected == -1) {
    uint8_t notify_message[2];

    pad_selected = pad_index; 
    notify_message[0] = pad_selected;
    notify_message[1] = pad_to_voice_map[pad_selected];

    // draw voice selection screen for selected pad,
    // mark active voice for selected pad if exists
    changed(notify_message, 2);  
  }
  else {
    // Update mapping

    // this time pad_index repsents voie_index
    pad_to_voice_map[pad_selected] = pad_index;
    pad_selected = -1;

    // redraw pad selection screen
    changed(pad_to_voice_map, 16);
  }
}