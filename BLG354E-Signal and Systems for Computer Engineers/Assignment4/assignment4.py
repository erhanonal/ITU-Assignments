#Erhan Onal 150170713

import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt




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
    alpha = (2 * np.pi * freqCutoff * samplingPeriod) / (2 * np.pi * freqCutoff * samplingPeriod + 1)
    filteredSignal[0] = alpha * inputSignal[0] + gain
    for i in range(1,inputSignal.shape[0]):
       filteredSignal[i] = alpha * inputSignal[i] + (1 -alpha) * filteredSignal[i-1] + gain
    return filteredSignal




def r2_dif_fft(s):
    
    def W(N , k):
        return np.exp((2 * -1j * np.pi * k)/N)
    
    N = len(s)
    halfN = int(N/2)
    p = []
    q = []
    for i in range(halfN):
       p.append(s[i] + s[i + halfN])
       #print(W(N, i))
       q.append((s[i] - s[i + halfN]) * W(N, i))
    
    P = []
    Q = []
    for k in range(halfN):
        summation = 0
        for n in range(halfN):
            summation += p[n] * W(halfN, n * k)
        P.append(summation)
        summation = 0
        for n in range(halfN):
            summation += q[n] * W(halfN, n * k)
        Q.append(summation)
    result = []
    for i in range(halfN):
        result.append(P[i])
        result.append(Q[i])
    return result

# Simple samples
fs_original, data_original = wavfile.read('Africa.wav') 
data_0Gain = lowPassFilterWithGain(data_original, 2000, fs_original, 0) 
data_5Gain = lowPassFilterWithGain(data_original, 2000, fs_original, 0)

for i in range(10, 31, 10):
  
    startPoint = i * fs_original
    fft_original = r2_dif_fft(data_original[startPoint : startPoint + 256])
    fft_0Gain = r2_dif_fft(data_0Gain[startPoint : startPoint + 256])
    fft_5Gain = r2_dif_fft(data_5Gain[startPoint : startPoint + 256])
    
    
    plt.subplot(211)
    plt.title('Spectrogram - Original Data - '+str(i)+' sec')
    plt.plot(np.log(fft_original))
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')
    plt.subplot(212)
    plt.specgram(np.log(fft_original), Fs= fs_original)
    plt.xlabel('Time')
    plt.ylabel('Frequency')
    plt.show()
    
    plt.subplot(211)
    plt.title('Spectrogram - LPF 0db Gain - '+str(i)+' sec')
    plt.plot(np.log(fft_0Gain))
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')
    plt.subplot(212)
    plt.specgram(np.log(fft_0Gain), Fs= fs_original)
    plt.xlabel('Time')
    plt.ylabel('Frequency')
    plt.show()
    
    plt.subplot(211)
    plt.title('Spectrogram - LPF 5db Gain - '+str(i)+' sec')
    plt.plot(np.log(fft_5Gain))
    plt.xlabel('Sample')
    plt.ylabel('Amplitude')
    plt.subplot(212)
    plt.specgram(np.log(fft_5Gain), Fs= fs_original)
    plt.xlabel('Time')
    plt.ylabel('Frequency')
    plt.show()






