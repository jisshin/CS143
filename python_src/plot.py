import matplotlib.pyplot as plt
import numpy as np

import matplotlib.cbook as cbook

fname = cbook.get_sample_data('example.csv', asfileobj = False)

### start plotting  assume i can just plot using header namespace

plt.plotfile(fname, ('time', 'flowstuff', 'adj_close'))

### http://matplotlib.org/examples/pylab_examples/plotfile_demo.html#pylab-examples-example-code-plotfile-demo-py
