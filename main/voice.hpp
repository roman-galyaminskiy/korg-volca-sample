#include "Arduino.h"

#ifndef VOICE_HPP
#define VOICE_HPP

#define NONE -1
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

#define CONTROL_CHANGE_MIN 0
#define CONTROL_CHANGE_MAX 127

// Play modes
// #define TRIGGER_MODE 1
// #define GATE_MODE 2
// #define SLICE_MODE 3
// #define STEP_SLICER_MODE 4
// #define RANDOM_SLICER_MODE 5
// #define MONO_CHROMATIC_MODE 6
// #define MONO_CHROMATIC_MODE 7

// Control modes
// #define DEFAULT_MODE 1
// #define VELOCITY_CONTROL_PARAMETER_MODE 2
// #define RANDOM_PARAMETER_MODE 3

class Voice {
  public:
    Voice(); // default constructor
    Voice(uint8_t c);

    uint8_t get_channel();
    uint8_t get_parameter();
    uint8_t* get_parameter_range();

  private:    
    // uint8_t play_mode = TRIGGER_MODE;
    // uint8_t control_mode = DEFAULT_MODE;

    uint8_t channel;
    uint8_t controlled_parameter = NONE;
    uint8_t controlled_parameter_range_from = CONTROL_CHANGE_MIN;
    uint8_t controlled_parameter_range_to = CONTROL_CHANGE_MAX;
};

#endif // VOICE_HPP
