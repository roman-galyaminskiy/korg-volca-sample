#include "voice.hpp"

Voice::Voice(MidiInterface* m, uint8_t i, uint8_t c)
{ 
    this -> MIDI = m;
    this -> index = i;
    this -> channel = c;
}

void Voice::initialize() {
  MIDI->begin();
  initialize_status = 1;
//  Serial.print("Voice ");
//  Serial.print(channel);
//  Serial.println(" initialized");
}

void Voice::test() {
      Serial.println("test");
    }

void Voice::trigger() {
//  Serial.print("Voice ");
//  Serial.print(channel);
//  Serial.println(" trigger");
  
//  if (initialize_status == 0) {
//   initialize();
//  }
  
  MIDI->sendNoteOn(42, 127, channel);
//  uint8_t velocity_message[3] = {CHANNEL1_NOTE_ON, 41, 127};
//  Serial2.write(velocity_message, 3);
}

void Voice::choke_note_on() {
  MIDI->sendControlChange(LEVEL, 127, channel);
  MIDI->sendNoteOn(42, 127, channel);
  
}

void Voice::choke_note_off() {
  MIDI->sendControlChange(LEVEL, 0, channel);
  MIDI->sendNoteOn(42, 127, channel);  
}

void Voice::randomize_parameter(uint8_t param, uint8_t from, uint8_t to) {
   MIDI->sendControlChange(param, random(from, to), channel);
}

void Voice::pick_random_phrase() {
   uint8_t phrases_total = 10;
   static uint8_t prev_phrase_number = -1;
   
   uint8_t phrase_start_points[] =  {0, 14, 28, 42, 56, 70, 85, 99, 113, 127};
   
   uint8_t phrase_length = 39;
   Serial.print("phrase_length ");
   Serial.println(phrase_length);
   MIDI->sendControlChange(SAMPLE_LENGTH, phrase_length, channel);

   uint8_t phrase_number = random(0, phrases_total);
   do {
    phrase_number = random(0, phrases_total);
   } while (prev_phrase_number == phrase_number);
   
   Serial.print("phrase_number ");
   Serial.println(phrase_number);

   uint8_t phrase_start_point = phrase_start_points[phrase_number];
   Serial.print("phrase_start_point ");
   Serial.println(phrase_start_point);
   
   MIDI->sendControlChange(SAMPLE_START_POINT, phrase_start_point, channel);
}

void Voice::play_note(uint8_t note) {
  uint8_t scale[] = {0, 2, 5, 8, 11, 13, 16, 18, 21, 24, 27, 30};
  Serial.print("note - 60 ");
  Serial.println(note - 60);
  MIDI->sendControlChange(SPEED, 64 + scale[note - 48], channel);
  trigger();
}
 
void Voice::velocity_controll(uint8_t param, uint8_t velocity) {
   MIDI->sendControlChange(param, velocity, channel);
}
