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

#define TOP_PLAY 104
#define BOTTOM_PLAY 120
#define TRACK_LEFT 106
#define TRACK_RIGHT 107
#define SCENE_UP 104
#define SCENE_DOWN 105

#define KNOB1 21
#define KNOB2 22
#define KNOB3 23
#define KNOB4 24
#define KNOB5 25
#define KNOB6 26
#define KNOB7 27
#define KNOB8 28

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
#include "component.hpp"

class Controller: public USBH_MIDI, public Component {
//  using USBH_MIDI::USBH_MIDI;
  
public:
  Controller(Mediator *m, USB *u);
  void start();
  void listen();
  void enableExtendedMode();

private:
  Mediator *mapper;
  uint8_t extended_mode_enabled = 0;
  uint8_t key_reset_flag = 0;
};

#endif // CONTROLLER_HPP
