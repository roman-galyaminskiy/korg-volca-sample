#include "mapper.hpp"
#include "definitions.hpp"

Mapper mapper;

void setup() {  
  SERIAL_MONITOR.begin(9600);
}

void loop() {
  // controller.listen();
  // Stop playing sample as you release button. Works best with long melodic/vocal samples
  // voice.choke_note_on();
  // delay(50);
  // voice.choke_note_off();
  // delay(100);
  // voice.choke_note_on();
  // delay(50);
  // voice.choke_note_off();
  // delay(200);
  // voice.choke_note_on();
  // delay(175);
  // voice.choke_note_off();
  // delay(125);
  // voice.choke_note_on();
  // delay(175);
  // voice.choke_note_off();
  // delay(125);
  // voice.choke_note_on();
  // delay(125);
  // voice.choke_note_off();
  // delay(275);
  // voice.choke_note_on();
  // delay(800);
  // voice.choke_note_off();

  // Randomize voice parameter value in selected range every time voice is triggered. Best works with extemely short looped segments, that sound like base waveforms

  // int random_voice = 0;
  // for (size_t i = 0; i < random(1, 3); i++)
  // {
  //   random_voice = random(3, 7);
  //   volca.randomize_parameter(random_voice, PITCH_INT, 60, 120);
  //   volca.randomize_parameter(random_voice, PAN, 0, 128);
  //   volca.trigger(random_voice);

  //   delay(random(100, 500));
  // }

  // Compose a track, that consists of multiple short samples of the same length and choose random phrase every time the voice is triggered
  // volca.pick_random_phrase(2);
  // volca.trigger(2);

  // Play midi notes chromatically. For now only one octave is available.
  // volca.play_note(1, 48);
  // delay(500);
  // volca.play_note(1, 49);
  // delay(500);
  // volca.play_note(1, 50);
  // delay(500);
  // volca.play_note(1, 51);
  // delay(500);
  // volca.play_note(1, 52);
  // delay(500);
  // volca.play_note(1, 53);
  // delay(500);
  // volca.play_note(1, 54);
  // delay(500);
  // volca.play_note(1, 55);
  // delay(500);
  // volca.play_note(1, 56);
  // delay(500);
  // volca.play_note(1, 57);
  // delay(500);
  // volca.play_note(1, 58);
  // delay(500);

  // delay(1000);
}
