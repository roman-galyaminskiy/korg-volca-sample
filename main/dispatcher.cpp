#include "dispatcher.hpp"

Dispatcher::Dispatcher() {}

void Dispatcher::notify(Component *component, uint8_t *event, uint8_t size) {
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
    switch (event[0]) {
      case CHANNEL1_NOTE_ON:
        switch (event[1]) {
          // SERIAL_MONITOR.print("Debug: pad index ");
          // if (event[1] >= PAD1 && event[1] <= PAD8) {
            // SERIAL_MONITOR.print(event[1] - PAD1);
            // volca->note_on(pad_to_voice_map[event[1] - PAD1]);
          // }
          // else if (event[1] >= PAD9 && event[1] <= PAD16) {
            // SERIAL_MONITOR.print(event[1] - PAD9);
            // volca->note_on(pad_to_voice_map[event[1] + 8 - PAD9]);
          // }
          // SERIAL_MONITOR.println();
          case TOP_PLAY:
            top_play_button_pressed = 1;
            break;

          case BOTTOM_PLAY:
            bottom_play_button_pressed = 1;
            break;
        
          default:
            break;
        }
        break;          
      case CHANNEL1_NOTE_OFF:
        switch (event[1]) {
          case TOP_PLAY:
            top_play_button_pressed = 0;
            break;

          case BOTTOM_PLAY:
            bottom_play_button_pressed = 0;
            break;
        
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
  else if (component == mapper) {
    switch (size) {
      case 2:
        dispay_grid->draw_mapper_voice_selection(event[0], event[1]);
        break;
      case 16:
        dispay_grid->draw_mapper_pad_selection(event);
        break;
      default:
        break;
    }
  }
  else if (component == dispay_grid) {
    controller->change_pad_color(event[0], event[1]);
  }
}

void Dispatcher::setup() {
  volca->initialize();   
  controller->start();
  controller->enableExtendedMode();
}

void Dispatcher::loop() {
  controller->listen();  
}