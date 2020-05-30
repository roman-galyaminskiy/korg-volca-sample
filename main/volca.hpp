#ifndef VOLCA_HPP
#define VOLCA_HPP

#include "MIDI.h"
#include "Arduino.h"
#include "HardwareSerial.h"

#include "voice.hpp"
#include "component.hpp"

typedef MIDI_NAMESPACE::MidiInterface \
  <MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MidiInterface;

class Volca : public Component {
  public:
    Volca(); // default constructor
    Volca(Mediator *m, MidiInterface* i);
    void initialize();
    

  private:
    uint8_t initialize_status = 0;
    Mediator *mapper;
    MidiInterface* MIDI;

    Voice voices[10] = {
      Voice(1)
      ,Voice(2)
      ,Voice(3)
      ,Voice(4)
      ,Voice(5)
      ,Voice(6)
      ,Voice(7)
      ,Voice(8)
      ,Voice(9)
      ,Voice(10)
    };

    void trigger(uint8_t voice_index);
    void choke_note_on(uint8_t voice_index);
    void choke_note_off(uint8_t voice_index);
    void randomize_parameter(uint8_t voice_index);
    void velocity_controll(uint8_t voice_index ,uint8_t velocity);
    void pick_random_phrase(uint8_t voice_index);
    void play_note(uint8_t voice_index, uint8_t note);
    void test();
    
};

#endif // VOLCA_HPP
