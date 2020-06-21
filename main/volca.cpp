#include "volca.hpp"
#include "definitions.hpp"

Volca::Volca(Mediator* m, MidiInterface* i) { 
    this -> mediator = m;
    this -> MIDI = i;
}

void Volca::changed(uint8_t *event, uint8_t size) {
  mediator->notify(this, event, size);
}

void Volca::initialize() {
  MIDI->begin();
  initialize_status = 1;
  // SERIAL_MONITOR.println("DEBUG: MIDI initialized");
}

void Volca::pad_on(uint8_t voice_index, uint8_t velocity) {
  trigger(voice_index);
}

void Volca::note_on(uint8_t voice_index, uint8_t note, uint8_t velocity) {
  // SERIAL_MONITOR.print("DEBUG: note_on ");
  // SERIAL_MONITOR.print(voice_index, DEC);
  // SERIAL_MONITOR.print(", note: ");
  // SERIAL_MONITOR.println(note, DEC);

  if (polysynth_flag == 1) {
    voice_index = press_key(note);  
    choke_note_on(voice_index);  
    play_note(voice_index, note);
  }
  else {
    play_note(voice_index, note);
  }  
}

void Volca::note_off(uint8_t voice_index, uint8_t note) {
  // SERIAL_MONITOR.print("DEBUG: note_off ");
  // SERIAL_MONITOR.print(voice_index, DEC);
  // SERIAL_MONITOR.print(", note: ");
  // SERIAL_MONITOR.println(note, DEC);

  if (polysynth_flag == 1) {      
    voice_index = release_key(note);    
    choke_note_off(voice_index);
  }
}

void Volca::test() {
  // SERIAL_MONITOR.println("test");
}

void Volca::trigger(uint8_t voice_index) {
//  SERIAL_MONITOR.print("DEBUG: MIDI channel ");
//  SERIAL_MONITOR.print(voices[voice_index].get_channel());
//  SERIAL_MONITOR.println(" triggered");
  
  MIDI->sendNoteOn(42, 127, voices[voice_index].get_channel());
}

void Volca::choke_note_on(uint8_t voice_index) {
  uint8_t channel = voices[voice_index].get_channel();
  MIDI->sendControlChange(LEVEL, 127, channel);
  // SERIAL_MONITOR.print("DEBUG: Choke channel ");
  // SERIAL_MONITOR.print(channel, DEC);
  // SERIAL_MONITOR.println(" ON");
}

void Volca::choke_note_off(uint8_t voice_index) {
  uint8_t channel = voices[voice_index].get_channel();
  MIDI->sendControlChange(LEVEL, 0, channel);
  // SERIAL_MONITOR.print("DEBUG: Choke channel ");
  // SERIAL_MONITOR.print(channel, DEC);
  // SERIAL_MONITOR.println(" OFF");
}

void Volca::randomize_parameter(uint8_t voice_index) {
  uint8_t* range = voices[voice_index].get_parameter_range();

  MIDI->sendControlChange(voices[voice_index].get_parameter()
                          ,random(*range, *(range + 1))
                          ,voices[voice_index].get_channel());
}

void Volca::pick_random_phrase(uint8_t voice_index) {
  uint8_t channel = voices[voice_index].get_channel();
  uint8_t phrases_total = 10;
  static uint8_t prev_phrase_number = -1;
  
  uint8_t phrase_start_points[] =  {0, 14, 28, 42, 56, 70, 85, 99, 113, 127};
  
  uint8_t phrase_length = 39;
  //  SERIAL_MONITOR.print("DEBUG: phrase_length ");
  //  SERIAL_MONITOR.println(phrase_length);

  MIDI->sendControlChange(SAMPLE_LENGTH, phrase_length, channel);

  uint8_t phrase_number = random(0, phrases_total);
  do {
  phrase_number = random(0, phrases_total);
  } while (prev_phrase_number == phrase_number);
  
  //  SERIAL_MONITOR.print("DEBUG: phrase_number ");
  //  SERIAL_MONITOR.println(phrase_number);

  uint8_t phrase_start_point = phrase_start_points[phrase_number];
  //  SERIAL_MONITOR.print("DEBUG: phrase_start_point ");
  //  SERIAL_MONITOR.println(phrase_start_point);
   
  MIDI->sendControlChange(SAMPLE_START_POINT, phrase_start_point, channel);
}

void Volca::play_note(uint8_t voice_index, uint8_t note) {
  if (note >= 36 && note <= 85) {
    int8_t scale[] = {-48, -47, -45, -44, -43, -41, -40, -39, -37, -36, -35, -33
                      ,-32, -30, -27, -24, -21, -18, -16, -13,-11, -8, -5, -2 
                      ,0, 2, 5, 8, 11, 13, 16, 18, 21, 24, 27, 30
                      ,32, 33, 35, 36, 37, 39, 40, 41, 43, 44, 45, 47
                      ,48, 49};
    MIDI->sendControlChange(SPEED, 64 + scale[note - 36]
                            ,voices[voice_index].get_channel());
    trigger(voice_index);
  }
}
 
void Volca::velocity_controll(uint8_t voice_index, uint8_t velocity) {
  MIDI->sendControlChange(voices[voice_index].get_parameter() 
                          ,velocity
                          ,voices[voice_index].get_channel());
}

int8_t Volca::press_key(int8_t note) {
  for (size_t i; i < 8; i++) {
    if (keys_pressed[i] == -1) {
      keys_pressed[i] = note;
      return i;
    } 
  }  
}

int8_t Volca::release_key(int8_t note) {
  for (size_t i; i < 8; i++) {
    if (keys_pressed[i] == note) {
      keys_pressed[i] = -1;
      return i;
    } 
  }
}

