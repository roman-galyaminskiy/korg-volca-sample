#ifndef VOLCA_HPP
#define VOLCA_HPP

#include "MIDI.h"
#include "Arduino.h"
#include "HardwareSerial.h"

#include "voice.hpp"

typedef midi::MidiInterface<midi::SerialMIDI<HardwareSerial> > MidiInterface;

class Volca {
  public:
    Volca(); // default constructor
    Volca(MidiInterface* m);
    void initialize();
    
    void trigger(uint8_t voice_channel);
    void choke_note_on(uint8_t voice_channel);
    void choke_note_off(uint8_t voice_channel);
    void randomize_parameter(uint8_t voice_channel 
                            ,uint8_t param
                            ,uint8_t from
                            ,uint8_t to);
    void velocity_controll(uint8_t voice_channel
                            ,uint8_t param
                            ,uint8_t velocity);
    void pick_random_phrase(uint8_t voice_channel);
    void play_note(uint8_t voice_channel, uint8_t note);
    void test();

  private:
    uint8_t initialize_status = 0;
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
    
};

#endif // VOLCA_HPP
