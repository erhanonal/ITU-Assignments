"""
Erhan Önal 150170713

"""
import numpy as np
from math import pi
from scipy.io import wavfile




def lowPassFilterWithGain(inputSignal, freqCutoff, freqSampling, gain):
    """Low Pass Filter With Gain
        Arguments:
            inputSignal: Signal to filter
            freqCutoff: Cutoff frequency
            freqSampling: Sampling frequency
            gain: Gain in db
    """
    
    samplingPeriod = 1/freqSampling 
    filteredSignal = np.zeros_like(inputSignal)
    alpha = (2 * pi * freqCutoff * samplingPeriod) / (2 * pi * freqCutoff * samplingPeriod + 1)
    filteredSignal[0] = alpha * inputSignal[0] + gain
    for i in range(1,inputSignal.shape[0]):
       filteredSignal[i] = alpha * inputSignal[i] + (1 -alpha) * filteredSignal[i-1] + gain
    return filteredSignal



fs_africa, data_africa = wavfile.read('Africa.wav') #Read Africa.wav File

africa_filtered0 = lowPassFilterWithGain(data_africa, 2000, fs_africa, 0) #Create LPF with 0db gain
africa_filtered5 = lowPassFilterWithGain(data_africa, 2000, fs_africa, 5) #Create LPF with 5db gain


wavfile.write('Africa0dBGainLPF.wav', fs_africa, africa_filtered0) #Write results to wav files
wavfile.write('Africa5dBGainLPF.wav', fs_africa, africa_filtered5)


fs_winner, data_winner = wavfile.read('WinnerTakesAll.wav') #Read WinnerTakesAll.wav file

winner_filtered0 = lowPassFilterWithGain(data_winner, 2000, fs_winner, 0) #Create LPF with 0db gain
winner_filtered5 = lowPassFilterWithGain(data_winner, 2000, fs_winner, 5) #Create LPF with 5db gain
 

wavfile.write('WinnerTakesAll0dBGainLPF.wav', fs_winner, winner_filtered0) #Write results to wav files
wavfile.write('WinnerTakesAll5dBGainLPF.wav', fs_winner, winner_filtered5)

africaHPF = data_africa - africa_filtered0  #Calculate HPF by subtracting LPF from the original signal
winnerHPF = data_winner - winner_filtered0

wavfile.write('AfricaHPF.wav', fs_winner, africaHPF)   #Write HPF results to wav files
wavfile.write('WinnerTakesAllHPF.wav', fs_winner, winnerHPF)

