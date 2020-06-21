#include "dispatcher.hpp"

Dispatcher::Dispatcher() {}

void Dispatcher::notify(Component *component, uint8_t *event, uint8_t size) {
  int8_t voice_index = -1;
  
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
        // SERIAL_MONITOR.print("Debug: pad index ");
        if (event[1] < PAD1) {
          // SERIAL_MONITOR.print("Debug: key on");
          volca->note_on(event[0], event[1], event[2]);
        }
        else if (event[1] >= PAD1 && event[1] <= PAD8) {
          // SERIAL_MONITOR.println(event[1] - PAD1, DEC);
          switch (mode) {
            case MAPPER_MODE:
              mapper->pad_pressed(event[1] - PAD1);
              break;
            case MENU_MODE:
              break;
            default: // PLAY_MODE
              controller->change_pad_color(event[1] - PAD1, RED);
              voice_index = mapper->get_voice_index(event[1] - PAD1);
              volca->pad_on(voice_index, event[2]);
              break;
          }          
        }
        else if (event[1] >= PAD9 && event[1] <= PAD16) {
          // SERIAL_MONITOR.println(event[1] - PAD9 + 8, DEC);
          switch (mode) {
            case MAPPER_MODE:
              mapper->pad_pressed(event[1] - PAD9 + 8);
              break;
            case MENU_MODE:
              break;
            default: // PLAY_MODE
              controller->change_pad_color(event[1] - PAD9 + 8, RED);
              voice_index = mapper->get_voice_index(event[1] - PAD9 + 8);
              volca->pad_on(voice_index, event[2]);
              break;
          }
        }
        else if (event[1] == TOP_PLAY) {
          top_play_button_pressed = 1;
          controller->change_button_color(TOP_PLAY, RED);
        }
        else if (event[1] == BOTTOM_PLAY) {
          bottom_play_button_pressed = 1;
          controller->change_button_color(BOTTOM_PLAY, RED);

          if (top_play_button_pressed == 1) {
            mode = MAPPER_MODE;
            mapper->enter();
          }
          else {
            mode = PLAY_MODE;
            mapper->exit();
            display_grid->draw_play_mode();
          }
        }
        break;          
      case CHANNEL1_NOTE_OFF:
        // SERIAL_MONITOR.print("Debug: pad index ");
        if (event[1] < PAD1) {
          // SERIAL_MONITOR.print("Debug: key off");
          volca->note_off(event[0], event[1]);
        }
        else if (event[1] >= PAD1 && event[1] <= PAD8) {
          // SERIAL_MONITOR.println(event[1] - PAD1, DEC);
          switch (mode) {
            case MAPPER_MODE:
              break;
            case MENU_MODE:
              break;
            default: // PLAY_MODE              
              controller->change_pad_color(event[1] - PAD1, YELLOW);
              break;
          }          
        }
        else if (event[1] >= PAD9 && event[1] <= PAD16) {
          // SERIAL_MONITOR.println(event[1] - PAD9 + 8, DEC);
          switch (mode) {
            case MAPPER_MODE:
              break;
            case MENU_MODE:
              break;
            default: // PLAY_MODE              
              controller->change_pad_color(event[1] - PAD9 + 8, YELLOW);
              break;
          }
        }
        else if (event[1] == TOP_PLAY) {
          top_play_button_pressed = 0;
          if (mode != MAPPER_MODE) {
            controller->change_button_color(TOP_PLAY, BLACK);
          }
        }
        else if (event[1] == BOTTOM_PLAY) {
          bottom_play_button_pressed = 0;
          if (mode != MAPPER_MODE) {
            controller->change_button_color(BOTTOM_PLAY, BLACK);
          }
        }
        break;
    }
  }
  else if (component == mapper) {
    // SERIAL_MONITOR.print("Dispatching mapper event: size ");
    // SERIAL_MONITOR.println(size);
    switch (size) {
      case 2:
        display_grid->draw_mapper_voice_selection(event[0], event[1]);
        break;
      case 16:
        display_grid->draw_mapper_pad_selection(event);
        break;
      default:
        break;
    }
  }
  else if (component == display_grid) {
    controller->change_pad_color(event[0], event[1]);
  }
}

void Dispatcher::setup() {
  volca->initialize();   
  controller->start();
  controller->enableExtendedMode();
  display_grid->draw_play_mode();
}

void Dispatcher::loop() {
  controller->listen();  
}