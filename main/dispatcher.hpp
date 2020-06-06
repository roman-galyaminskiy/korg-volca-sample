#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#define PLAY_MODE 0
#define MENU_MODE 1
#define MAPPER_MODE 2

#include "MIDI.h"
#include <usbh_midi.h>
#include <usbhub.h>
#include <SPI.h>

#include "mediator.hpp"

#include "volca.hpp"
#include "controller.hpp" 
#include "mapper.hpp" 
#include "display_grid.hpp" 

// As I'm unable to use this macro 
// 
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midi2);
// 
// inside a class, so I had to dissect file serialMIDI.h  and redeclare classes needed:
// 
// #define MIDI_CREATE_INSTANCE(Type, SerialPort, Name)  \
//   MIDI_NAMESPACE::SerialMIDI<Type> serial##Name(SerialPort);\
//   MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<Type>> Name((MIDI_NAMESPACE::SerialMIDI<Type>&)serial##Name);

typedef MIDI_NAMESPACE::SerialMIDI<HardwareSerial> SerialMIDI;
typedef MIDI_NAMESPACE::MidiInterface<SerialMIDI> MidiInterface;

class Dispatcher: public Mediator {
private:  

  SerialMIDI serialmidi2 = SerialMIDI(Serial3);
  MidiInterface midi2 = MidiInterface((SerialMIDI&)serialmidi2);
  USB Usb;

  Volca* volca = new Volca(this, &midi2);
  Controller* controller = new Controller(this, &Usb);  
  Mapper* mapper = new Mapper(this);
  DisplayGrid* dispay_grid = new DisplayGrid(this);

  uint8_t mode = PLAY_MODE;
  uint8_t top_play_button_pressed = 0;
  uint8_t bottom_play_button_pressed = 0;

public:
  Dispatcher();
  void notify(Component *component, uint8_t *event, uint8_t size);
  void setup();
  void loop();

  // MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialmidi2(Serial3);
};

#endif // DISPATCHER_HPP

