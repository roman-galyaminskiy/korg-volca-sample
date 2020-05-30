#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "MIDI.h"
#include <usbh_midi.h>
#include <usbhub.h>
#include <SPI.h>

#include "volca.hpp"
#include "controller.hpp" 
#include "component.hpp"

// As I'm unable to use this macro 
// 
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midi2);
// 
// inside a class, I had to dissect file serialMIDI.h  and redeclare classes needed:
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


public:
  Mapper();
  void notify();
  void notify(Component* component);

  // MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialmidi2(Serial3);
};

#endif // MAPPER_HPP

