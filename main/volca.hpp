#ifndef VOLCA_HPP
#define VOLCA_HPP

#include "MIDI.h"
#include "Arduino.h"
#include "HardwareSerial.h"

#include "voice.hpp"
#include "mediator.hpp"

typedef MIDI_NAMESPACE::MidiInterface \
  <MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MidiInterface;

class Volca : public Component {
  public:
    Volca(); // default constructor
    Volca(Mediator *m, MidiInterface* i);
    void initialize();

    void pad_on(uint8_t voice_index, uint8_t velocity);
    void pad_off(uint8_t voice_index);
    void note_on(uint8_t voice_index, uint8_t note, uint8_t velocity);
    void note_off(uint8_t voice_index, uint8_t note);

  private:
    uint8_t initialize_status = 0;
    Mediator *mediator;
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

    // Mediator
    void changed(uint8_t *event, uint8_t size);

    void test();
    void trigger(uint8_t voice_index);
    void choke_note_on(uint8_t voice_index);
    void choke_note_off(uint8_t voice_index);
    void randomize_parameter(uint8_t voice_index);
    void velocity_controll(uint8_t voice_index ,uint8_t velocity);
    void pick_random_phrase(uint8_t voice_index);
    void play_note(uint8_t voice_index, uint8_t note);
    
    // Polysynth
    uint8_t polysynth_flag = 1;
    int8_t keys_pressed[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

    int8_t press_key(int8_t note);
    int8_t release_key(int8_t note);


    
};

#endif // VOLCA_HPP
