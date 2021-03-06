import numpy as np
import matplotlib.pyplot as plt

y_h = []
with open("SetState.txt","r") as f:
    for line in f:
        y_h.append([float(x) for x in line.split()])
y_h = np.array(y_h)


'''y_h_1 = []
with open("Discrete_10.txt","r") as f:
    for line in f:
        y_h_1.append([float(x) for x in line.split()])
y_h_1 = np.array(y_h_1)'''

x = np.arange(100, 2010100, 10000)

plt.plot(x, y_h, 'b.', label=r'n = 1')
#plt.plot(x, y_h_1, 'g.', label=r'n = 10')
plt.title(r'SetState (default). P(test_count)')
plt.xlabel(r'test_count', fontsize=10)
plt.ylabel(r'P', fontsize=10)


plt.savefig('SetState_default.png')
plt.grid(True)

plt.show()