#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#define PAD1 96
#define PAD2 97
#define PAD3 98
#define PAD4 99
#define PAD5 100
#define PAD6 101
#define PAD7 102
#define PAD8 103
#define PAD9 112
#define PAD10 113
#define PAD11 114
#define PAD12 115
#define PAD13 116
#define PAD14 117
#define PAD15 118
#define PAD16 119

#define BLACK 0
#define RED 15
#define ORANGE 19
#define YELLOW 21
#define GREEN 24

#define CHANNEL1_NOTE_ON 144
#define CHANNEL1_NOTE_OFF 128
#define CHANNEL1_CONTROL_CHANGE 176

#include <usbh_midi.h>
#include <usbhub.h>
#include <SPI.h>

#include "volca.hpp"
#include "definitions.hpp"
#include "mediator.hpp"

class Controller: public USBH_MIDI, public Component {
//  using USBH_MIDI::USBH_MIDI;
  
public:
  Controller(Mediator *m, USB *u);
  void start();
  void listen();
  void enableExtendedMode();  
  void change_pad_color(int8_t pad_note, uint8_t color_code);

private:
  Mediator *mapper;
  uint8_t extended_mode_enabled = 0;
  uint8_t key_reset_flag = 0;

  const uint8_t pad_notes[16] = {
    96, 97, 98, 99, 100, 101, 102, 103,
    112, 113, 114, 115, 116, 117, 118, 119
  };

  void changed(uint8_t *event, uint8_t size);
};

#endif // CONTROLLER_HPP
