# korg-volca-sample

I like my Volca Sample, but most of its features really shine, when you use motion record with step sequencer. But I wanted to use it as an expressive **live** instrument and to have all that features under my fingertips instantly. So I decided to expand functionality of Korg Volca Sample using Arduino and MIDI controller. I hope, that this project will make some cool features more accesible and will inspire musicans to use this little box in new ways.

For now I implemented and tested multiple voice "modes":
## Play modes

### Trigger mode (default)
Play sample once to the end

### Gate mode
Stop playing sample as you release button. Works best with long melodic/vocal samples

```cpp

volca.choke_note_on(1);
delay(100);
volca.choke_note_off(1);

```

### Slice mode
Man, I wanted this feature so much. Alas you could not change sample assigned to voice via MIDI, but I figured out a workaround. Compose a track, that consists of multiple short samples of the same length and choose random phrase every time the voice is triggered. You could find in repo python script, that concatenates audio files in directory into one file.

```cpp

volca.pick_random_phrase(1);
volca.trigger(1);

```

### Chromatic mode
Play MIDI notes chromatically. For now only one octave (12 steps) is available.

```cpp

volca.play_note(1, 48);
delay(500);
volca.play_note(1, 49);
delay(500);
volca.play_note(1, 50);
delay(500);
volca.play_note(1, 51);
delay(500);
volca.play_note(1, 52);
delay(500);
volca.play_note(1, 53);
delay(500);
volca.play_note(1, 54);
delay(500);
volca.play_note(1, 55);
delay(500);
volca.play_note(1, 56);
delay(500);
volca.play_note(1, 57);
delay(500);
volca.play_note(1, 58);
delay(500);

```

## Control modes

### Velocity controlled parameters
Randomize voice parameter value in selected range every time voice is triggered. Best works with extemely short looped segments, that sound like base waveforms

```cpp

volca.randomize(1, PITCH_INT, 60, 120);
volca.trigger(1);

```

### Parameter value randomizer
Randomize voice parameter value in selected range every time voice is triggered. Best works with extemely short looped segments, that sound like base waveforms

```cpp

int random_voice = 0;
for (size_t i = 0; i < random(1, 3); i++)
{
  random_voice = random(3, 7);
  volca.randomize_parameter(random_voice, PITCH_INT, 60, 120);
  volca.randomize_parameter(random_voice, PAN, 0, 128);
  volca.trigger(random_voice);

  delay(random(100, 500));
}
```