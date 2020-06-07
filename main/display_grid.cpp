#include "display_grid.hpp"

DisplayGrid::DisplayGrid(Mediator* m)
{ 
  this -> mediator = m;
}

void DisplayGrid::changed(uint8_t *event, uint8_t size) {
  mediator->notify(this, event, size);
}

void DisplayGrid::draw_play_mode() {
  uint8_t notify_array[2]; 
  notify_array[1] = YELLOW;

  for (size_t pad_index = 0; pad_index < 16; pad_index++) {
    notify_array[0] = pad_index;
    
    // Lit pad_index with color_code
    changed(notify_array, 2);
  }  
}

void DisplayGrid::draw_mapper_pad_selection(int8_t *pad_to_voice_map) {
  uint8_t notify_array[2]; 
  uint8_t color_code = 0;

  for (size_t pad_index = 0; pad_index < 16; pad_index++) {
    // SERIAL_MONITOR.print("Display grid: pad ");
    // SERIAL_MONITOR.print(pad_index, DEC);
    // SERIAL_MONITOR.print(" mapped to ");
    // SERIAL_MONITOR.println(pad_to_voice_map[pad_index], DEC);

    if (pad_to_voice_map[pad_index] == -1) {
      color_code = BLACK;
    }
    else {
      color_code = ORANGE;
    }
    notify_array[0] = pad_index;
    notify_array[1] =  color_code;

    // Lit pad_index with color_code
    changed(notify_array, 2);
  }    
}

void DisplayGrid::draw_mapper_voice_selection(uint8_t _pad_index, uint8_t _voice_index) {
  uint8_t notify_array[2]; 
  uint8_t color_code = 0;

  for (size_t pad_index = 0; pad_index < 16; pad_index++) {
    if (pad_index < 10) {
      if (pad_index == _voice_index) {
        color_code = GREEN;
      }
      else {
        color_code = YELLOW;
      }
    }
    else {
      color_code = BLACK;
    }

    notify_array[0] = pad_index;
    notify_array[1] =  color_code;

    // Lit pad_index with color_code
    changed(notify_array, 2);
  }    
}