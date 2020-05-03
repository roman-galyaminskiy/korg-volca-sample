#include <usbh_midi.h>
#include <usbhub.h>
#include <SPI.h>

#include "voice.hpp"  

MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, midi2);

Voice voice = Voice(&midi2, 1, 1);

void setup() {  
  voice.initialize();    
}

void loop() {  
  // Stop playing sample as you release button. Works best with long melodic/vocal samples
  // voice.choke_note_on();
  // delay(100);
  // voice.choke_note_off();

  // Randomize voice parameter value in selected range every time voice is triggered. Best works with extemely short looped segments, that sound like base waveforms
  // voice.randomize(PITCH_INT, 60, 120);
  // voice.trigger();

  // Compose a track, that consists of multiple short samples of the same length and choose random phrase every time the voice is triggered
  // voice.pick_random_phrase();
  // voice.trigger();

  // Play midi notes chromatically. For now only one octave is available.
  // voice.play_note(48);
  // delay(500);
  // voice.play_note(49);
  // delay(500);
  // voice.play_note(50);
  // delay(500);
  // voice.play_note(51);
  // delay(500);
  // voice.play_note(52);
  // delay(500);
  // voice.play_note(53);
  // delay(500);
  // voice.play_note(54);
  // delay(500);
  // voice.play_note(55);
  // delay(500);
  // voice.play_note(56);
  // delay(500);
  // voice.play_note(57);
  // delay(500);
  // voice.play_note(58);
  // delay(500);

  delay(2000);
}
