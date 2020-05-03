# korg-volca-sample

I like my Volca Sample, but most of its features really shine, when you use motion record with step sequencer. But I wanted to use it as an expressive **live** instrument and to have all that features under my fingertips instantly. So I decided to expand functionality of Korg Volca Sample using Arduino and MIDI controller. I hope, that this project will make some cool features more accesible and will inspire musicans to use this little box in new ways.

For now I implemented and tested multiple voice "modes":

## Choke mode
Stop playing sample as you release button. Works best with long melodic/vocal samples

'''cpp

voice.choke_note_on();
delay(100);
voice.choke_note_off();

'''

## Parameter value randomizer
Randomize voice parameter value in selected range every time voice is triggered. Best works with extemely short looped segments, that sound like base waveforms

'''cpp

voice.randomize(PITCH_INT, 60, 120);
voice.trigger();

''''

## Play random "sample" each time
Man, I wanted this feature so much. Alas you could not change sample assigned to voice via MIDI, but I figured out a workaround. Compose a track, that consists of multiple short samples of the same length and choose random phrase every time the voice is triggered. You could find in repo python script, that concatenates audio files in directory into one file.

'''cpp

voice.pick_random_phrase();
voice.trigger();

''''

## Chromatic mode
Play MIDI notes chromatically. For now only one octave (12 steps) is available.

'''cpp

voice.play_note(48);
delay(500);
voice.play_note(49);
delay(500);
voice.play_note(50);
delay(500);
voice.play_note(51);
delay(500);
voice.play_note(52);
delay(500);
voice.play_note(53);
delay(500);
voice.play_note(54);
delay(500);
voice.play_note(55);
delay(500);
voice.play_note(56);
delay(500);
voice.play_note(57);
delay(500);
voice.play_note(58);
delay(500);

'''