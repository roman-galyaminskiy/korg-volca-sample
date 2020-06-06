#include "display_grid.hpp"

void DisplayGrid::changed(uint8_t *event, uint8_t size) {
  mediator->notify(this, event, size);
}

void DisplayGrid::draw_mapper_pad_selection(uint8_t *pad_to_voice_map) {
  uint8_t notify_array[2]; 
  uint8_t color_code = 0;

  for (size_t pad_index = 0; pad_index < sizeof(pad_notes)/sizeof(uint8_t); pad_index++) {
    if (pad_to_voice_map[pad_index] == -1) {
      color_code = BLACK;
    }
    else {
      color_code = ORANGE;
    }
    notify_array[0] = pad_notes[pad_index];
    notify_array[1] =  color_code;

    // Lit pad_index with color_code
    changed(notify_array, 2);
  }    
}

void DisplayGrid::draw_mapper_voice_selection(uint8_t pad_index, uint8_t _voice_index) {
  uint8_t notify_array[2]; 
  uint8_t color_code = 0;

  for (size_t voice_index = 0; voice_index < 10; voice_index++) {
    if (voice_index == _voice_index) {
      color_code = GREEN;
    }
    else {
      color_code = YELLOW;
    }
    notify_array[0] = pad_notes[voice_index];
    notify_array[1] =  color_code;

    // Lit pad_index with color_code
    changed(notify_array, 2);
  }    
}