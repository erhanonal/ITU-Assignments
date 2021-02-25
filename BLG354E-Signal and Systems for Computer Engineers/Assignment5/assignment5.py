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


startPoint = 10 * fs_original
fft_10 = r2_dif_fft(data_original[startPoint : startPoint + 256])

startPoint = 20 * fs_original
fft_20 = r2_dif_fft(data_original[startPoint : startPoint + 256])

startPoint = 30 * fs_original
fft_30 = r2_dif_fft(data_original[startPoint : startPoint + 256])

all_fft = []
index = [*range(0, 2360154, 256)]
for i in index:
    tmp_fft = r2_dif_fft(data_original[i : i + 256])
    if(len(tmp_fft) == 256): 
        all_fft.append(tmp_fft)
    
conv_10 = []
conv_20 = []
conv_30 = []
for part in all_fft:
    tmp_10 = [a*b for a,b in zip(part, fft_10)]
    conv_10.append(tmp_10)
    
    tmp_20 = [a*b for a,b in zip(part, fft_20)]
    conv_20.append(tmp_20)
    
    tmp_30 = [a*b for a,b in zip(part, fft_30)]
    conv_30.append(tmp_30)


avg_10 = []
avg_20 = []
avg_30 = []
for i in range(9219):
    tmp_10 = 0
    tmp_20 = 0
    tmp_30 = 0
    for j in range(256):
        tmp_10 += conv_10[i][j]
        tmp_20 += conv_20[i][j]
        tmp_30 += conv_30[i][j]
    avg_10.append(tmp_10/256)
    avg_20.append(tmp_20/256)
    avg_30.append(tmp_30/256)

plt.plot(avg_10)
plt.title("Conv_10")
plt.show()

plt.plot(avg_20)
plt.title("Conv_20")
plt.show()

plt.plot(avg_30)
plt.title("Conv_30")
plt.show()

plt.plot(avg_10[1522:1922])
plt.title("Conv_10")
plt.show()

plt.plot(avg_20[3245:3645])
plt.title("Conv_20")
plt.show()

plt.plot(avg_30[3832:4232])
plt.title("Conv_30")
plt.show()

"""
 
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
    
"""