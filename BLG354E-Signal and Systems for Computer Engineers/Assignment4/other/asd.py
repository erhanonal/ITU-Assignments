import numpy as np
import math


def bit_reverse_traverse(a):
    n = a.shape[0]
    assert(not n&(n-1) ) # assert that n is a power of 2

    if n == 1:
        yield a[0]
    else:
        even_index = arange(n/2)*2
        odd_index = arange(n/2)*2 + 1
        for even in bit_reverse_traverse(a[even_index]):
            yield even
        for odd in bit_reverse_traverse(a[odd_index]):
            yield odd
            
def get_bit_reversed_list(l):
    n = len(l)

    indexs = arange(n)
    b = []
    for i in bit_reverse_traverse(indexs):
        b.append(l[i])

    return b
N = 32

x = np.random.randn( N)

x_original = x
x_hat = np.zeros_like(x)

numberOfStages = int(math.log2(N))
omega = np.exp(-1j * 2 * math.pi / N);

mulCount = 0
sumCount = 0
M = int(N / 2)

for i in range(1,(numberOfStages+1)):
    for k in range(0, int(N / (2**(i-1))) , N ):
        for n in range(M):
            a = x[n + k ] + x[n + k + M ];
            b = np.multiply((x[n + k ] - x[n + k + M ]), omega ** (2**(i-1) * n))
            x[n+k] = a
            x[n+k+M] = b
            mulCount+=4
            sumCount+=6
    
    M=int(M/2)
    
x_hat = x