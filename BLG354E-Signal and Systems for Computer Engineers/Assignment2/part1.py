
#######################
#Erhan Önal 150170713

import numpy as np



def convolution(x,h):
    size=max(len(x), len(h))
  #  print(x.shape)
    if(len(x)>len(h)):
        result = np.zeros(x.shape)
        result[:h.shape[0]] = h
        h=result
    if(len(h)>len(x)):
        result = np.zeros(h.shape)
        result[:x.shape[0]] = x
        x=result
    result=np.zeros(size*2-1)
    for n in range(len(result)):
        tmp=0
        for k in range(-len(h)+1,len(h)+len(x)):
            #print(k)
            if (n-k)<len(h) and (n-k)>=0 and k<len(x) and k>=0 :
              #  print("k: ",k)
              #  print(x[k]*h[n-k])
                tmp+=x[k]*h[n-k]
        result[n]=tmp  
        
    return result




#a
x=np.array([0,1,2,3])
h=np.array([1,1,1,1])
print(convolution(x,h))




#b
x=np.array([0,1,2,3])
h=np.array([1])
print(convolution(x,h))



#c
x=np.array([0,1,2,3])
h=np.array([0,1,2,3])
print(convolution(x,h))



#d
x=np.array([1,0,1,2,3])
h=np.array([1,2])
print(convolution(x,h))

