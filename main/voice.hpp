#include "MIDI.h"
#include "Arduino.h"
#include "HardwareSerial.h"

#ifndef VOICE_HPP
#define VOICE_HPP

#define LEVEL 7
#define PAN 10
#define SAMPLE_START_POINT 40
#define SAMPLE_LENGTH 41
#define HI_CUT 42
#define SPEED 43
#define PITCH_INT 44
#define PITCH_ATTACK 45
#define PITCH_DECAY 46
#define AMPLITUDE_ATTACK 47
#define AMPLITUDE_DECAY 48

#define CHANNEL1_NOTE_ON 144
#define CHANNEL1_NOTE_OFF 128
#define CHANNEL1_CONTROL_CHANGE 176

typedef midi::MidiInterface<midi::SerialMIDI<HardwareSerial> > MidiInterface;

class Voice {
  public:
    Voice(); // default constructor
    Voice(MidiInterface* m, uint8_t i, uint8_t c);
    void initialize();
    void trigger();
    void choke_note_on();
    void choke_note_off();
    void randomize_parameter(uint8_t param, uint8_t from, uint8_t to);
    void velocity_controll(uint8_t param, uint8_t velocity);
    void pick_random_phrase();
    void play_note(uint8_t note);
    void test();

  private:
    uint8_t index;
    uint8_t channel;   
    uint8_t initialize_status = 0;
    MidiInterface* MIDI;
    
};

#endif // VOICE_HPP
