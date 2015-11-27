#!/usr/bin/env python
from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np
import pandas as pd



info = pd.read_csv("output.csv")

### start plotting  assume i can just plot using header namespace

print info

x,y = np.loadtxt('output.csv',
                 unpack=True,
                 delimiter = ',', usecols=(0, 2))



plt.plot(x,y)
plt.show()
