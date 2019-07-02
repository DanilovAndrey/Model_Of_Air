#import matplotlb.pyploy as plt
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import numpy as np
import os
import math
from PIL import Image
import time
import scipy.stats as stats

#plt.ion()

fig, ax = plt.subplots()

def update(frame):
	try:	
		plt.clf()
		f = open("File1.txt", "r")
		arr = []
		list_of_ints = []
		for line in f:
			arr.append(line)
		list_of_ints = [float(n) for n in arr]

		plt.hist(list_of_ints,bins = 40, color = 'blue', density = True)
	
		plt.ylabel('dN/N')
		plt.xlabel('Speed')
	
		try:
			density = stats.kde.gaussian_kde(list_of_ints)
			x = np.arange(0., max(list_of_ints), .1)
			plt.plot(x, density(x), color = 'red')
		except:
			print('error')
		f.close()
		p = stats.normaltest(list_of_ints)
		print(p)
	except:
		print('error2')

ani = FuncAnimation(fig, update, interval = 1000)

plt.show()
