#include "volca.hpp"

Volca::Volca(MidiInterface* m)
{ 
    this -> MIDI = m;
}

void Volca::initialize() {
  MIDI->begin();
  initialize_status = 1;
//  Serial.println("DEBUG: MIDI initialized");
}

void Volca::test() {
  Serial.println("test");
}

void Volca::trigger(uint8_t voice_channel) {
//  Serial.print("DEBUG: MIDI channel ");
//  Serial.print(voice_channel);
//  Serial.println(" triggered");
  
  MIDI->sendNoteOn(42, 127, voice_channel);
}

void Volca::choke_note_on(uint8_t voice_channel) {
  MIDI->sendControlChange(LEVEL, 127, voice_channel);
  MIDI->sendNoteOn(42, 127, voice_channel);
  
}

void Volca::choke_note_off(uint8_t voice_channel) {
  MIDI->sendControlChange(LEVEL, 0, voice_channel);
  MIDI->sendNoteOn(42, 127, voice_channel);  
}

void Volca::randomize_parameter(uint8_t voice_channel
                                ,uint8_t param
                                ,uint8_t from
                                ,uint8_t to) {
  MIDI->sendControlChange(param, random(from, to), voice_channel);
}

void Volca::pick_random_phrase(uint8_t voice_channel) {
  uint8_t phrases_total = 10;
  static uint8_t prev_phrase_number = -1;
  
  uint8_t phrase_start_points[] =  {0, 14, 28, 42, 56, 70, 85, 99, 113, 127};
  
  uint8_t phrase_length = 39;
  //  Serial.print("DEBUG: phrase_length ");
  //  Serial.println(phrase_length);

  MIDI->sendControlChange(SAMPLE_LENGTH, phrase_length, voice_channel);

  uint8_t phrase_number = random(0, phrases_total);
  do {
  phrase_number = random(0, phrases_total);
  } while (prev_phrase_number == phrase_number);
  
  //  Serial.print("DEBUG: phrase_number ");
  //  Serial.println(phrase_number);

  uint8_t phrase_start_point = phrase_start_points[phrase_number];
  //  Serial.print("DEBUG: phrase_start_point ");
  //  Serial.println(phrase_start_point);
   
  MIDI->sendControlChange(SAMPLE_START_POINT, phrase_start_point, voice_channel);
}

void Volca::play_note(uint8_t voice_channel, uint8_t note) {
  uint8_t scale[] = {0, 2, 5, 8, 11, 13, 16, 18, 21, 24, 27, 30};
  // Serial.print("DEBUG: note - 60 ");
  // Serial.println(note - 60);
  MIDI->sendControlChange(SPEED, 64 + scale[note - 48], voice_channel);
  trigger(voice_channel);
}
 
void Volca::velocity_controll(uint8_t voice_channel, uint8_t param, uint8_t velocity) {
  MIDI->sendControlChange(param, velocity, voice_channel);
}
