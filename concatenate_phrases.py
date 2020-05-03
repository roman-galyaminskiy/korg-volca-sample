import sys
from os import listdir
import wave

# path_to_directory_with_samples = sys.argv[0]
path_to_directory_with_samples = "C:\\Users\\roman.galyaminskiy\\Downloads\\7450__blackie666__random-sound-effects\\candidates"

outfile = "test_sample2.wav"

data= []

for sample in listdir(path_to_directory_with_samples):
  # print(sample)
  with wave.open(path_to_directory_with_samples + '\\' + sample,'r') as f:
    frames = f.getnframes()
    rate = f.getframerate()
    duration = frames / float(rate)
    # print(duration)
    data.append( [f.getparams(), f.readframes(f.getnframes())] )


infiles = ["sound_1.wav", "sound_2.wav"]
outfile = "sounds.wav"


output = wave.open(path_to_directory_with_samples + '\\' + outfile, 'wb')
output.setparams(data[0][0])

for d in range(len(data)):
  output.writeframes(data[d][1])
  print(data[d][0])

  # if d == 2:
  #   break
output.close()