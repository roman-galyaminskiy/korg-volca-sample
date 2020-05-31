#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "MIDI.h"
#include <usbh_midi.h>
#include <usbhub.h>
#include <SPI.h>

#include "volca.hpp"
#include "controller.hpp" 
#include "mediator.hpp"

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

class Mapper: public Mediator 
{
private:  

  SerialMIDI serialmidi2 = SerialMIDI(Serial3);
  MidiInterface midi2 = MidiInterface((SerialMIDI&)serialmidi2);
  USB Usb;

  Volca* volca = new Volca(this, &midi2);
  Controller* controller = new Controller(this, &Usb);

  uint8_t pad_to_voice_map[16] = {
    0, 0, 4, 2, 2, 4, 0, 0,
    0, 1, 3, 2, 2, 3, 1, 0
  };

public:
  Mapper();
  void notify(Component *component, uint8_t *event, uint8_t size);
  void setup();
  void loop();

  // MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialmidi2(Serial3);
};

#endif // MAPPER_HPP

